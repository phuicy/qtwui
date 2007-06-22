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

#ifndef QWEBABSTRACTRESSOURCE_H
#define QWEBABSTRACTRESSOURCE_H

#include <QtCore/QString>

class QIODevice;

class QWebAbstractRessource
{
public:
    QWebAbstractRessource(const QString& path = QString::null);
    virtual ~QWebAbstractRessource();

    virtual QString mimeType() const = 0;
    virtual qint64 length() const = 0;
    virtual QString path() const;
    virtual bool exists() const;
    virtual void sendToDevice(QIODevice* dev) const = 0;

private:
    QString m_path;
};

#endif // QWEBABSTRACTRESSOURCE_H