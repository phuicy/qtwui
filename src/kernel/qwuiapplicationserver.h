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
#ifndef QWUIAPPLICATIONSERVER_H
#define QWUIAPPLICATIONSERVER_H

#include <QtWui/QwuiRessourceProviderServer>
#include <QtWui/QwuiApplicationCreator>
#include <QtWui/QwuiGlobal>

class QTWUI_EXPORT QwuiApplicationServer : public QwuiRessourceProviderServer
{
    Q_OBJECT

public:
    QwuiApplicationServer(QwuiApplicationCreator creatorFunction, QObject* parent = NULL);
    virtual ~QwuiApplicationServer();

    void setBuiltInServerPort(quint16 port);
    void exec();

private slots:
    void initialize();
};

#endif // QWUIAPPLICATIONSERVER_H
