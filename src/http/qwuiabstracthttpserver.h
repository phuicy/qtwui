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

#ifndef QWUIABSTRACTHTTPSERVER_H
#define QWUIABSTRACTHTTPSERVER_H

#include <QtCore/QObject>

class QwuiRessourceProviderServer;
class QwuiAbstractHttpServerDelegate;

class QwuiAbstractHttpServer : public QObject
{
    Q_OBJECT

public:
    enum RequestProcessingType {
        QueuedProcessing,
        ThreadedProcessing
    };

public:
    QwuiAbstractHttpServer(QObject* parent = NULL);
    virtual ~QwuiAbstractHttpServer();

    void setRessourceProviderServer(QwuiRessourceProviderServer* server);
    QwuiRessourceProviderServer* ressourceProviderServer() const;
    void setRequestProcessingType(RequestProcessingType t);
    RequestProcessingType requestProcessingType() const;

    virtual bool start() = 0;
    virtual QString error() const;

protected:
    void process(QwuiAbstractHttpServerDelegate* delegate);

private:
    QwuiRessourceProviderServer* m_server;
    RequestProcessingType m_type;
};

#endif // QWUIABSTRACTHTTPSERVER_H