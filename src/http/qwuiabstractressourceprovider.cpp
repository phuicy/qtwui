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

#include <QtWui/QwuiAbstractRessourceProvider>

QwuiAbstractRessourceProvider::QwuiAbstractRessourceProvider(const QString& sessionId) :
    QObject(NULL),
    m_keepSessions(false),
    m_sessionLifeTime(1800),
    m_sessionId(sessionId)
{
    resetSessionTimeoutDate();
}

QwuiAbstractRessourceProvider::~QwuiAbstractRessourceProvider()
{
}

QString QwuiAbstractRessourceProvider::sessionId() const
{
    return m_sessionId;
}

bool QwuiAbstractRessourceProvider::keepSessions() const
{
    return m_keepSessions;
}

void QwuiAbstractRessourceProvider::setKeepSessions(bool keep)
{
    m_keepSessions = keep;
}

QDateTime QwuiAbstractRessourceProvider::sessionTimeoutDate() const
{
    return m_sessionTimeoutDate;
}

void QwuiAbstractRessourceProvider::resetSessionTimeoutDate()
{
    m_sessionTimeoutDate = QDateTime::currentDateTime().addSecs(m_sessionLifeTime);
}

bool QwuiAbstractRessourceProvider::isSessionTimedOut() const
{
    return m_sessionTimeoutDate <= QDateTime::currentDateTime();
}

int QwuiAbstractRessourceProvider::sessionLifeTime() const
{
    return m_sessionLifeTime;
}

void QwuiAbstractRessourceProvider::setSessionLifeTime(int secs)
{
    m_sessionLifeTime = secs;
}
