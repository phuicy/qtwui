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

#include <QtWeb/QWebBoxLayout>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtWeb/QWebWebget>

QWebBoxLayout::QWebBoxLayout(QWebWebget* parent, Unit unit) :
    QWebLayout(parent, unit)
{
}

QWebBoxLayout::QWebBoxLayout(Unit unit) :
    QWebLayout(unit)
{
}

QWebBoxLayout::~QWebBoxLayout()
{
}

void QWebBoxLayout::addItem(QWebLayoutItem* item, int size)
{
    insertItem(m_items.count(), item, size);
}

void QWebBoxLayout::addWebget(QWebWebget* w, int size)
{
    insertWebget(m_items.count(), w, size);
}

void QWebBoxLayout::addLayout(QWebLayout* l, int size)
{
    insertLayout(m_items.count(), l, size);
}

void QWebBoxLayout::addStretch(int size)
{
    insertStretch(m_items.count(), size);
}

void QWebBoxLayout::insertItem(int index, QWebLayoutItem* item, int size)
{
    if (item->itemType() == QWebLayoutItem::LayoutItem) {
        static_cast<QWebLayout*>(item)->setParent(this);
    }
    m_items.insert(index, qMakePair(item, size));
}

void QWebBoxLayout::insertWebget(int index, QWebWebget* w, int size)
{
    insertItem(index, new QWebWebgetItem(w), size);
}

void QWebBoxLayout::insertLayout(int index, QWebLayout* l, int size)
{
    insertItem(index, l, size);
}

void QWebBoxLayout::insertStretch(int index, int size)
{
    insertItem(index, new QWebSpacerItem(), size);
}

void QWebBoxLayout::removeItem(QWebLayoutItem* item)
{
    ItemList::Iterator it = m_items.begin();
    ItemList::Iterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if (it->first == item) {
            m_items.erase(it);
            delete item;
            break;
        }
    }
}

int QWebBoxLayout::count() const
{
    return m_items.count();
}

int QWebBoxLayout::indexOf(QWebWebget* w) const
{
    int index = 0;
    ItemList::ConstIterator it = m_items.begin();
    ItemList::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        if (it->first->itemType() == QWebLayoutItem::WebgetItem) {
            if (static_cast<QWebWebgetItem*>(it->first)->webget() == w) {
                return index;
            }
            ++index;
        }
    }
    return -1;
}

bool QWebBoxLayout::contains(QWebWebget* w) const
{
    ItemList::ConstIterator it = m_items.begin();
    ItemList::ConstIterator itEnd = m_items.end();
    for (; it != itEnd; ++it) {
        switch (it->first->itemType()) {
            case QWebLayoutItem::WebgetItem:
                if (static_cast<QWebWebgetItem*>(it->first)->webget() == w) {
                    return true;
                }
                break;
            case QWebLayoutItem::LayoutItem:
                if (static_cast<QWebLayout*>(it->first)->contains(w)) {
                    return true;
                }
                break;
            case QWebLayoutItem::SpacerItem:
                break;
            default:
                break;
        }
    }
    return false;
}

QWebLayoutItem* QWebBoxLayout::itemAt(int index) const
{
    if (index >= 0 && index < m_items.count()) {
        return m_items[index].first;
    }
    return NULL;
}

QWebLayoutItem* QWebBoxLayout::takeAt(int index)
{
    QWebLayoutItem* item = NULL;
    if (index >= 0 && index < m_items.count()) {
        item = m_items[index].first;
        m_items.removeAt(index);
    }
    return item;
}

void QWebBoxLayout::itemSize(int index, int size)
{
    if (index >= 0 && index < m_items.count()) {
        m_items[index].second = size;
    }
}

QPair<QWebLayoutItem*, int> QWebBoxLayout::boxItemAt(int index) const
{
    return m_items[index];
}

QWebHBoxLayout::QWebHBoxLayout(QWebWebget* parent, Unit unit) :
    QWebBoxLayout(parent, unit)
{
}

QWebHBoxLayout::QWebHBoxLayout(Unit unit) :
    QWebBoxLayout(unit)
{
}

QWebHBoxLayout::~QWebHBoxLayout()
{
}

QWebBoxLayout::LayoutType QWebHBoxLayout::type() const
{
    return HBoxLayout;
}

void QWebHBoxLayout::render()
{
    if (count() != 0) {
        QWebWebget* p = parentWebget();
        if (p == NULL) {
            return;
        }
        QIODevice* dev = p->device();

        QTextStream stream(dev);
        stream << "<table class=\"QWebLayout\"";
        if (spacing() >= 0) {
            stream << " cellspacing=\"" << spacing() << "\"";
        }
        stream << ">\n";
        stream << "<tr class=\"QWebLayout\">\n";
        int max = 0;
        if (unit() == RelativeStrength) {
            for (int i = 0; i < count(); ++i) {
                max += boxItemAt(i).second;
            }
        }
        if (max == 0) {
            max = 1;
        }
        for (int i = 0; i < count(); ++i) {
            QPair<QWebLayoutItem*, int> boxItem = boxItemAt(i);
            stream << "<td class=\"QWebLayout\"";
            if (boxItem.second != 0) {
                QString value;
                if (unit() == RelativeStrength) {
                    value = QString::number(((float) boxItem.second / (float) max) * 100.0, 'f', 2);
                } else {
                    value = QString::number(boxItem.second);
                }
                stream << " style=\"width:" << value << unitToString() << ";\"";
            }
            stream << ">\n";
            stream.flush();
            boxItem.first->render();
            stream.flush();
            stream << "</td>\n";
        }
        stream << "</tr>\n";
        stream << "</table>\n";
        stream.flush();
    }
}

QWebVBoxLayout::QWebVBoxLayout(QWebWebget* parent, Unit unit) :
        QWebBoxLayout(parent, unit)
{
}

QWebVBoxLayout::QWebVBoxLayout(Unit unit) :
    QWebBoxLayout(unit)
{
}

QWebVBoxLayout::~QWebVBoxLayout()
{
}

QWebBoxLayout::LayoutType QWebVBoxLayout::type() const
{
    return VBoxLayout;
}

void QWebVBoxLayout::render()
{
    if (count() != 0) {
        QWebWebget* p = parentWebget();
        if (p == NULL) {
            return;
        }
        QIODevice* dev = p->device();

        QTextStream stream(dev);
        stream << "<table class=\"QWebLayout\"";
        if (spacing() >= 0) {
            stream << " cellspacing=\"" << spacing() << "\"";
        }
        stream << ">\n";
        int max = 0;
        if (unit() == RelativeStrength) {
            for (int i = 0; i < count(); ++i) {
                max += boxItemAt(i).second;
            }
        }
        if (max == 0) {
            max = 1;
        }
        for (int i = 0; i < count(); ++i) {
            QPair<QWebLayoutItem*, int> boxItem = boxItemAt(i);
            stream << "<tr class=\"QWebLayout\"";
            if (boxItem.second != 0) {
                QString value;
                if (unit() == RelativeStrength) {
                    value = QString::number(((float) boxItem.second / (float) max) * 100.0, 'f', 2);
                } else {
                    value = QString::number(boxItem.second);
                }
                stream << " style=\"height:" << value << unitToString() << ";\"";
            }
            stream << ">\n<td class=\"QWebLayout\">\n";
            stream.flush();
            boxItem.first->render();
            stream.flush();
            stream << "</td>\n";
            stream << "</tr>\n";
        }
        stream << "</table>\n";
        stream.flush();
    }
}
