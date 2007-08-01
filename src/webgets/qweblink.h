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

#ifndef QWEBLINK_H
#define QWEBLINK_H

#include <QtWeb/QWebWebget>
#include <QtWeb/QWebGlobal>

class QWebLink : public QWebWebget
{
    Q_OBJECT

public:
    enum LinkType { AjaxLink, WebgetLink, StandardLink };

public:
    QWebLink(QWebWebget* parent = NULL, const QString& webName = QString::null);
    QWebLink(QWebWebget* parent, const QString& webName, const QString& label);
    QWebLink(QWebWebget* parent, const QString& webName, const QString& label, const QString& destination); // StandardLink
    QWebLink(QWebWebget* parent, const QString& webName, const QString& label, QWebWebget* destination); // WebgetLink
    QWebLink(QWebWebget* parent, const QString& webName, const QString& label, QWebWebget* webgetToUpdate, Qt::QWebAjaxInsertion dst); // AjaxLink
    virtual ~QWebLink();

    void setLabel(const QString& text);
    QString label() const;

    // StandardLink
    void setDestination(const QString& dst);
    QString destination() const;
    // WebgetLink
    void setDestinationWebget(QWebWebget* webget);
    QWebWebget* destinationWebget() const;
    // AjaxLink
    void setAjaxDestination(QWebWebget* webgetToUpdate, Qt::QWebAjaxInsertion dst);
    QWebWebget* ajaxDestinationWebget() const;
    Qt::QWebAjaxInsertion ajaxUpdateMethod() const;

    LinkType linkType() const;

    void addParameter(const QString& name, const QString& value);
    QString parameter(const QString& name) const;

protected:
    virtual void beforeRenderChildren(QTextStream& stream);
    virtual void afterRenderChildren(QTextStream& stream);

private:
    QString serializeAjaxParameters() const;
    QString serializeParameters() const;

private slots:
    void handleClick(QString& mimeType, QIODevice* dev);

signals:
    void clicked(QString& mimeType, QIODevice* dev);

private:
    Qt::QWebAjaxInsertion m_updateMethod;
    QWebWebget* m_webget;
    QString m_standard;
    LinkType m_linkType;
    QString m_label;
    QHash<QString, QString> m_parameters;
};

#endif // QWEBLINK_H
