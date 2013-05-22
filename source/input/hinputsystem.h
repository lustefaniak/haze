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

#ifndef HINPUTSYSTEM_H
#define HINPUTSYSTEM_H

/*
 * odbiera zdarzenia od HRenderWindow lub jako inaczej
 */
class HInputSystem : public Singleton<HInputSystem> {
public:
    // class constructor
    HInputSystem();
    // class destructor
    ~HInputSystem();
    Uint8 *m_bKeys;
    // robi updejt
    int Update();
    // odbiera zdarzenia
    int HandleSDLEvent(SDL_Event event);
    // odbiera sygna o poruszeniu mysz
    void MouseMove(int deltax, int deltay);
    void SetMouseSens(float x); // sets the value of m_fMouseSens
private:
    // czuo�myszki
    float m_fMouseSens;
};

extern HInputSystem * gHInputSystem;

#endif // HINPUTSYSTEM_H

