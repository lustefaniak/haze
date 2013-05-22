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

#ifndef HOBJECTSNOW_H
#define HOBJECTSNOW_H

#include "hobject.h" // inheriting class's header file

/*
 * odpowiedzialny za padanie niegu w danym miejscu
 */
class HObjectSnow : public HObject {
public:
    // class constructor
    HObjectSnow(HLevel * level);
    // class destructor
    ~HObjectSnow();
    HParticleSystemSnow * m_system;
    HParticleRendererSnow * m_renderer;
    // renderuje nieg
    virtual void Render();
    // przeprowadza updejt
    void Update();
};

#endif // HOBJECTSNOW_H

