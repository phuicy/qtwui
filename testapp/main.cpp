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

#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include "QWebApplicationServer.h"
#include "QWebApplication.h"
#include "QWebMainWebget.h"
#include "TestWebget.h"

void printUsage()
{
    QTextStream out(stdout);
    out << "Usage : qwebhttpserver [options]\n";
    out << "Options :\n";
    out << "          -p --port : listening port\n";
}

QWebApplication* webMain(const QString& sessionId, const QStringList& args)
{
    Q_UNUSED(args);

    QWebApplication* webApp = new QWebApplication(sessionId);
    webApp->setJavascriptDir("javascript");
    webApp->setStyleSheetsDir("stylesheets");
    QWebMainWebget* mw = new QWebMainWebget(NULL, "mw");
    mw->setTitle("QtWeb Test");
    TestWebget* test1 = new TestWebget(mw, "test1");
    TestWebget* test2 = new TestWebget(test1, "test2");
    TestWebget* test3 = new TestWebget(test1, "test3");
    TestWebget* test4 = new TestWebget(test2, "test4");
    webApp->setMainWebget(mw);

    return webApp;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QWebApplicationServer webAppServer(webMain);

    QString option = QCoreApplication::arguments().at(1);
    if ((option == "-p") || (option == "--port")) {
        bool ok;
        quint16 port = QString(argv[2]).toInt(&ok);
        if (ok) {
            webAppServer.setBuiltInServerPort(port);
        } else {
            printUsage();
            return -1;
        }
    } else {
        printUsage();
        return -1;
    }
    webAppServer.exec();
    return app.exec();
}
