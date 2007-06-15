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

#ifndef QWEBWEBGET_H
#define QWEBWEBGET_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QSet>
#include "QWebParameters.h"

class QIODevice;
class QTextStream;
class QWebApplication;

class QWebWebget : public QObject
{
    Q_OBJECT

public:
    QWebWebget(QWebWebget* parent = NULL, const QString& webName = QString::null);
    virtual ~QWebWebget();

    void setWebName(const QString& webName);
    QString webName() const;
    QString webPath() const;
    void setWebId(const QString& webId);
    QString webId() const;
    void setWebClass(const QString& webClass);
    QString webClass() const;
    virtual QString invoke(const QString& call, const QWebParameters& parameters, QIODevice* dev);
    virtual QString startTag(const QString& tag);
    virtual QString endTag(const QString& tag);
    void addStyleSheet(const QString& css);
    void addJavascriptFile(const QString& js);
    QSet<QString> styleSheets() const;
    QSet<QString> javascriptFiles() const;
    QWebApplication* webApp() const;

public slots:
    void render(QString& mimeType, const QWebParameters& parameters, QIODevice* dev);

protected:
    virtual void render(const QWebParameters& parameters, QIODevice* dev);
    virtual void beforeRenderChildren(const QWebParameters& parameters, QTextStream& stream);
    virtual void renderChild(const QWebParameters& parameters, QTextStream& stream, QWebWebget* child);
    virtual void afterRenderChildren(const QWebParameters& parameters, QTextStream& stream);

private:
    void setWebApp(QWebApplication* app);

private:
    QString m_webName;
    QString m_webId;
    QString m_webClass;
    QWebApplication* m_webApp;
    QSet<QString> m_jsFiles;
    QSet<QString> m_cssFiles;

    friend class QWebApplication;
};

#endif // QWEBWEBGET_H
