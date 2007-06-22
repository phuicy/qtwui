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

#include <QtWeb/QWebAbstractHttpServer>

QWebAbstractHttpServer::QWebAbstractHttpServer(QObject* parent) :
    QObject(parent),
    m_server(NULL)
{
}

QWebAbstractHttpServer::~QWebAbstractHttpServer()
{
}

void QWebAbstractHttpServer::setRessourceProviderServer(QWebRessourceProviderServer* server)
{
    m_server = server;
}

QWebRessourceProviderServer* QWebAbstractHttpServer::ressourceProviderServer() const
{
    return m_server;
}

QString QWebAbstractHttpServer::error() const
{
    return QString::null;
}