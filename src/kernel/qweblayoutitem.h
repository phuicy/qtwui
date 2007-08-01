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

#ifndef QWEBLAYOUTITEM_H
#define QWEBLAYOUTITEM_H

#include <QtCore/QString>

class QWebWebget;
class QWebParameters;
class QIODevice;

class QWebLayoutItem
{
public:
    enum ItemType {
        WebgetItem,
        SpacerItem,
        LayoutItem
    };
public:
    QWebLayoutItem();
    virtual ~QWebLayoutItem();
    virtual ItemType itemType() const = 0;
    virtual void render(QIODevice* dev) = 0;
};

class QWebWebgetItem : public QWebLayoutItem
{
public:
    QWebWebgetItem(QWebWebget* w);
    virtual ~QWebWebgetItem();
    QWebWebget* webget() const;
    virtual ItemType itemType() const;
    virtual void render(QIODevice* dev);

private:
    QWebWebget* m_webget;
};

class QWebSpacerItem : public QWebLayoutItem
{
public:
    QWebSpacerItem();
    virtual ~QWebSpacerItem();
    virtual ItemType itemType() const;
    virtual void render(QIODevice* dev);
};

#endif // QWEBLAYOUTITEM_H
