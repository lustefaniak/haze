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

#ifndef HGPOLY_H
#define HGPOLY_H

#include "hgvert.h"
#include "hgbrushplane.h"
#include "../light/hlightmap.h"

/*
 * klasa dla polygon�
 */
class HGPoly {
public:
    // class constructor
    HGPoly();
    // class destructor
    ~HGPoly();
    // sortuje wszystkie wierzchoki
    void SortVerticesCCW();
    HGBrushPlane * p;
    // dodaje wierzchoek do polygonu
    void AddVert(HGVert vert);
    int m_BaseID;
    HLightmap *m_Lightmap;
    vec3_t m_vCenter;
    List<HGVert> m_Verts;
    // oblicza wsp�dne tekstury
    void CalculateTextureUV();
    // sprawdza czy punkt ley na polygonie
    bool PointOnPoly(vec3_t point);
    vec3_t stangent;
    vec3_t ttangent;
    HGPoly * BSP_Next;
    HGPoly * BSP_Prev;
    HGPoly * Rendering_Next;
    // przecina poly na dwie cz�i
    int SplitByPlane(HGPlane* plane, HGPoly * &front, HGPoly * &back);
    int SplitByPoly(HGPoly* poly, HGPoly * &front, HGPoly * &back);
    // sprawdza po kt�ej stronie paszczyzny ley poly
    int PlaneSide(HGPlane * plane);

};

#endif // HGPOLY_H

