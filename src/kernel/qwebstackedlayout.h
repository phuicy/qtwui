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

#ifndef QWEBSTACKEDLAYOUT_H
#define QWEBSTACKEDLAYOUT_H

#include <QtWeb/QWebLayout>
#include <QtCore/QList>

class QWebStackedLayout : public QWebLayout
{
    Q_OBJECT

public:
    QWebStackedLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebStackedLayout(Unit unit = RelativeStrength);
    virtual ~QWebStackedLayout();
    virtual LayoutType type() const;
    void addWebget(QWebWebget* w);
    void insertWebget(int index, QWebWebget* w);
    void addItem(QWebLayoutItem* item);
    void insertItem(int index, QWebLayoutItem* item);
    virtual void removeItem(QWebLayoutItem* item);
    virtual int count() const;
    virtual int indexOf(QWebWebget* w) const;
    virtual bool contains(QWebWebget* w) const;
    virtual QWebLayoutItem* itemAt(int index) const;
    virtual QWebLayoutItem* takeAt(int index);
    int currentIndex() const;
    QWebLayoutItem* currentItem() const;
    virtual void render();

public slots:
    void setCurrentIndex(int index);
    void setCurrentItem(QWebLayoutItem* item);

signals:
    void currentChanged(int index);
    void itemRemoved(int index);

private slots:
    void updateParentWebget();

private:
    QList<QWebLayoutItem*> m_items;
    int m_currentIndex;
};

#endif // QWEBSTACKEDLAYOUT_H
