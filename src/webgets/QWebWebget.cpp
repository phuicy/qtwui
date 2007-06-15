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

#include "QWebWebget.h"
#include <QTextStream>
#include <QIODevice>
#include "QWebApplication.h"

QWebWebget::QWebWebget(QWebWebget* parent, const QString& webName) :
    QObject(parent),
    m_webApp(NULL)
{
    setWebName(webName);
}

QWebWebget::~QWebWebget()
{
}

void QWebWebget::setWebName(const QString& webName)
{
    m_webName = webName;
}

QString QWebWebget::webName() const
{
    if (m_webName.isEmpty()) {
        return objectName();
    }
    return m_webName;
}

QString QWebWebget::webPath() const
{
    QWebWebget* w = qobject_cast<QWebWebget*>(parent());
    if (w != NULL) {
        return w->webPath() + "." + webName();
    }
    return webName();
}

void QWebWebget::setWebId(const QString& webId)
{
    m_webId = webId;
}

QString QWebWebget::webId() const
{
    if (m_webId.isEmpty()) {
        return webPath(); // Compute SHA1 of webPath available in Qt 4.3
    }
    return m_webId;
}

void QWebWebget::setWebClass(const QString& webClass)
{
    m_webClass = webClass;
}

QString QWebWebget::webClass() const
{
    if (m_webClass.isEmpty()) {
        return metaObject()->className();
    }
    return m_webClass;
}

QString QWebWebget::invoke(const QString& call, const QWebParameters& parameters, QIODevice* dev)
{
    int sep = call.indexOf('.');
    if (sep == -1) {
        sep = call.length();
    }
    QString thisPath = call.mid(0, sep);
    QString nextPath = call.mid(sep + 1);
    QString mimeType;

    if (thisPath == webName()) {
        if (nextPath.isEmpty()) {
            render(mimeType, parameters, dev);
            return mimeType;
        } else {
            QListIterator<QObject*> it(children());
            QWebWebget* w = NULL;

            while (it.hasNext()) {
                w = qobject_cast<QWebWebget*>(it.next());
                if (w != NULL) {
                    mimeType = w->invoke(nextPath, parameters, dev);
                    if (!mimeType.isNull()) {
                        return mimeType;
                    }
                }
            }
            if (QMetaObject::invokeMethod(this, nextPath.toAscii(), QArgument<QString>("QString&", mimeType), QArgument<QWebParameters>("const QWebParameters&", parameters), Q_ARG(QIODevice*, dev))) {
                return mimeType;
            }
        }
    }

    return QString::null;
}

QString QWebWebget::startTag(const QString& tag)
{
    QString wc;
    QString wid;
    if (!webClass().isEmpty()) {
        wc = QString(" class=\"%1\"").arg(webClass());
    }
    if (!webId().isEmpty()) {
        wid = QString(" id=\"%1\"").arg(webId());
    }
    return QString("<%1%2%3>\n").arg(tag).arg(wc).arg(wid);
}

QString QWebWebget::endTag(const QString& tag)
{
    return QString("</%1>\n").arg(tag);
}

void QWebWebget::addStyleSheet(const QString& css)
{
    m_cssFiles.insert(css);
}

void QWebWebget::addJavascriptFile(const QString& js)
{
    m_jsFiles.insert(js);
}

QSet<QString> QWebWebget::styleSheets() const
{
    QSet<QString> res = m_cssFiles;

    QListIterator<QObject*> it(children());
    QWebWebget* w = NULL;
    while (it.hasNext()) {
        w = qobject_cast<QWebWebget*>(it.next());
        if (w != NULL) {
        	res.unite(w->styleSheets());
        }
    }
    return res;
}

QSet<QString> QWebWebget::javascriptFiles() const
{
    QSet<QString> res = m_jsFiles;

    QListIterator<QObject*> it(children());
    QWebWebget* w = NULL;
    while (it.hasNext()) {
        w = qobject_cast<QWebWebget*>(it.next());
        if (w != NULL) {
        	res.unite(w->javascriptFiles());
        }
    }
    return res;
}

QWebApplication* QWebWebget::webApp() const
{
    if (m_webApp != NULL) {
        return m_webApp;
    }
    for(QObject* o = parent(); o != NULL; o = o->parent()) {
        const_cast<QWebWebget*>(this)->m_webApp = qobject_cast<QWebApplication*>(o);
        if (m_webApp != NULL) {
            return m_webApp;
        }
    }
    return NULL;
}

void QWebWebget::render(QString& mimeType, const QWebParameters& parameters, QIODevice* dev)
{
    mimeType = "text/html";
    render(parameters, dev);
}

void QWebWebget::render(const QWebParameters& parameters, QIODevice* dev)
{
    QTextStream stream(dev);
    QListIterator<QObject*> it(children());
    QWebWebget* w;

    beforeRenderChildren(parameters, stream);
    stream.flush();
    while (it.hasNext()) {
        w = qobject_cast<QWebWebget*>(it.next());
        if (w != NULL) {
            renderChild(parameters, stream, w);
            stream.flush();
        }
    }
    afterRenderChildren(parameters, stream);
    stream.flush();
}

void QWebWebget::beforeRenderChildren(const QWebParameters& parameters, QTextStream& stream)
{
    Q_UNUSED(parameters);
    stream << startTag("div");
}

void QWebWebget::renderChild(const QWebParameters& parameters, QTextStream& stream, QWebWebget* child)
{
    child->render(parameters, stream.device());
}

void QWebWebget::afterRenderChildren(const QWebParameters& parameters, QTextStream& stream)
{
    Q_UNUSED(parameters);
    stream << endTag("div");
}

void QWebWebget::setWebApp(QWebApplication* app)
{
    m_webApp = app;
}
