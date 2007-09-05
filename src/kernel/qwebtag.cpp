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

#include <QtWeb/QWebTag>
#include <QtCore/QTextStream>
#include <QtWeb/QWebWebget>
#include <QtWeb/QWebLayout>

QWebTag::QWebTag(QWebWebget* w, const QString& tag, bool emptyTag) :
    m_tag(tag),
    m_webget(w),
    m_emptyTag(emptyTag)
{
}

QWebTag::~QWebTag()
{
    QTextStream stream(m_webget->device());
    m_attributes["class"] = m_webget->webClass();
    m_attributes["id"] = m_webget->webId();
    QString& style = m_attributes["style"];
    if (!style.isEmpty() && style[style.size() - 1] != ';') {
        style += ";";
    }
    QHash<QString, QString>::ConstIterator it = m_webget->m_styleItems.begin();
    QHash<QString, QString>::ConstIterator itEnd = m_webget->m_styleItems.end();
    for (; it != itEnd; ++it) {
        style += it.key() + ":" + it.value() + ";";
    }
    stream << "<" << m_tag;
    it = m_attributes.begin();
    itEnd = m_attributes.end();
    for (; it != itEnd; ++it) {
        if (!it.value().isEmpty()) {
            stream << " " << it.key() << "=\"" << it.value() << "\"";
        }
    }
    if (!m_emptyTag) {
        stream << ">\n";
        stream.flush();

        if (m_text.isEmpty()) {
            m_webget->renderContent();
        } else {
            stream << m_text;
        }
        stream << "</" << m_tag << ">\n";
    } else {
        stream << " />\n";
    }

    stream.flush();
}

void QWebTag::setAttribute(const QString& name, const QString& value)
{
    m_attributes[name] = value;
}

QString QWebTag::attribute(const QString& name) const
{
    QHash<QString, QString>::ConstIterator it = m_attributes.find(name);
    if (it == m_attributes.end()) {
        return QString();
    }
    return it.value();
}

void QWebTag::setText(const QString& text)
{
    m_text = text;
}

QString QWebTag::text() const
{
    return m_text;
}
