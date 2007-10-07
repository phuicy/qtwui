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

#include <QtWeb/QWebWebget>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtCore/QEvent>
#include <QtWeb/QWebApplication>
#include <QtWeb/QWebLayout>
#include <QtWeb/QWebTag>

QWebWebget::QWebWebget(QWebWebget* parent, const QString& webName) :
    QObject(parent),
    m_webApp(NULL),
    m_layout(NULL)
{
    if (parent != NULL) {
        parent->update();
    }
    setWebName(webName);
    addStyleSheet("qwebwebget.css");
}

QWebWebget::~QWebWebget()
{
    QWebWebget* p = qobject_cast<QWebWebget*>(parent());
    if (p != NULL) {
        if (p->layout() != NULL) {
            p->layout()->removeWebget(this);
        }
    }
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

QString QWebWebget::invoke(const QString& call)
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
            render(mimeType);
            return mimeType;
        } else {
            QListIterator<QObject*> it(children());
            QWebWebget* w = NULL;

            while (it.hasNext()) {
                w = qobject_cast<QWebWebget*>(it.next());
                if (w != NULL) {
                    mimeType = w->invoke(nextPath);
                    if (!mimeType.isNull()) {
                        return mimeType;
                    }
                }
            }
            if (QMetaObject::invokeMethod(this, nextPath.toAscii(), QArgument<QString>("QString&", mimeType))) {
                return mimeType;
            }
        }
    }

    return QString::null;
}

void QWebWebget::addStyleSheet(const QString& css)
{
    m_cssFiles.insert(css);
}

void QWebWebget::addJavaScript(const QString& js)
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

void QWebWebget::setLayout(QWebLayout* l)
{
    delete m_layout;
    m_layout = l;
    if (m_layout != NULL) {
        m_layout->setParent(this);
    }
}

QWebLayout* QWebWebget::layout() const
{
    return m_layout;
}

QIODevice* QWebWebget::device() const
{
    return webApp()->device();
}

void QWebWebget::setStyleItem(const QString& item, const QString& value)
{
    m_styleItems[item] = value;
}

QString QWebWebget::styleItem(const QString& item) const
{
    QHash<QString, QString>::ConstIterator it = m_styleItems.find(item);
    if (it == m_styleItems.end()) {
        return QString::null;
    }
    return it.value();
}

void QWebWebget::setBorderWidth(int w)
{
    setStyleItem("border-width", QString::number(w));
}

int QWebWebget::borderWidth() const
{
    QString s = styleItem("border-width");
    bool ok = false;
    int w = s.toInt(&ok);
    if (!ok) {
        return 0;
    }
    return w;
}

void QWebWebget::setBorderColor(const QColor& c)
{
    setStyleItem("border-color", c.name());
}

QColor QWebWebget::borderColor() const
{
    return styleItem("border-width");
}

void QWebWebget::setBackgroundColor(const QColor& c)
{
    setStyleItem("background-color", c.name());
}

QColor QWebWebget::backgroundColor() const
{
    return styleItem("background-color");
}

void QWebWebget::setBorderStyle(Qt::QWebBorderStyle s)
{
    switch (s) {
        case Qt::NoneStyle:
            setStyleItem("border-style", "none");
            break;
        case Qt::HiddenStyle:
            setStyleItem("border-style", "hidden");
            break;
        case Qt::DottedStyle:
            setStyleItem("border-style", "dotted");
            break;
        case Qt::DashedStyle:
            setStyleItem("border-style", "dashed");
            break;
        case Qt::SolidStyle:
            setStyleItem("border-style", "solid");
            break;
        case Qt::DoubleStyle:
            setStyleItem("border-style", "double");
            break;
        case Qt::GrooveStyle:
            setStyleItem("border-style", "groove");
            break;
        case Qt::RidgeStyle:
            setStyleItem("border-style", "ridge");
            break;
        case Qt::InsetStyle:
            setStyleItem("border-style", "inset");
            break;
        case Qt::OutsetStyle:
            setStyleItem("border-style", "outset");
            break;
        default:
            setStyleItem("border-style", "none");
            break;
    }
}

Qt::QWebBorderStyle QWebWebget::borderStyle() const
{
    QString s = styleItem("border-style");
    if (s == "none") {
        return Qt::NoneStyle;
    } else if (s == "hidden") {
        return Qt::HiddenStyle;
    } else if (s == "dotted") {
        return Qt::DottedStyle;
    } else if (s == "dashed") {
        return Qt::DashedStyle;
    } else if (s == "solid") {
        return Qt::SolidStyle;
    } else if (s == "double") {
        return Qt::DoubleStyle;
    } else if (s == "groove") {
        return Qt::GrooveStyle;
    } else if (s == "ridge") {
        return Qt::RidgeStyle;
    } else if (s == "inset") {
        return Qt::InsetStyle;
    } else if (s == "outset") {
        return Qt::OutsetStyle;
    }
    return Qt::NoneStyle;
}

void QWebWebget::setTextColor(const QColor& c)
{
    setStyleItem("color", c.name());
}

QColor QWebWebget::textColor() const
{
    return styleItem("color");
}

void QWebWebget::setAlignment(const Qt::Alignment a)
{
    switch (a) {
        case Qt::AlignLeft:
            setStyleItem("text-align", "left");
            break;
        case Qt::AlignRight:
            setStyleItem("text-align", "right");
            break;
        case Qt::AlignHCenter:
            setStyleItem("text-align", "center");
            break;
        case Qt::AlignJustify:
            setStyleItem("text-align", "justify");
            break;
    }
}

Qt::Alignment QWebWebget::alignment() const
{
    QString s = styleItem("text-align");
    if (s == "left") {
        return Qt::AlignLeft;
    } else if (s == "right") {
        return Qt::AlignRight;
    } else if (s == "center") {
        return Qt::AlignHCenter;
    } else if (s == "justify") {
        return Qt::AlignJustify;
    }
    return Qt::AlignLeft;
}


void QWebWebget::update()
{
    QWebApplication* a = webApp();
    if (a != NULL) {
        a->addWebgetToUpdate(this);
    }
}

void QWebWebget::render(QString& mimeType)
{
    mimeType = "text/html";
    render();
}

void QWebWebget::render()
{
    QWebTag tag(this, "div");
}

void QWebWebget::renderContent()
{
    QIODevice* dev = device();
    if (dev == NULL) {
        return;
    }
    QTextStream stream(dev);
    QListIterator<QObject*> it(children());
    QWebWebget* w;

    if (m_layout != NULL) {
        m_layout->render();
        stream.flush();
    }
    while (it.hasNext()) {
        w = qobject_cast<QWebWebget*>(it.next());
        if (w != NULL && (m_layout == NULL || !m_layout->contains(w))) {
            w->render();
            stream.flush();
        }
    }
}

bool QWebWebget::event(QEvent* e)
{
    if (e->type() == QEvent::ParentChange) {
        QWebWebget* w = qobject_cast<QWebWebget*>(parent());
        if (w != NULL) {
            w->update();
        }
    }
    return QObject::event(e);
}

void QWebWebget::setWebApp(QWebApplication* app)
{
    m_webApp = app;
}
