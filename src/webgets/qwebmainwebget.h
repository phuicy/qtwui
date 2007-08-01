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

#ifndef QWEBMAINWEBGET_H
#define QWEBMAINWEBGET_H

#include <QtWeb/QWebWebget>

class QWebMainWebget : public QWebWebget
{
    Q_OBJECT

public:
    QWebMainWebget(QWebWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QWebMainWebget();
    void setTitle(const QString& title);
    QString title() const;

protected:
    virtual void beforeRenderChildren(QTextStream& stream);
    virtual void afterRenderChildren(QTextStream& stream);

private:
    QString m_title;
};

#endif // QWEBMAINWEBGET_H
