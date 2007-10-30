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

#ifndef QWEBTAG_H
#define QWEBTAG_H

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>

class QWebWebget;
class QTextStream;

class QWebTag
{
public:
    QWebTag(QWebWebget* w, const QString& tag);
    QWebTag(QWebTag* parent, const QString& tag);
    virtual ~QWebTag();

    void setAttribute(const QString& name, const QString& value);
    QString attribute(const QString& name) const;

    void setText(const QString& text);
    QString text() const;

private:
    void generate(QTextStream* stream);

private:
    QString m_tag;
    QWebWebget* m_webget;
    bool m_emptyTag;
    QString m_text;
    QHash<QString, QString> m_attributes;
    QList<QWebTag*> m_children;
};

#endif // QWEBTAG_H