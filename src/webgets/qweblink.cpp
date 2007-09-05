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

#include <QtWeb/QWebLink>
#include <QtWeb/QWebTag>

QWebLink::QWebLink(QWebWebget* parent, const QString& webName) :
    QWebWebget(parent, webName),
    m_updateMethod(Qt::AjaxInsertionNone),
    m_webget(NULL),
    m_linkType(StandardLink)
{
    addJavascriptFile("qweblink.js");
}

QWebLink::QWebLink(QWebWebget* parent, const QString& webName, const QString& label) :
    QWebWebget(parent, webName),
    m_updateMethod(Qt::AjaxInsertionNone),
    m_webget(NULL),
    m_linkType(StandardLink),
    m_label(label)
{
    addJavascriptFile("qweblink.js");
}

QWebLink::QWebLink(QWebWebget* parent, const QString& webName, const QString& label, const QString& destination) :
    QWebWebget(parent, webName),
    m_updateMethod(Qt::AjaxInsertionNone),
    m_webget(NULL),
    m_standard(destination),
    m_linkType(StandardLink),
    m_label(label)
{
    addJavascriptFile("qweblink.js");
}

QWebLink::QWebLink(QWebWebget* parent, const QString& webName, const QString& label, QWebWebget* destination) :
    QWebWebget(parent, webName),
    m_updateMethod(Qt::AjaxInsertionNone),
    m_webget(destination),
    m_linkType(WebgetLink),
    m_label(label)
{
    addJavascriptFile("qweblink.js");
}

QWebLink::QWebLink(QWebWebget* parent, const QString& webName, const QString& label, QWebWebget* webgetToUpdate, Qt::QWebAjaxInsertion dst) :
    QWebWebget(parent, webName),
    m_updateMethod(dst),
    m_webget(webgetToUpdate),
    m_linkType(AjaxLink),
    m_label(label)
{
    addJavascriptFile("qweblink.js");
}

QWebLink::~QWebLink()
{
}

void QWebLink::setLabel(const QString& text)
{
    m_label = text;
}

QString QWebLink::label() const
{
    return m_label;
}

void QWebLink::setDestination(const QString& dst)
{
    m_linkType = StandardLink;
    m_standard = dst;
}

QString QWebLink::destination() const
{
    if (m_linkType == StandardLink) {
        return m_standard;
    }
    return QString::null;
}

void QWebLink::setDestinationWebget(QWebWebget* webget)
{
    m_linkType = WebgetLink;
    m_webget = webget;
}

QWebWebget* QWebLink::destinationWebget() const
{
    if (m_linkType == WebgetLink) {
        return m_webget;
    }
    return NULL;
}

void QWebLink::setAjaxDestination(QWebWebget* webgetToUpdate, Qt::QWebAjaxInsertion dst)
{
    m_linkType = AjaxLink;
    m_webget = webgetToUpdate;
    m_updateMethod = dst;
}

QWebWebget* QWebLink::ajaxDestinationWebget() const
{
    if (m_linkType == AjaxLink) {
        return m_webget;
    }
    return NULL;
}

Qt::QWebAjaxInsertion QWebLink::ajaxUpdateMethod() const
{
    if (m_linkType == AjaxLink) {
        return m_updateMethod;
    }
    return Qt::AjaxInsertionNone;
}

QWebLink::LinkType QWebLink::linkType() const
{
    return m_linkType;
}

void QWebLink::addParameter(const QString& name, const QString& value)
{
    m_parameters[name] = value;
}

QString QWebLink::parameter(const QString& name) const
{
    QHash<QString, QString>::ConstIterator it = m_parameters.find(name);
    if (it != m_parameters.end()) {
        return it.value();
    }
    return QString::null;
}

void QWebLink::render()
{
    QWebTag tag(this, "a");
    QString href;
    switch (m_linkType) {
        case AjaxLink:
            href += QString("javascript:handleAjaxClick('?call=") + webPath() + ".handleClick','" + serializeParameters() + "',";
            switch (m_updateMethod) {
                case Qt::AjaxInsertionNone:
                    href += "null, null)";
                    break;
                case Qt::AjaxInsertionReplace:
                    href += QString("'") + m_webget->webId() + "',null)";
                    break;
                case Qt::AjaxInsertionBefore:
                    href += QString("'") + m_webget->webId() + "',Insertion.Before)";
                    break;
                case Qt::AjaxInsertionAfter:
                    href += QString("'") + m_webget->webId() + "',Insertion.After)";
                    break;
                case Qt::AjaxInsertionTop:
                    href += QString("'") + m_webget->webId() + "',Insertion.Top)";
                    break;
                case Qt::AjaxInsertionBottom:
                    href += QString("'") + m_webget->webId() + "',Insertion.Bottom)";
                    break;
            }
            break;
        case WebgetLink:
            if (m_webget != NULL) {
                href += QString("?call=") + m_webget->webPath();
                QString params = serializeParameters();
                if (!params.isEmpty()) {
                    href += QString("&") + params;
                }
            }
            break;
        case StandardLink:
            href += m_standard;
            QString params = serializeParameters();
            if (!params.isEmpty()) {
                href += QString("&") + params;
            }
            break;
    }
    tag.setAttribute("href", href);
    tag.setText(m_label);
}

QString QWebLink::serializeAjaxParameters() const
{
    QString params("{");
    if (!m_parameters.isEmpty()) {
        QHash<QString, QString>::ConstIterator it = m_parameters.begin();
        QHash<QString, QString>::ConstIterator itEnd = m_parameters.end();
        for (; it != itEnd; ++it) {
            params += it.key() + ":" + it.value() + ",";
        }
        params.chop(1);
    }
    params += "}";
    return params;
}

QString QWebLink::serializeParameters() const
{
    QString params;
    QHash<QString, QString>::ConstIterator it = m_parameters.begin();
    QHash<QString, QString>::ConstIterator itEnd = m_parameters.end();
    for (; it != itEnd; ++it) {
        params += it.key() + "=" + it.value() + "&";
    }
    params.chop(1);
    return params;
}

void QWebLink::handleClick(QString& mimeType)
{
    emit clicked(mimeType);
}
