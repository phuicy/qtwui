/**************************************************************************
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

#ifndef QWUIABSTRACTRESSOURCE_H
#define QWUIABSTRACTRESSOURCE_H

#include <QtCore/QString>
#include <QtWui/QwuiGlobal>

class QIODevice;

/**
 * \brief This class represents a ressource that can be served by the web server.
 * A ressource can be any type of information that can be served by a web server. Examples: an image file, a text file, some code generating HTML, etc...
 * A ressource is identified by its MIME-type and this class provides the ressource length, its path and is able
 * to send the ressource to an QIODevice.
 */
class QTWUI_EXPORT QwuiAbstractRessource
{
public:
    /**
     * @param path path of the ressource.
     */
    QwuiAbstractRessource(const QString& path = QString::null);
    virtual ~QwuiAbstractRessource();

    /**
     * Subclasses must provide the MIME type of the ressource like "text/html" or "image/jpeg".
     * @return the MIME type of the ressource.
     */
    virtual QString mimeType() const = 0;

    /**
     * @return the length of the ressource in bytes.
     */
    virtual qint64 length() const = 0;

    /**
     * @return the path identifying the ressource. This is added to the URL by the HTTP server.
     */
    virtual QString path() const;


    /**
     * @return true if the ressource exists, false otherwise.
     */
    virtual bool exists() const;

    /**
     * Writes the ressource to \a dev
     * @param dev IO device to write to.
     */
    virtual void sendToDevice(QIODevice* dev) const = 0;

private:
    QString m_path;
};

#endif // QWUIABSTRACTRESSOURCE_H
