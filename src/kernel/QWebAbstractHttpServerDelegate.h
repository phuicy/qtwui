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

#ifndef QWEBABSTRACTHTTPSERVERWORKINGTHREAD_H
#define QWEBABSTRACTHTTPSERVERWORKINGTHREAD_H

#include <QThread>
#include <QHttpRequestHeader>

class QIODevice;
class QHttpResponseHeader;
class QLocale;
class QTimer;
class QWebAbstractRessource;
class QWebAbstractRessourceProvider;
class QWebMessageRessource;
class QWebRessourceProviderServer;

class QWebAbstractHttpServerDelegate : public QThread
{
    Q_OBJECT

public:
    QWebAbstractHttpServerDelegate(QWebRessourceProviderServer* providerServer = NULL);
    virtual ~QWebAbstractHttpServerDelegate();

protected:
    QIODevice* device() const;
    virtual QIODevice* createDevice() = 0;
    virtual void deleteDevice(QIODevice* device) = 0;
    virtual QHttpRequestHeader readHttpRequestHeader() = 0;
    virtual QString readHttpRequestContent() = 0;
    virtual void writeHttpResponseHeader(const QHttpResponseHeader& responseHeader) = 0;
    virtual void run();
    virtual void handleRequest(const QHttpRequestHeader& header);
    virtual void handleHeadRequest(const QHttpRequestHeader& header);

    void setSessionId(QHttpHeader& header, const QString& sessionId) const;
    QString sessionId(const QHttpHeader& header) const;

protected slots:
    virtual void doRun();

private:
    QIODevice* m_device;
    QWebRessourceProviderServer* m_providerServer;
    QLocale* m_en_USLocale;
    QWebAbstractRessourceProvider* m_provider;
    QWebMessageRessource* m_notFoundRessource;
    QWebAbstractRessource* m_ressource;
    QTimer* m_timer;
};

#endif // QWEBABSTRACTHTTPSERVERWORKINGTHREAD_H
