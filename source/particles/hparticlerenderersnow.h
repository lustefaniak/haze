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

#ifndef HPARTICLERENDERERSNOW_H
#define HPARTICLERENDERERSNOW_H

#include "hparticlerenderer.h" // inheriting class's header file

/*
 * renderuje nieg i inne podobne spadajce platki czegostam
 */

class HParticleRendererSnow : public HParticleRenderer {
public:
    // class constructor
    HParticleRendererSnow();
    // class destructor
    virtual ~HParticleRendererSnow();
    // renderuje nieg
    void Render(HCamera * cam, HParticleSystem * system);
    int m_tSnow;
    vec3_t * m_posBuffer;
    int * m_coordBuffer;
};

#endif // HPARTICLERENDERERSNOW_H

