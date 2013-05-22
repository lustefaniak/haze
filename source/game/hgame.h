/***************************************************************************
 *   Copyright (C) 2007 by Łukasz Stefaniak   *
 *   lustefaniak@gmail.com   *
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

#ifndef HGAME_H
#define HGAME_H

/*
 * do obsugi gry, musi by�przeadowana
 */
class HGame {
public:
    // class constructor
    HGame();
    // class destructor
    ~HGame();
    // uruchamia gr�
    virtual int Init() = 0L;
    // zwalnia zasoby gry
    virtual int DeInit() = 0L;
    // robi update stanu gry
    virtual int Update() = 0L;
    // renderuje klatk�
    virtual void Render() = 0L;
};

#endif // HGAME_H

