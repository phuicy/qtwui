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

#ifndef QWUIRESSOURCEPROVIDERSERVER_H
#define QWUIRESSOURCEPROVIDERSERVER_H

#include <QtCore/QObject>
#include <QtCore/QHash>

class QTimer;
class QReadWriteLock;
class QwuiAbstractRessourceProviderFactory;
class QwuiAbstractHttpServer;
class QwuiAbstractRessourceProvider;

class QwuiRessourceProviderServer : public QObject
{
    Q_OBJECT

public:
    QwuiRessourceProviderServer(QObject* parent = NULL);
    virtual ~QwuiRessourceProviderServer();

    void setRessourceProviderFactory(QwuiAbstractRessourceProviderFactory* factory);
    QwuiAbstractRessourceProviderFactory* ressourceProviderFactory() const;
    void setHttpServer(QwuiAbstractHttpServer* server);
    QwuiAbstractHttpServer* httpServer() const;
    void setDefaultSessionLifeTime(int secs);
    int defaultSessionLifeTime() const;

    virtual QwuiAbstractRessourceProvider* takeSession(const QString& sessionId);
    virtual void releaseSession(QwuiAbstractRessourceProvider* session);
    virtual QwuiAbstractRessourceProvider* newSession();

    virtual bool start();

protected:
    virtual void customEvent(QEvent* event);

private:
    void pullToCurrentThread(QObject* obj);

private slots:
    void cleanupSessions();

private:
    QHash<QString, QwuiAbstractRessourceProvider*> m_sessions;
    QwuiAbstractRessourceProviderFactory* m_factory;
    QwuiAbstractHttpServer* m_server;
    QTimer* m_sessionCleanupTimer;
    QReadWriteLock* m_lock;
    int m_defaultSessionLifeTime;
};

#endif // QWUIRESSOURCEPROVIDERSERVER_H
