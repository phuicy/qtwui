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

#ifndef QWUIAPPLICATIONFACTORY_H
#define QWUIAPPLICATIONFACTORY_H

#include <QtWui/QwuiAbstractRessourceProviderFactory>
#include <QtCore/QStringList>
#include <QtWui/QwuiApplicationCreator>

class QwuiApplicationFactory : public QwuiAbstractRessourceProviderFactory
{
public:
    QwuiApplicationFactory(QwuiApplicationCreator creatorFunction, const QStringList& args);
    virtual ~QwuiApplicationFactory();

    virtual QwuiAbstractRessourceProvider* create(const QString& sessionId) const;

private:
    QwuiApplicationCreator m_creatorFunction;
    QStringList m_args;
};

#endif // QWUIAPPLICATIONFACTORY_H
