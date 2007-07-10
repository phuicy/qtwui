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

#include "TestWebget.h"
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtWeb/QWebLink>
#include <QtWeb/QWebApplication>
#include <QtWeb/QWebHBoxLayout>
#include <QtWeb/QWebVBoxLayout>

TestWebget::TestWebget(QWebWebget* parent, const QString& webName) :
    QWebWebget(parent, webName),
    m_items(0)
{
    qDebug("YYYYYYYYEEEEEEEEEHHHHHHHHHHHHHHAAAAAAAAAAAAHHHHH !!!!");
    QWebLink* link = new QWebLink(this, "link", "Test", this, Qt::AjaxInsertionReplace);
    connect(link, SIGNAL(clicked(QString&, const QWebParameters&, QIODevice*)), this, SLOT(linkClicked(QString&, const QWebParameters&, QIODevice*)));
    if (webName == "test1") {
        QWebHBoxLayout* hbox = new QWebHBoxLayout(this);
        hbox->addWebget(new TestWebget(this, "test2"), 1);
        QWebVBoxLayout* vbox = new QWebVBoxLayout(QWebLayout::Em);
        hbox->addLayout(vbox, 2);
        vbox->addWebget(new TestWebget(this, "test3"), 30);
        vbox->addWebget(new TestWebget(this, "test4"));
    }
    link->addParameter("toto", "toto-param");
    link->addParameter("toto2", "toto-param-second");
}

TestWebget::~TestWebget()
{
    qDebug("AAAAAAAAAAAAAAAAAAAARRRRRGGGGGGGGGGGG !!!!");
}
void TestWebget::beforeRenderChildren(const QWebParameters& parameters, QTextStream& stream)
{
    QWebWebget::beforeRenderChildren(parameters, stream);
    Q_UNUSED(parameters);
/*    QString str("<script type=\"text/javascript\">function test1update(){new Ajax.Updater('testajax', '?call=");
    str += webPath() + ".ajaxcall', { method: 'get', insertion: Insertion.Bottom } );}</script>\n<a href=\"javascript:test1update()\">Add</a><ul id=\"testajax\"></ul>";
    stream << str;*/
}

void TestWebget::afterRenderChildren(const QWebParameters& parameters, QTextStream& stream)
{
    QWebWebget::afterRenderChildren(parameters, stream);
    Q_UNUSED(parameters);
    Q_UNUSED(stream);
}

void TestWebget::coucou(QString& mimeType, const QWebParameters& parameters, QIODevice* dev)
{
    Q_UNUSED(parameters);
    mimeType = "text/plain";
    QString s("Hello World from %1 method !");
    s = s.arg(webPath());
    dev->write(s.toAscii(), s.length());
}

void TestWebget::empty(QString& mimeType, const QWebParameters& parameters, QIODevice* dev)
{
    mimeType = "text/html";
    Q_UNUSED(parameters);
    Q_UNUSED(dev);
}

void TestWebget::ajaxcall(QString& mimeType, const QWebParameters& parameters, QIODevice* dev)
{
    mimeType = "text/html";
    Q_UNUSED(parameters);
    qDebug("AJAX Call !!!");
    QString s1("<ul class=\"testajax\">");
    QString s2("<li>Item %1</li>");
    QString s3("</ul>");

    dev->write(s2.arg(++m_items).toAscii(), s2.length());
    //dev->write(s1.toAscii(), s1.length());
    /*++m_items;
    for (int i = 0; i < m_items; ++i) {
        dev->write(s2.toAscii(), s2.length());
    }*/
    //dev->write(s3.toAscii(), s3.length());
}

void TestWebget::linkClicked(QString& mimeType, const QWebParameters& parameters, QIODevice* dev)
{
    mimeType = "text/plain";
    QTextStream stream(dev);
    stream << "coucou " << m_items << " " << webApp()->sessionId() << " " << parameters["toto"] << " " << parameters["toto2"] << "<br />";
    m_items = m_items + 1;
}
