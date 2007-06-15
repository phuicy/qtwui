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

#include "QWebApplicationServer.h"
#include <QTimer>
#include <QCoreApplication>
#include "QWebHttpServer.h"
#include "QWebApplicationFactory.h"

QWebApplicationServer::QWebApplicationServer(QWebApplicationCreator creatorFunction, QObject* parent) :
    QWebRessourceProviderServer(parent)
{
    setRessourceProviderFactory(new QWebApplicationFactory(creatorFunction, QCoreApplication::arguments()));
    QWebHttpServer* server = new QWebHttpServer(this);
    server->setRessourceProviderServer(this);
    setHttpServer(server);
}

QWebApplicationServer::~QWebApplicationServer()
{
}

void QWebApplicationServer::setBuiltInServerPort(quint16 port)
{
    qobject_cast<QWebHttpServer*>(httpServer())->setPort(port);
}

void QWebApplicationServer::exec()
{
    QTimer::singleShot(0, this, SLOT(initialize()));
}

void QWebApplicationServer::initialize()
{
    if (!start()) {
        qWarning(qobject_cast<QWebHttpServer*>(httpServer())->error().toAscii().data());
    }
}
