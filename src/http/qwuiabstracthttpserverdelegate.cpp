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

#include <QtWui/QwuiAbstractHttpServerDelegate>
#include <QtCore/QIODevice>
#include <QtCore/QLocale>
#include <QtCore/QTimer>
#include <QtCore/QTextStream>
#include <QtNetwork/QHttpHeader>
#include <QtNetwork/QHttpRequestHeader>
#include <QtNetwork/QHttpResponseHeader>
#include <QtWui/QwuiAbstractRessource>
#include <QtWui/QwuiAbstractRessourceProvider>
#include <QtWui/QwuiRessourceProviderServer>
#include <QtWui/QwuiMessageRessource>

QwuiAbstractHttpServerDelegate::QwuiAbstractHttpServerDelegate(QwuiRessourceProviderServer* providerServer) :
    QThread(NULL),
    m_device(NULL),
    m_providerServer(providerServer),
    m_en_USLocale(NULL),
    m_notFoundRessource(NULL),
    m_ressource(NULL),
    m_timer(NULL)
{
    m_en_USLocale = new QLocale(QLocale::English, QLocale::UnitedStates);
    m_notFoundRessource = new QwuiMessageRessource();
    m_notFoundRessource->setMessage("<html><body><h2>Ressource not found</h2><br /><a href=\"http://qtweb.sourceforge.net\">QtWui Application Server</a></body></html>");
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

QwuiAbstractHttpServerDelegate::~QwuiAbstractHttpServerDelegate()
{
    delete m_en_USLocale;
    delete m_notFoundRessource;
}

QIODevice* QwuiAbstractHttpServerDelegate::device() const
{
    return m_device;
}

void QwuiAbstractHttpServerDelegate::run()
{
    m_timer = new QTimer();
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(doRun()), Qt::DirectConnection);
    m_timer->start(0); // call doRun() after this thread's event loop started.
    exec();
}

void QwuiAbstractHttpServerDelegate::handleRequest(const QHttpRequestHeader& header)
{
    handleHeadRequest(header);
    if (m_ressource->exists()) {
        m_ressource->sendToDevice(m_device);
    } else {
        m_notFoundRessource->sendToDevice(m_device);
    }
}

void QwuiAbstractHttpServerDelegate::handleHeadRequest(const QHttpRequestHeader& header)
{
    Q_UNUSED(header);

    QHttpResponseHeader responseHeader;

    QDateTime dt = QDateTime::currentDateTime().toUTC();
    QString dtString = m_en_USLocale->toString(dt.date(), "ddd, dd MMM yyyy") + " " + m_en_USLocale->toString(dt.time(), "hh:mm:ss") + " GMT";
    responseHeader.addValue("Date", dtString);

    if (m_provider->keepSessions()) {
        setSessionId(responseHeader, m_provider->sessionId());
    }

    if (m_ressource->exists()) {
        responseHeader.setStatusLine(200, "OK", 1, 0);
        responseHeader.setContentType(m_ressource->mimeType());
        responseHeader.setContentLength(m_ressource->length());
    } else {
        responseHeader.setStatusLine(404, "Not Found", 1, 0);
        responseHeader.setContentType(m_notFoundRessource->mimeType());
        responseHeader.setContentLength(m_notFoundRessource->length());
    }

    writeHttpResponseHeader(responseHeader);
qDebug(responseHeader.toString().toAscii());
}

void QwuiAbstractHttpServerDelegate::setSessionId(QHttpHeader& header, const QString& sessionId) const
{
    header.addValue("Set-Cookie", QString("QtWuiSessionId=") + sessionId + "; Path=/; Version=1");
}

QString QwuiAbstractHttpServerDelegate::sessionId(const QHttpHeader& header) const
{
    QStringList cookies = header.allValues("cookie");
    QStringList::ConstIterator it = cookies.begin();
    QStringList::ConstIterator itEnd = cookies.end();
    for (; it != itEnd; ++it) {
        int begin = it->indexOf("QtWuiSessionId=");
        if (begin != -1) {
            begin += 15; // Length of "QtWuiSessionId="
            int end = it->indexOf(";", begin);
            return it->mid(begin, end - begin);
        }
    }
    return QString::null;
}

void QwuiAbstractHttpServerDelegate::doRun()
{
    delete m_timer;
    m_timer = NULL;

    bool deleteRessource = true;

    m_device = createDevice();

    if (m_device == NULL) {
        qWarning("QIODevice creation error");
        delete m_device;
        m_device = NULL;
        quit();
        return;
    }
    if (!m_device->waitForReadyRead(30000)) {
        qWarning("Incomming request data reading timeout");
        delete m_device;
        m_device = NULL;
        quit();
        return;
    }

    QHttpRequestHeader header = readHttpRequestHeader();

    QString sessId = sessionId(header);

    if (sessId == QString::null) {
        m_provider = m_providerServer->newSession();
    } else {
        m_provider = m_providerServer->takeSession(sessId);
        if (m_provider == NULL) {
            // Session expired
            m_provider = m_providerServer->newSession();
        }
    }

    m_ressource = m_provider->provide(header, readHttpRequestContent());
    if (m_ressource == NULL) {
        m_ressource = m_notFoundRessource;
        deleteRessource = false;
    }

    QString method = header.method();

    if (method == "GET" || method == "POST") {
        handleRequest(header);
    } else if (method == "HEAD") {
        handleHeadRequest(header);
    }

    if (deleteRessource) {
        delete m_ressource;
    }
    m_ressource = NULL;

    m_providerServer->releaseSession(m_provider);
    m_provider = NULL;

    while (m_device->waitForBytesWritten(-1) && m_device->bytesToWrite() > 0);

    deleteDevice(m_device);
    m_device = NULL;
    if (isRunning()) {
        quit();
    }
}
