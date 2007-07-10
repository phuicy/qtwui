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

#include <QtWeb/QWebLayout>
#include <QtWeb/QWebWebget>

QWebLayout::QWebLayout(QWebWebget* parent, Unit unit) :
    m_parent(parent),
    m_enabled(true),
    m_spacing(4),
    m_unit(unit)
{
    if (m_parent != NULL) {
        m_parent->setLayout(this);
    }
}

QWebLayout::QWebLayout(Unit unit) :
    m_parent(NULL),
    m_enabled(true),
    m_spacing(4),
    m_unit(unit)
{
}

QWebLayout::~QWebLayout()
{
}

void QWebLayout::removeWebget(QWebWebget* w)
{
    int i = indexOf(w);
    if (i != -1) {
        removeItem(itemAt(i));
    }
}

QWebWebget* QWebLayout::parentWebget() const
{
    return m_parent;
}

bool QWebLayout::isEnabled() const
{
    return m_enabled;
}

void QWebLayout::setEnabled(bool enable)
{
    m_enabled = enable;
}

void QWebLayout::setSpacing(int s)
{
    m_spacing = s;
}

int QWebLayout::spacing() const
{
    return m_spacing;
}

QWebLayoutItem::ItemType QWebLayout::itemType() const
{
    return LayoutItem;
}


QWebLayout::Unit QWebLayout::unit() const
{
    return m_unit;
}

void QWebLayout::setUnit(QWebLayout::Unit u)
{
    m_unit = u;
}

QString QWebLayout::unitToString() const
{
    switch (m_unit) {
        case Em:
            return "em";
            break;
        case Pixel:
            return "px";
            break;
        case RelativeStrength:
            return "%";
            break;
    }
    return QString::null;
}

