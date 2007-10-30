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

#include <QtWeb/QWebStackedLayout>
#include <QtWeb/QWebWebget>

QWebStackedLayout::QWebStackedLayout(QWebWebget* parent) :
    QWebLayout(parent),
    m_currentIndex(-1)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(updateParentWebget()));
}

QWebStackedLayout::QWebStackedLayout() :
    QWebLayout(NULL),
    m_currentIndex(-1)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(updateParentWebget()));
}

QWebStackedLayout::~QWebStackedLayout()
{
    while (!m_items.isEmpty()) {
        delete m_items.takeFirst();
    }
}

QWebLayout::LayoutType QWebStackedLayout::type() const
{
    return QWebLayout::StackedLayout;
}

int QWebStackedLayout::addWebget(QWebWebget* w)
{
    return insertWebget(m_items.count(), w);
}

int QWebStackedLayout::insertWebget(int index, QWebWebget* w)
{
    return insertItem(index, new QWebWebgetItem(w));
}

int QWebStackedLayout::addItem(QWebLayoutItem* item)
{
    return insertItem(m_items.count(), item);
}

int QWebStackedLayout::insertItem(int index, QWebLayoutItem* item)
{
    if (index < 0) {
        index = 0;
    } else if (index > m_items.count()) {
        index = m_items.count();
    }
    m_items.insert(index, item);
    if (m_currentIndex == -1) {
        m_currentIndex = 0;
        emit currentChanged(m_currentIndex);
    }
    return index;
}

void QWebStackedLayout::removeItem(QWebLayoutItem* item)
{
    int index = m_items.indexOf(item);
    if (index != -1) {
        m_items.removeAt(index);
        if (m_currentIndex == index && m_currentIndex != 0) {
            --m_currentIndex;
        }
        if (m_items.isEmpty()) {
            m_currentIndex = -1;
            emit currentChanged(m_currentIndex);
        }
        emit itemRemoved(index);
    }
}

int QWebStackedLayout::count() const
{
    return m_items.count();
}

int QWebStackedLayout::indexOf(QWebWebget* w) const
{
    int i = 0;
    QList<QWebLayoutItem*>::ConstIterator it = m_items.begin();
    QList<QWebLayoutItem*>::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if ((*it)->itemType() == QWebLayoutItem::WebgetItem) {
            if (static_cast<QWebWebgetItem*>(*it)->webget() == w) {
                return i;
            }
        }
        ++i;
    }
    return -1;
}

bool QWebStackedLayout::contains(QWebWebget* w) const
{
    return indexOf(w) != -1;
}

QWebLayoutItem* QWebStackedLayout::itemAt(int index) const
{
    if ((index < 0) || (index >= m_items.count())) {
        return NULL;
    }
    return m_items[index];
}

QWebLayoutItem* QWebStackedLayout::takeAt(int index)
{
    QWebLayoutItem* item = itemAt(index);
    removeItem(item);
    return item;
}

int QWebStackedLayout::currentIndex() const
{
    return m_currentIndex;
}

QWebLayoutItem* QWebStackedLayout::currentItem() const
{
    if (m_currentIndex != -1) {
        return m_items[m_currentIndex];
    }
    return NULL;
}

void QWebStackedLayout::render()
{
    if (m_currentIndex != -1) {
        m_items[m_currentIndex]->render();
    }
}

void QWebStackedLayout::setCurrentIndex(int index)
{
    if (index < 0) {
        index = 0;
    } else if (index >= m_items.count()) {
        index = m_items.count() - 1;
    }
    m_currentIndex = index;
    emit currentChanged(m_currentIndex);
}

void QWebStackedLayout::setCurrentItem(QWebLayoutItem* item)
{
    int index = m_items.indexOf(item);
    if (index != -1) {
        m_currentIndex = index;
        emit currentChanged(m_currentIndex);
    }
}

void QWebStackedLayout::updateParentWebget()
{
    QWebWebget* w = parentWebget();
    if (w != NULL) {
        w->update();
    }
}
