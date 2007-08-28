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

#ifndef QWEBLAYOUT_H
#define QWEBLAYOUT_H

#include <QtCore/QObject>
#include <QtWeb/QWebLayoutItem>

class QWebParameters;
class QIODevice;

class QWebLayout : public QObject, public QWebLayoutItem
{
    Q_OBJECT
public:
    enum LayoutType {
        HBoxLayout,
        VBoxLayout,
        GridLayout
    };
    enum Unit {
        Em,
        Pixel,
        RelativeStrength
    };

public:
    QWebLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebLayout(Unit unit = RelativeStrength);
    QWebLayout();
    virtual ~QWebLayout();
    QWebWebget* parentWebget() const;
    virtual LayoutType type() const = 0;
    virtual void removeItem(QWebLayoutItem* item) = 0;
    void removeWebget(QWebWebget* w);
    virtual int count() const = 0;
    virtual int indexOf(QWebWebget* w) const = 0;
    virtual bool contains(QWebWebget* w) const = 0;
    virtual QWebLayoutItem* itemAt(int index) const = 0;
    virtual QWebLayoutItem* takeAt(int index) = 0;
    bool isEnabled() const;
    void setEnabled(bool enable);
    void setSpacing(int s);
    int spacing() const;
    ItemType itemType() const;
    virtual void render() = 0;
    Unit unit() const;
    void setUnit(Unit u);
    QString unitToString() const;

private:
    bool m_enabled;
    int m_spacing;
    Unit m_unit;

    friend class QWebWebget;
};

#endif // QWEBLAYOUT_H
