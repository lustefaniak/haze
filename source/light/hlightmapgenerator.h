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

#ifndef HLIGHTMAPGENERATOR_H
#define HLIGHTMAPGENERATOR_H

#include "hlightmap.h"

class HWorld;
class HGPoly;

/*
 * generuje lightmapy
 */
class HLightmapGenerator : public Singleton<HLightmapGenerator> {
public:
    // class constructor
    HLightmapGenerator();
    // class destructor
    ~HLightmapGenerator();
    // generuje lightmap�dla takiego czego
    int Generate(HWorld * world, HGPoly *);
    // sprawdza czy punkt jest widoczny
    float Visible(vec3_t a, vec3_t b, HWorld *world, int polytoignore);
};

#endif // HLIGHTMAPGENERATOR_H

