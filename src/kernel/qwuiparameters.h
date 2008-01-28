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

#ifndef QWUIPARAMETERS_H
#define QWUIPARAMETERS_H

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtXml/QDomDocument>

class QHttpRequestHeader;

class QwuiParameters
{
public:
    QwuiParameters();
    virtual ~QwuiParameters();

    void init(const QHttpRequestHeader& header, const QString& postContent = QString::null);
    void clear();
    QString operator[](const QString& key) const;
    bool contains(const QString& key) const;
    QString get(const QString& key) const;
    QString post(const QString& key) const;
    QDomElement xmlElement() const;
    QString postContent() const;

private:
    QHash<QString, QString> m_getParameters;
    QHash<QString, QString> m_postParameters;
    QDomDocument m_xmlDoc;
    QString m_postContent;
};

#endif // QWUIPARAMETERS_H
