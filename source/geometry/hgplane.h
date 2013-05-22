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

#ifndef HGPLANE_H
#define HGPLANE_H

/*
 * klasa dla paszczyzny
 */

#define PLANE_X          0
#define PLANE_Y          1
#define PLANE_Z          2
#define PLANE_ANYX       3
#define PLANE_ANYY       4
#define PLANE_ANYZ       5

#define SIDE_FRONT   1
#define SIDE_BACK    2
#define SIDE_SPLIT   3
#define SIDE_ONPLANE 0

//#define HGPlane plane_t

class HGPlane {
public:
    // class constructor
    HGPlane();
    HGPlane(vec3_t a, vec3_t b, vec3_t c);
    // class destructor
    ~HGPlane();
    vec3_t n;
    float d;
    // tworzy paszczyzn�z punkt�
    void CalcNormal(vec3_t a, vec3_t b, vec3_t c);
    // podaje odlefo�punktu od paszczyzny
    float GetPointDistance(vec3_t &v);
    // punkt przeci�ia 3 paszczyzn
    bool GetIntersection(HGPlane *a, HGPlane *b, vec3_t &v);
    // zwraca punkt przeci�ia paszczyzny przez wizk�
    bool RayIntersect(vec3_t start, vec3_t dir, vec3_t & point);
    // zwraca jakiego typu paszczyzn jest ta paszczyzna
    int GetPlaneType();
    int iType;
//      bool GetIntersection(vec3_t start, vec3_t end, vec3_t & point, float &Percentage);
};

#endif // HGPLANE_H

