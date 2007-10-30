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

#include <QtWeb/QWebStackedWebget>
#include <QtWeb/QWebStackedLayout>

QWebStackedWebget::QWebStackedWebget(QWebWebget* parent, const QString& webName) :
    QWebWebget(parent, webName)
{
    QWebStackedLayout* l = new QWebStackedLayout(this);
    connect(l, SIGNAL(currentChanged(int)), this, SIGNAL(currentChanged(int)));
    connect(l, SIGNAL(itemRemoved(int)), this, SIGNAL(widgetRemoved(int)));
}

QWebStackedWebget::~QWebStackedWebget()
{
}

int QWebStackedWebget::addWebget(QWebWebget* w)
{
    w->setParent(this);
    return qobject_cast<QWebStackedLayout*>(layout())->addWebget(w);
}

int QWebStackedWebget::count() const
{
    return qobject_cast<QWebStackedLayout*>(layout())->count();
}

int QWebStackedWebget::currentIndex() const
{
    return qobject_cast<QWebStackedLayout*>(layout())->currentIndex();
}

QWebWebget* QWebStackedWebget::currentWebget() const
{
    QWebLayoutItem* item = qobject_cast<QWebStackedLayout*>(layout())->currentItem();
    if (item != NULL) {
        return static_cast<QWebWebgetItem*>(item)->webget();
    }
    return NULL;
}

int QWebStackedWebget::indexOf(QWebWebget* w) const
{
    return qobject_cast<QWebStackedLayout*>(layout())->indexOf(w);
}

int QWebStackedWebget::insertWebget(int index, QWebWebget* w)
{
    return qobject_cast<QWebStackedLayout*>(layout())->insertWebget(index, w);
}

void QWebStackedWebget::removeWebget(QWebWebget* w)
{
    QWebStackedLayout* l = qobject_cast<QWebStackedLayout*>(layout());
    l->removeItem(l->itemAt(l->indexOf(w)));
}

QWebWebget* QWebStackedWebget::webget(int index) const
{
    QWebLayoutItem* item = qobject_cast<QWebStackedLayout*>(layout())->itemAt(index);
    if (item != NULL) {
        return static_cast<QWebWebgetItem*>(item)->webget();
    }
    return NULL;
}

void QWebStackedWebget::setCurrentIndex(int index)
{
    qobject_cast<QWebStackedLayout*>(layout())->setCurrentIndex(index);
}

void QWebStackedWebget::setCurrentWebget(QWebWebget* w)
{
    QWebStackedLayout* l = qobject_cast<QWebStackedLayout*>(layout());
    int index = l->indexOf(w);
    if (index != -1) {
        l->setCurrentIndex(index);
    }
}
