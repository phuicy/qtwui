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

#ifndef QWEBBOXLAYOUT_H
#define QWEBBOXLAYOUT_H

#include <QtWeb/QWebLayout>
#include <QtCore/QList>
#include <QtCore/QPair>

class QWebBoxLayout : public QWebLayout
{
public:
    QWebBoxLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebBoxLayout(Unit unit = RelativeStrength);
    virtual ~QWebBoxLayout();
    virtual void addItem(QWebLayoutItem* item, int size = 0);
    void addWebget(QWebWebget* w, int size = 0);
    void addLayout(QWebLayout* l, int size = 0);
    void addStretch(int size = 0);
    virtual void insertItem(int index, QWebLayoutItem* item, int size = 0);
    void insertWebget(int index, QWebWebget* w, int size = 0);
    void insertLayout(int index, QWebLayout* l, int size = 0);
    void insertStretch(int index, int size = 0);
    virtual void removeItem(QWebLayoutItem* item);
    virtual int count() const;
    virtual int indexOf(QWebWebget* w) const;
    virtual bool contains(QWebWebget* w) const;
    virtual QWebLayoutItem* itemAt(int index) const;
    virtual QWebLayoutItem* takeAt(int index);
    void itemSize(int index, int size);

protected:
    QPair<QWebLayoutItem*, int> boxItemAt(int index) const;

private:
    typedef QList<QPair<QWebLayoutItem*, int> > ItemList;
    ItemList m_items;
};

class QWebHBoxLayout : public QWebBoxLayout
{
public:
    QWebHBoxLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebHBoxLayout(Unit unit = RelativeStrength);
    virtual ~QWebHBoxLayout();
    virtual LayoutType type() const;
    virtual void render(const QWebParameters& parameters, QIODevice* dev);
};

class QWebVBoxLayout : public QWebBoxLayout
{
public:
    QWebVBoxLayout(QWebWebget* parent, Unit unit = RelativeStrength);
    QWebVBoxLayout(Unit unit = RelativeStrength);
    virtual ~QWebVBoxLayout();
    virtual LayoutType type() const;
    virtual void render(const QWebParameters& parameters, QIODevice* dev);
};

#endif // QWEBBOXLAYOUT_H
