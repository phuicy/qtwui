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

#include <QtCore/QObject>
#include <QtWeb/QWebGlobal>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtGui/QColor>

class QIODevice;
class QTextStream;
class QWebApplication;
class QWebLayout;

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
    virtual QString invoke(const QString& call);
    void addStyleSheet(const QString& css);
    void addJavascriptFile(const QString& js);
    QSet<QString> styleSheets() const;
    QSet<QString> javascriptFiles() const;
    QWebApplication* webApp() const;
    void setLayout(QWebLayout* l);
    QWebLayout* layout() const;
    QIODevice* device() const;
    void setStyleItem(const QString& item, const QString& value);
    QString styleItem(const QString& item) const;
    void setBorderWidth(int w);
    int borderWidth() const;
    void setBorderColor(const QColor& c);
    QColor borderColor() const;
    void setBackgroundColor(const QColor& c);
    QColor backgroundColor() const;
    void setBorderStyle(Qt::QWebBorderStyle s);
    Qt::QWebBorderStyle borderStyle() const;
    void setTextColor(const QColor& c);
    QColor textColor() const;
    void setTextAlignment(const Qt::Alignment a);
    Qt::Alignment textAlignment() const;

public slots:
    void render(QString& mimeType);

protected:
    virtual void render();
    virtual void renderContent();

private:
    void setWebApp(QWebApplication* app);

private:
    QString m_webName;
    QString m_webId;
    QString m_webClass;
    QWebApplication* m_webApp;
    QSet<QString> m_jsFiles;
    QSet<QString> m_cssFiles;
    QWebLayout* m_layout;
    QHash<QString, QString> m_styleItems;

    friend class QWebApplication;
    friend class QWebLayout;
    friend class QWebWebgetItem;
    friend class QWebTag;
};

#endif // QWEBWEBGET_H
