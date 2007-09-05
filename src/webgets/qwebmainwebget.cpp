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

#include <QtWeb/QWebMainWebget>
#include <QtCore/QTextStream>
#include <QtWeb/QWebApplication>

QWebMainWebget::QWebMainWebget(QWebWebget* parent, const QString& webName) :
    QWebWebget(parent, webName)
{
    addStyleSheet("qwebmainwebget.css");
}

QWebMainWebget::~QWebMainWebget()
{
}

void QWebMainWebget::setTitle(const QString& title)
{
    m_title = title;
}

QString QWebMainWebget::title() const
{
    return m_title;
}

void QWebMainWebget::render()
{
    if (device() == NULL) {
        return;
    }
    QTextStream stream(device());

    QString jsDir(".");
    QString cssDir(".");
    QWebApplication* app = webApp();
    if (app != NULL) {
        jsDir = app->javascriptDir();
        cssDir = app->styleSheetDir();
    }
    stream << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
            << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
            << "<head>\n"
            << "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />\n"
            << "<title>" << title() << "</title>\n";

    QSet<QString> cssFiles = styleSheets();
    QSet<QString>::ConstIterator it = cssFiles.begin();
    QSet<QString>::ConstIterator itEnd = cssFiles.end();
    stream << "<link href=\"" << cssDir << "/qtweb.css\" rel=\"stylesheet\" type=\"text/css\" />\n";
    for (; it != itEnd; ++it) {
        stream << "<link href=\"" << cssDir << "/" << *it
                << "\" rel=\"stylesheet\" type=\"text/css\" />\n";
    }

    stream << "<script src=\"" << jsDir << "/prototype.js\" type=\"text/javascript\"></script>\n";
    QSet<QString> jsFiles = javascriptFiles();
    it = jsFiles.begin();
    itEnd = jsFiles.end();
    for (; it != itEnd; ++it) {
        stream << "<script src=\"" << jsDir << "/" << *it
                << "\" type=\"text/javascript\"></script>\n";
    }

    stream << "</head>\n<body class=\"" << webClass() << "\" id=\"" << webId() << "\">\n";
    stream.flush();

    renderContent();

    stream << "</body>\n</html>\n";
    stream.flush();
}
