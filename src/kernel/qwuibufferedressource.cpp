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

#include <QtWui/QwuiBufferedRessource>
#include <QtCore/QIODevice>

QwuiBufferedRessource::QwuiBufferedRessource(const QString& path, const QString& mimeType, const QByteArray& source) :
    QwuiAbstractRessource(path),
    m_mimeType(mimeType),
    m_source(source)
{
}

QwuiBufferedRessource::~QwuiBufferedRessource()
{
}

QString QwuiBufferedRessource::mimeType() const
{
    return m_mimeType;
}

qint64 QwuiBufferedRessource::length() const
{
    return m_source.length();
}

void QwuiBufferedRessource::sendToDevice(QIODevice* dev) const
{
    dev->write(m_source);
}
