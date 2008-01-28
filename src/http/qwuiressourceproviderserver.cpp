/***************************************************************************
 *   Copyright (C) 2007 by Eric ALBER                                      *
 *   eric.alber@gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QtWui/QwuiRessourceProviderServer>
#include <QtCore/QTimer>
#include <QtCore/QReadWriteLock>
#include <QtCore/QWriteLocker>
#include <QtCore/QReadLocker>
#include <QtCore/QUuid>
#include <QtCore/QEvent>
#include <QtCore/QSemaphore>
#include <QtCore/QThread>
#include <QtCore/QCoreApplication>
#include <QtWui/QwuiAbstractRessourceProviderFactory>
#include <QtWui/QwuiAbstractHttpServer>
#include <QtWui/QwuiAbstractRessourceProvider>

class QwuiObjectThreadChangeEvent : public QEvent
{
public:
    enum QwuiObjectThreadChangeEventType { ObjectThreadChange = QEvent::User + 32768 };

public:
    QwuiObjectThreadChangeEvent(QObject* obj, QThread* target, QSemaphore* sem) :
        QEvent((QEvent::Type)ObjectThreadChange),
        m_object(obj),
        m_targetThread(target),
        m_semaphore(sem)
    {
    }

    virtual ~QwuiObjectThreadChangeEvent()
    {
    }

    QObject* object() const
    {
        return m_object;
    }

    QThread* targetThread() const
    {
        return m_targetThread;
    }

    QSemaphore* semaphore() const
    {
        return m_semaphore;
    }

private:
    QObject* m_object;
    QThread* m_targetThread;
    QSemaphore* m_semaphore;
};

QwuiRessourceProviderServer::QwuiRessourceProviderServer(QObject* parent) :
    QObject(parent),
    m_factory(NULL),
    m_server(NULL),
    m_sessionCleanupTimer(NULL),
    m_lock(NULL),
    m_defaultSessionLifeTime(1800)
{
    m_lock = new QReadWriteLock();
    m_sessionCleanupTimer = new QTimer(this);
    connect(m_sessionCleanupTimer, SIGNAL(timeout()), this, SLOT(cleanupSessions()));
    m_sessionCleanupTimer->start(30000); // Cleanup sessions every 30 seconds.
}

QwuiRessourceProviderServer::~QwuiRessourceProviderServer()
{
    delete m_factory;
    delete m_server;
    delete m_sessionCleanupTimer;
    delete m_lock;
}

void QwuiRessourceProviderServer::setRessourceProviderFactory(QwuiAbstractRessourceProviderFactory* factory)
{
    delete m_factory;
    m_factory = factory;
}

QwuiAbstractRessourceProviderFactory* QwuiRessourceProviderServer::ressourceProviderFactory() const
{
    return m_factory;
}

void QwuiRessourceProviderServer::setHttpServer(QwuiAbstractHttpServer* server)
{
    delete m_server;
    m_server = server;
}

QwuiAbstractHttpServer* QwuiRessourceProviderServer::httpServer() const
{
    return m_server;
}

void QwuiRessourceProviderServer::setDefaultSessionLifeTime(int secs)
{
    m_defaultSessionLifeTime = secs;
}

int QwuiRessourceProviderServer::defaultSessionLifeTime() const
{
    return m_defaultSessionLifeTime;
}

QwuiAbstractRessourceProvider* QwuiRessourceProviderServer::takeSession(const QString& sessionId)
{
    QReadLocker locker(m_lock);
    QHash<QString, QwuiAbstractRessourceProvider*>::Iterator it = m_sessions.find(sessionId);
    if (it != m_sessions.end()) {
        pullToCurrentThread(it.value());
        return it.value();
    }
    return NULL;
}

void QwuiRessourceProviderServer::releaseSession(QwuiAbstractRessourceProvider* session)
{
    if (session != NULL) {
        if (session->keepSessions()) {
            session->moveToThread(thread());
            session->resetSessionTimeoutDate();
        } else {
            delete session;
        }
    }
}

QwuiAbstractRessourceProvider* QwuiRessourceProviderServer::newSession()
{
    if (m_factory != NULL) {
        QWriteLocker locker(m_lock);
        QwuiAbstractRessourceProvider* provider = m_factory->create(QUuid::createUuid());
        provider->setSessionLifeTime(m_defaultSessionLifeTime);
        provider->resetSessionTimeoutDate();
        if (provider->keepSessions()) {
            m_sessions[provider->sessionId()] = provider;
        }
        return provider;
    }
    return NULL;
}

bool QwuiRessourceProviderServer::start()
{
    if (m_server != NULL) {
        return m_server->start();
    }
    return false;
}

void QwuiRessourceProviderServer::customEvent(QEvent* event)
{
    if (event->type() == (QEvent::Type) QwuiObjectThreadChangeEvent::ObjectThreadChange) {
        QwuiObjectThreadChangeEvent* e = static_cast<QwuiObjectThreadChangeEvent*>(event);
        e->object()->moveToThread(e->targetThread());
        e->semaphore()->release(1);
        event->accept();
    }
}

void QwuiRessourceProviderServer::pullToCurrentThread(QObject* obj)
{
    if (obj->thread() != QThread::currentThread()) {
        QSemaphore sem(0);
        QwuiObjectThreadChangeEvent* event = new QwuiObjectThreadChangeEvent(obj, QThread::currentThread(), &sem);
        QCoreApplication::postEvent(this, event);
        sem.acquire(1);
    }
}

void QwuiRessourceProviderServer::cleanupSessions()
{
    QWriteLocker locker(m_lock);
    QHash<QString, QwuiAbstractRessourceProvider*>::Iterator it = m_sessions.begin();
    while (it != m_sessions.end()) {
        if (it.value()->isSessionTimedOut() || !it.value()->keepSessions()) {
            delete it.value();
            it = m_sessions.erase(it);
        } else {
            ++it;
        }
    }
}
