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

#ifndef HGBRUSH_H
#define HGBRUSH_H

#include "hgbrushplane.h"
#include "hgpoly.h"
#include "hgbbox.h"

//class HGBBox;

/*
 * przechowuje polygony, bbox, i pwenie jeszcze inne rzeczy
 */
class HGBrush {
public:
    // class constructor
    HGBrush();
    // class destructor
    ~HGBrush();
    List<HGPoly*> m_Polys;
    // dodaje plane do listy
    int AddPlane(HGBrushPlane plane);
    // zamienia plane'y na polygony
    int Compile();
    HGBBox m_BBox;
//      // kompiluje i zamienia y z z
//      int CompileQMap();
    bool m_bSolid;
    bool m_bCastShadows;
    bool m_bVisible;
    vec3_t m_vOrigin;
//  protected:
    List<HGBrushPlane*> m_Planes;
    List<HGPoly*> m_BasePolys;
    // sprawdza czy poly jest wewntrz brusha
    bool PolyInside(HGPoly *);
    // wykonuje operacj�csg union
    int CSGUnion(HGBrush * brush);
};

#endif // HGBRUSH_H

