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
    if (m_webget != NULL) {
        QTextStream stream(m_webget->device());
        stream << generate();
        stream.flush();
    }
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

QString QWebTag::generate() const
{
    QString content;
    QHash<QString, QString> attributes(m_attributes);

    attributes["class"] = m_webget->webClass();
    attributes["id"] = m_webget->webId();
    QString& style = attributes["style"];
    if (!style.isEmpty() && style[style.size() - 1] != ';') {
        style += ";";
    }
    QHash<QString, QString>::ConstIterator it = m_webget->m_styleItems.begin();
    QHash<QString, QString>::ConstIterator itEnd = m_webget->m_styleItems.end();
    for (; it != itEnd; ++it) {
        style += it.key() + ":" + it.value() + ";";
    }
    content = QString("<") + m_tag;
    it = attributes.begin();
    itEnd = attributes.end();
    for (; it != itEnd; ++it) {
        if (!it.value().isEmpty()) {
            content += QString(" ") + it.key() + "=\"" + it.value() + "\"";
        }
    }
    if (!m_emptyTag) {
        content += ">\n";

        if (m_text.isEmpty()) {
            m_webget->renderContent();
        } else {
            content += m_text;
        }
        content += "</" + m_tag + ">\n";
    } else {
        content + " />\n";
    }
    return content;
}
