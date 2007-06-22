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

#ifndef QWEBHTTPSERVERWORKINGTHREAD_H
#define QWEBHTTPSERVERWORKINGTHREAD_H

#include <QtWeb/QWebAbstractHttpServerDelegate>

class QWebHttpServerDelegate : public QWebAbstractHttpServerDelegate
{
    Q_OBJECT

public:
    QWebHttpServerDelegate(QWebRessourceProviderServer* providerServer = NULL, int socketDescriptor = 0);
    virtual ~QWebHttpServerDelegate();

protected:
    virtual QIODevice* createDevice();
    virtual void deleteDevice(QIODevice* device);
    virtual QHttpRequestHeader readHttpRequestHeader();
    virtual QString readHttpRequestContent();
    virtual void writeHttpResponseHeader(const QHttpResponseHeader& responseHeader);

private:
    int m_socketDescriptor;
    uint m_requestContentLength;
};

#endif // QWEBHTTPSERVERWORKINGTHREAD_H