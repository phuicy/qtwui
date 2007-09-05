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

#include <QtWeb/QWebLabel>
#include <QtGui/QImage>
#include <QtWeb/QWebTag>

QWebLabel::QWebLabel(QWebWebget* parent, const QString& webName) :
    QWebWebget(parent, webName),
    m_imageType(PngImage),
    m_image(NULL)
{
}

QWebLabel::~QWebLabel()
{
    delete m_image;
}

QString QWebLabel::text() const
{
    return m_text;
}

QString QWebLabel::imageFile() const
{
    return m_imageFile;
}

const QImage* QWebLabel::image() const
{
    return m_image;
}

QWebLabel::ImageType QWebLabel::imageType() const
{
    return m_imageType;
}

void QWebLabel::setImageType(ImageType p)
{
    m_imageType = p;
}

void QWebLabel::clear()
{
    delete m_image;
    m_image = NULL;
    m_text = QString::null;
    m_imageFile = QString::null;
}

void QWebLabel::setNum(int num)
{
    clear();
    m_text = QString::number(num);
}

void QWebLabel::setNum(double num)
{
    clear();
    m_text = QString::number(num);
}

void QWebLabel::setImageFile(const QString& f)
{
    clear();
    m_imageFile = f;
}

void QWebLabel::setImage(const QImage& p)
{
    clear();
    m_image = new QImage(p);
}

void QWebLabel::setText(const QString& t)
{
    clear();
    m_text = t;
}

void QWebLabel::image(QString& mimeType)
{
    QIODevice* dev = device();
    if (dev == NULL) {
        return;
    }
    if (m_image != NULL) {
        switch (m_imageType) {
            case JpegImage:
                m_image->save(dev, "JPG");
                mimeType = "image/jpeg";
                break;
            case PngImage:
                m_image->save(dev, "PNG");
                mimeType = "image/png";
                break;
        }
    }
}

void QWebLabel::render()
{
    if (m_image != NULL) {
        QWebTag tag(this, "img", false);
        tag.setAttribute("src", QString("?call=") + webPath() + ".image");
        tag.setAttribute("width", QString::number(m_image->width()) + "px");
        tag.setAttribute("height", QString::number(m_image->height()) +  "px");
    } else if (!m_imageFile.isEmpty()) {
        QWebTag tag(this, "img", false);
        tag.setAttribute("src", m_imageFile);
    } else if (!m_text.isNull()) {
        QWebTag tag(this, "p");
        tag.setText(m_text);
    }
}
