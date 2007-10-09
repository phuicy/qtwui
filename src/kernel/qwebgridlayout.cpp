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

#include <QtWeb/QWebGridLayout>
#include <QtCore/QTextStream>
#include <QtWeb/QWebWebget>

QWebGridLayout::QWebGridLayout(QWebWebget* parent, Unit unit) :
    QWebLayout(parent, unit),
    m_count(0)
{
}

QWebGridLayout::QWebGridLayout(Unit unit) :
    QWebLayout(unit),
    m_count(0)
{
}

QWebGridLayout::~QWebGridLayout()
{
}

QWebLayout::LayoutType QWebGridLayout::type() const
{
    return GridLayout;
}

void QWebGridLayout::insertItem(QWebLayoutItem* item, int row, int column, int rowSpan, int columnSpan)
{
    if (item == NULL || row < 0 || column < 0 || rowSpan < 1 || columnSpan < 1) {
        return;
    }

    if (item->itemType() == QWebLayoutItem::LayoutItem) {
        static_cast<QWebLayout*>(item)->setParent(this);
    }

    expandTo(row + rowSpan, column + columnSpan);

    ++m_count;
    for (int i = row; i < row + rowSpan; ++i) {
        for (int j = column; j < column + columnSpan; ++j) {
            Item& current = m_items[i][j];
            delete current.m_item;
            if (i == row && j == column) {
                current.m_item = item;
                current.m_rowSpan = rowSpan;
                current.m_columnSpan = columnSpan;
            } else {
                current.m_item = NULL;
                current.m_rowSpan = 0;
                current.m_columnSpan = 0;
            }
        }
    }
}

void QWebGridLayout::insertWebget(QWebWebget* w, int row, int column, int rowSpan, int columnSpan)
{
    insertItem(new QWebWebgetItem(w), row, column, rowSpan, columnSpan);
}

void QWebGridLayout::insertStretch(int row, int column, int rowSpan, int columnSpan)
{
    insertItem(new QWebSpacerItem(), row, column, rowSpan, columnSpan);
}

void QWebGridLayout::removeItem(QWebLayoutItem* item)
{
    --m_count;
    QPair<int, int> c = coordsOf(item);
    if (c.first != -1 && c.second != -1) {
        Item& it = m_items[c.first][c.second];
        it.m_item = NULL;
        it.m_rowSpan = 0;
        it.m_columnSpan = 0;
    }
    reduce();
}

void QWebGridLayout::setRowSize(int row, int size)
{
    if (row >= 0 && row < m_rowSizes.count()) {
        if (size < 1) {
            size = 1;
        }
        m_rowSizes[row] = size;
    }
}

int QWebGridLayout::rowSize(int row)
{
    if (row >= 0 && row < m_rowSizes.count()) {
        return m_rowSizes[row];
    }
    return -1;
}

void QWebGridLayout::setColumnSize(int column, int size)
{
    if (column >= 0 && column < m_columnSizes.count()) {
        if (size < 1) {
            size = 1;
        }
        m_columnSizes[column] = size;
    }
}

int QWebGridLayout::columnSize(int column)
{
    if (column >= 0 && column < m_columnSizes.count()) {
        return m_columnSizes[column];
    }
    return -1;
}

int QWebGridLayout::rowCount() const
{
    return m_rowSizes.count();
}

int QWebGridLayout::columnCount() const
{
    return m_columnSizes.count();
}

int QWebGridLayout::count() const
{
    return m_count;
}

int QWebGridLayout::indexOf(QWebWebget* w) const
{
    int index = 0;
    ItemMatrix::ConstIterator rowIt = m_items.begin();
    ItemMatrix::ConstIterator rowItEnd = m_items.end();
    for (; rowIt != rowItEnd; ++rowIt) {
        ItemList::ConstIterator it = rowIt->begin();
        ItemList::ConstIterator itEnd = rowIt->end();
        for (; it != itEnd; ++it) {
            if (it->m_item != NULL) {
                if (it->m_item->itemType() == QWebLayoutItem::WebgetItem) {
                    if (static_cast<QWebWebgetItem*>(it->m_item)->webget() == w) {
                        return index;
                    }
                }
            }
            ++index;
        }
    }
    return -1;
}

QPair<int, int> QWebGridLayout::coordsOf(QWebLayoutItem* item) const
{
    int i = 0;
    int j = 0;
    ItemMatrix::ConstIterator rowIt = m_items.begin();
    ItemMatrix::ConstIterator rowItEnd = m_items.end();
    for (; rowIt != rowItEnd; ++rowIt) {
        ItemList::ConstIterator it = rowIt->begin();
        ItemList::ConstIterator itEnd = rowIt->end();
        for (; it != itEnd; ++it) {
            if (it->m_item == item) {
                return qMakePair(i, j);
            }
            ++j;
        }
        ++i;
    }
    return qMakePair(-1, -1);
}

