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

#ifndef QWEBABSTRACTHTTPSERVER_H
#define QWEBABSTRACTHTTPSERVER_H

#include <QtCore/QObject>

class QWebRessourceProviderServer;
class QWebAbstractHttpServerDelegate;

class QWebAbstractHttpServer : public QObject
{
    Q_OBJECT

public:
    enum RequestProcessingType {
        QueuedProcessing,
        ThreadedProcessing
    };

public:
    QWebAbstractHttpServer(QObject* parent = NULL);
    virtual ~QWebAbstractHttpServer();

    void setRessourceProviderServer(QWebRessourceProviderServer* server);
    QWebRessourceProviderServer* ressourceProviderServer() const;
    void setRequestProcessingType(RequestProcessingType t);
    RequestProcessingType requestProcessingType() const;

    virtual bool start() = 0;
    virtual QString error() const;

protected:
    void process(QWebAbstractHttpServerDelegate* delegate);

private:
    QWebRessourceProviderServer* m_server;
    RequestProcessingType m_type;
};

#endif // QWEBABSTRACTHTTPSERVER_H
