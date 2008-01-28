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

#include <QtWui/QwuiMessageRessource>
#include <QtCore/QTextStream>

QwuiMessageRessource::QwuiMessageRessource(const QString& path) :
    QwuiAbstractRessource(path)
{
}

QwuiMessageRessource::~QwuiMessageRessource()
{
}

QString QwuiMessageRessource::mimeType() const
{
    return "text/html";
}

qint64 QwuiMessageRessource::length() const
{
    return message().length();
}

void QwuiMessageRessource::sendToDevice(QIODevice* dev) const
{
    QTextStream stream(dev);
    stream << message();
}

void QwuiMessageRessource::setMessage(const QString& message)
{
    m_message = message;
}

QString QwuiMessageRessource::message() const
{
    return m_message;
}
