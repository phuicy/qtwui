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

#include "QWebParameters.h"
#include <QHttpRequestHeader>
#include <QUrl>

QWebParameters::QWebParameters(const QHttpRequestHeader& header, const QString& postContent)
{
    m_postContent = postContent;

    QUrl url(header.path());
    QList<QPair<QString, QString> > items = url.queryItems();
    QList<QPair<QString, QString> >::ConstIterator it = items.begin();
    QList<QPair<QString, QString> >::ConstIterator itEnd = items.end();
    for (; it != itEnd; ++it) {
        m_getParameters[it->first] = it->second;
    }

    QString contentType(header.contentType());
    if (contentType == "text/xml" || contentType == "application/xml") {
        m_xmlDoc.setContent(m_postContent);
    } else if (contentType == "application/x-url-encoded") {
        QStringList postParams(m_postContent.split("&", QString::SkipEmptyParts));
        QStringList::Iterator it = postParams.begin();
        QStringList::Iterator itEnd = postParams.end();
        for (; it != itEnd; ++it) {
            QStringList pair(it->split("=", QString::SkipEmptyParts));
            if (pair.count() == 2) {
                m_postParameters[pair[0]] = pair[1];
            }
        }
    }
}

QWebParameters::~QWebParameters()
{
}

QString QWebParameters::operator[](const QString& key) const
{
    QString value = get(key);
    if (!value.isNull()) {
        return value;
    }
    return post(key);
}

bool QWebParameters::contains(const QString& key) const
{
    return (m_getParameters.find(key) == m_getParameters.end()) && (m_postParameters.find(key) == m_postParameters.end());
}

QString QWebParameters::get(const QString& key) const
{
    QHash<QString, QString>::ConstIterator it = m_getParameters.find(key);
    if (it != m_getParameters.end()) {
        return it.value();
    }
    return QString::null;
}

QString QWebParameters::post(const QString& key) const
{
    QHash<QString, QString>::ConstIterator it = m_postParameters.find(key);
    if (it != m_postParameters.end()) {
        return it.value();
    }
    return QString::null;
}

QDomElement QWebParameters::xmlElement() const
{
    return m_xmlDoc.documentElement();
}

QString QWebParameters::postContent() const
{
    return m_postContent;
}
