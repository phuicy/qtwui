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

#ifndef QWEBGRIDLAYOUT_H
#define QWEBGRIDLAYOUT_H

#include <QtWeb/QWebLayout>
#include <QtCore/QList>
#include <QtCore/QPair>

class QWebGridLayout : public QWebLayout
{
public:
    QWebGridLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebGridLayout(Unit unit = RelativeStrength);
    virtual ~QWebGridLayout();
/*    virtual LayoutType type() const;
    virtual void addItem(QWebLayoutItem* item);
    void addItem(QWebLayoutItem* item, int row, int column, int rowSpan = 1, int columnSpan = 1);
    void addWebget(QWebWebget* w, int row, int column, int rowSpan = 1, int columnSpan = 1);
    virtual void removeItem(QWebLayoutItem* item);
    virtual int count() const;
    virtual int indexOf(QWebWebget* w) const;
    virtual QWebLayoutItem* itemAt(int index) const;
    virtual QWebLayoutItem* takeAt(int index);
*/
};

#endif // QWEBGRIDLAYOUT_H
