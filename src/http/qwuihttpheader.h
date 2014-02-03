#ifndef QWUIHTTPHEADER_H
#define QWUIHTTPHEADER_H

#include <qglobal.h>
#include <QString>
#include <QStringList>
#include <QList>
#include <QPair>

class QWuiHttpHeader
{
public:
    QWuiHttpHeader();
    QWuiHttpHeader(const QString&);
    virtual ~QWuiHttpHeader();

    void setValue(const QString& key, const QString& value);
    void addValue(const QString& key, const QString& value);
    QString value(const QString& key) const;
    QStringList allValues(const QString& key) const;
    bool hasKey(const QString&) const;

    // ### Qt 5: change to qint64
    bool hasContentLength() const;
    uint contentLength() const;
    void setContentLength(int);

    bool hasContentType() const;
    QString contentType() const;
    void setContentType(const QString&);

    virtual QString toString() const;
    bool isValid() const { return m_valid; }

    virtual int majorVersion() const = 0;
    virtual int minorVersion() const = 0;

protected:
    virtual bool parseLine(const QString& line, int number);
    bool parse(const QString&);
    void setValid(bool v) { m_valid = v; }

private:
    bool m_valid;
    QList<QPair<QString, QString> > m_values;
};

class QWuiHttpResponseHeader : public QWuiHttpHeader {
public:
    QWuiHttpResponseHeader(int code = 200, const QString& text = QString(), int majorVer = 1, int minorVer = 1);

    void setStatusLine(int code = 200, const QString& text = QString(), int majorVer = 1, int minorVer = 1);
    int statusCode() const { return m_statusCode; }
    QString reasonPhrase() const {return m_reasonPhrase; }
    int majorVersion() const { return m_majorVersion; }
    int minorVersion() const { return m_minorVersion; }

    QString toString() const;

protected:
    bool parseLine(const QString& line, int number);

private:
    int m_statusCode;
    QString m_reasonPhrase;
    int m_majorVersion;
    int m_minorVersion;
};

class QWuiHttpRequestHeader : public QWuiHttpHeader {
public:
    QWuiHttpRequestHeader();
    QWuiHttpRequestHeader(const QString&);

    QString method() const { return m_method; }
    QString path() const { return m_path; }
    int majorVersion() const { return m_majorVersion; }
    int minorVersion() const { return m_minorVersion; }

    QString toString() const;

protected:
    bool parseLine(const QString& line, int number);

private:
    QString m_method;
    QString m_path;
    int m_majorVersion;
    int m_minorVersion;
};

#endif // QWUIHTTPHEADER_H