bool QWebGridLayout::contains(QWebWebget* w) const
{
    ItemMatrix::ConstIterator rowIt = m_items.begin();
    ItemMatrix::ConstIterator rowItEnd = m_items.end();
    for (; rowIt != rowItEnd; ++rowIt) {
        ItemList::ConstIterator it = rowIt->begin();
        ItemList::ConstIterator itEnd = rowIt->end();
        for (; it != itEnd; ++it) {
            if (it->m_item != NULL) {
                switch (it->m_item->itemType()) {
                    case QWebLayoutItem::WebgetItem:
                        if (static_cast<QWebWebgetItem*>(it->m_item)->webget() == w) {
                            return true;
                        }
                        break;
                    case QWebLayoutItem::LayoutItem:
                        if (static_cast<QWebLayout*>(it->m_item)->contains(w)) {
                            return true;
                        }
                        break;
                    case QWebLayoutItem::SpacerItem:
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return false;
}

QWebLayoutItem* QWebGridLayout::itemAt(int index) const
{
    if (m_items.isEmpty()) {
        return NULL;
    }
    int row = index / m_items.count();
    int col = index % m_items.count();
    if (row >= 0 && row < m_items.count() && col >= 0 && col < m_items[row].count()) {
        return m_items[row][col].m_item;
    }
    return NULL;
}

QWebLayoutItem* QWebGridLayout::takeAt(int index)
{
    if (m_items.isEmpty()) {
        return NULL;
    }
    int row = index / m_items.count();
    int col = index % m_items.count();
    if (row >= 0 && row < m_items.count() && col >= 0 && col < m_items[row].count()) {
        Item& it = m_items[row][col];
        QWebLayoutItem* res = it.m_item;
        it.m_item = NULL;
        it.m_rowSpan = 0;
        it.m_columnSpan = 0;
        reduce();
        return res;
    }
    return NULL;
}

void QWebGridLayout::render()
{
    if (m_items.isEmpty()) {
        return;
    }

    QWebWebget* p = parentWebget();
    if (p == NULL) {
        return;
    }
    QIODevice* dev = p->device();

    QList<int>::ConstIterator intIt;
    QList<int>::ConstIterator intItEnd;

    int maxColSize = 0;
    if (unit() == RelativeStrength) {
        intIt = m_columnSizes.begin();
        intItEnd = m_columnSizes.end();
        for (; intIt != intItEnd; ++intIt) {
            maxColSize += *intIt;
        }
    }
    if (maxColSize == 0) {
        maxColSize = 1;
    }

    int maxRowSize = 0;
    if (unit() == RelativeStrength) {
        intIt = m_rowSizes.begin();
        intItEnd = m_rowSizes.end();
        for (; intIt != intItEnd; ++intIt) {
            maxRowSize += *intIt;
        }
    }
    if (maxRowSize == 0) {
        maxRowSize = 1;
    }

    QTextStream stream(dev);
    stream << "<table class=\"QWebGridLayout\"";
    if (spacing() >= 0) {
        stream << " cellpadding=\"" << spacing() << "\"";
    }
    stream << ">\n";
    QString value;

    ItemMatrix::Iterator rowIt = m_items.begin();
    ItemMatrix::Iterator rowItEnd = m_items.end();
    int rowIndex = 0;
    for (; rowIt != rowItEnd; ++rowIt) {
        if (unit() == RelativeStrength) {
            value = QString::number(((float) m_rowSizes[rowIndex] / (float) maxRowSize) * 100.0, 'f', 2);
        } else {
            value = QString::number(m_rowSizes[rowIndex]);
        }
        QString style = " style=\"height:" + value + unitToString() + ";";
        stream << "<tr class=\"QWebGridLayout\"" << style << "\">\n";
        ItemList::Iterator colIt = rowIt->begin();
        ItemList::Iterator colItEnd = rowIt->end();
        int colIndex = 0;
        for (; colIt != colItEnd; ++colIt) {
            if (colIt->m_item != NULL) {
                stream << "<td class=\"QWebGridLayout\"";
                if (colIt->m_rowSpan > 1) {
                    stream << " rowspan=\"" << colIt->m_rowSpan << "\"";
                }
                if (colIt->m_columnSpan > 1) {
                    stream << " colspan=\"" << colIt->m_columnSpan << "\"";
                }
                if (unit() == RelativeStrength) {
                    value = QString::number(((float) m_columnSizes[colIndex] / (float) maxColSize) * 100.0, 'f', 2);
                } else {
                    value = QString::number(m_columnSizes[colIndex]);
                }
                style += "width:" + value + unitToString() + ";";
                stream << style << "\">\n";
                stream.flush();
                colIt->m_item->render();
                stream.flush();
                stream << "</td>\n";
            }
            ++colIndex;
        }
        stream << "</tr>\n";
        ++rowIndex;
    }
    stream << "</table>\n";
}

void QWebGridLayout::expandTo(int rows, int columns)
{
    ItemList line;
    Item item;
    int nCols = columnCount();
    int nRows = rowCount();
    for (int col = 0; col < nCols; ++col) {
        line.append(item);
    }

    for (int row = nRows; row < rows; ++row) {
        m_items.append(line);
        m_rowSizes.append(1);
    }

    nRows = rowCount();
    for (int col = nCols; col < columns; ++col) {
        Item item;
        for (int row = 0; row < nRows; ++row) {
            m_items[row].append(item);
        }
        m_columnSizes.append(1);
    }
}

void QWebGridLayout::reduce()
{
    if (m_items.isEmpty()) {
        return;
    }

    bool stop = false;
    while (!stop) {
        ItemList& l = m_items.last();
        ItemList::ConstIterator it = l.begin();
        ItemList::ConstIterator itEnd = l.end();
        for (; it != itEnd && !stop; ++it) {
            stop = it->m_item != NULL;
        }
        if (!stop) {
            m_items.removeLast();
            m_rowSizes.removeLast();
        }
        stop |= m_items.isEmpty();
    }
    stop = false;
    int col = columnCount() - 1;
    int rows = rowCount();
    while (!stop && col != -1) {
        for (int row = 0; row < rows; ++row) {
            stop = m_items[row][col].m_item != NULL;
        }
        if (!stop) {
            for (int row = 0; row < rows; ++row) {
                m_items[row].removeLast();
            }
            m_columnSizes.removeLast();
        }
        stop |= --col == -1;
    }
}
