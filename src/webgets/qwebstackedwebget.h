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

#ifndef QWEBSTACKEDWEBGET_H
#define QWEBSTACKEDWEBGET_H

#include <QtWeb/QWebWebget>

class QWebStackedWebget : public QWebWebget
{
    Q_OBJECT

public:
    QWebStackedWebget(QWebWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QWebStackedWebget();

    int addWebget(QWebWebget* w);
    int count() const;
    int currentIndex() const;
    QWebWebget* currentWebget() const;
    int indexOf(QWebWebget* w) const;
    int insertWebget(int index, QWebWebget* w);
    void removeWebget(QWebWebget* w);
    QWebWebget* webget(int index) const;

public slots:
    void setCurrentIndex(int index);
    void setCurrentWebget(QWebWebget* w);

signals:
    void currentChanged(int index);
    void widgetRemoved(int index);
};

#endif // QWEBSTACKEDWEBGET_H
