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

#include "HangMan.h"
#include <QtWui/QwuiBoxLayout>
#include <QtWui/QwuiLabel>
#include "Game.h"

HangMan::HangMan(QwuiWebget* parent, const QString& webName) :
    QwuiWebget(parent, webName),
    m_title(NULL),
    m_word(NULL),
    m_image(NULL),
    m_letterBox(NULL),
    m_game(NULL)
{
    m_game = new Game(this);
    QStringList wl;
    wl << "maison" << "voiture" << "vacances";
    m_game->setWordsList(wl);
    connect(m_game, SIGNAL(victory()), this, SLOT(playerWon()));
    connect(m_game, SIGNAL(defeat()), this, SLOT(playerLost()));

    QwuiBoxLayout* l = new QwuiVBoxLayout(this);

    m_title = new QwuiLabel(this, "m_title");
    m_word = new QwuiLabel(this, "m_word");
    m_image = new QwuiLabel(this, "m_image");
    m_letterBox = new QwuiLabel(this, "m_letterBox");
    connect(m_letterBox, SIGNAL(clicked(const QString&)), this, SLOT(letterClicked(const QString&)));
    connect(m_title, SIGNAL(clicked(const QString&)), this, SLOT(newGame(const QString&)));

    l->addWebget(m_title, 1);
    l->addWebget(m_word, 1);
    l->addWebget(m_image, 5);
    l->addWebget(m_letterBox, 2);

    m_title->setText("<h1>Hangman</h1><br /><h4><a href=\"new_game\">New Game</a></h4>");
    m_title->setAlignment(Qt::AlignHCenter);
    m_letterBox->setAlignment(Qt::AlignHCenter);
    newGame("new_game");
}

HangMan::~HangMan()
{
}

void HangMan::letterClicked(const QString& link)
{
    qDebug(QString("letterClicked(%1)").arg(link).toAscii());
    if (!link.isEmpty()) {
        m_game->play(link[link.length() - 1]);
        m_image->setText(QString("<h1>%1</h1>").arg(m_game->usedCharacters()));
        m_word->setText(QString("<h2>%1</h2>").arg(m_game->foundWord()));
    }
}

void HangMan::newGame(const QString& link)
{
    qDebug("newGame()");
    if (link == "new_game") {
        m_letterBox->setText("<h1> \
                <a href=\"letter_A\">A</a> \
                <a href=\"letter_B\">B</a> \
                <a href=\"letter_C\">C</a> \
                <a href=\"letter_D\">D</a> \
                <a href=\"letter_E\">E</a> \
                <a href=\"letter_F\">F</a> \
                <a href=\"letter_G\">G</a> \
                <a href=\"letter_H\">H</a> \
                <a href=\"letter_I\">I</a> \
                <a href=\"letter_J\">J</a> \
                <a href=\"letter_K\">K</a> \
                <a href=\"letter_L\">L</a> \
                <a href=\"letter_M\">M</a> \
                <a href=\"letter_N\">N</a> \
                <a href=\"letter_O\">O</a> \
                <a href=\"letter_P\">P</a> \
                <a href=\"letter_Q\">Q</a> \
                <a href=\"letter_R\">R</a> \
                <a href=\"letter_S\">S</a> \
                <a href=\"letter_T\">T</a> \
                <a href=\"letter_U\">U</a> \
                <a href=\"letter_V\">V</a> \
                <a href=\"letter_W\">W</a> \
                <a href=\"letter_X\">X</a> \
                <a href=\"letter_Y\">Y</a> \
                <a href=\"letter_Z\">Z</a> \
                </h1>");
        m_game->newGame();
        m_image->setText(QString::null);
        m_word->setText(QString("<h2>%1</h2>").arg(m_game->foundWord()));
    }
}

void HangMan::playerWon()
{
    m_letterBox->setText("Victory !");
}

void HangMan::playerLost()
{
    m_letterBox->setText("Defeat !");
}
