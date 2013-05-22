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

#ifndef HPLANE_H
#define HPLANE_H

//typy paszczyzn
#define PLANE_X          0
#define PLANE_Y          1
#define PLANE_Z          2
#define PLANE_ANYX       3
#define PLANE_ANYY       4
#define PLANE_ANYZ       5

/*
 * taka sobie paszczyzna
 */
class HPlane {
public:
    // class constructor
    HPlane();
    HPlane(vec3_t n, float d);
    HPlane(vec3_t a, vec3_t b, vec3_t c);
    // class destructor
    ~HPlane();
    //wektor normalny
    vec3_t n;
    //odlego�
    float d;
    //typ paszczyzny
    int iType;
    // oblicza wektor normalny i odlego�
    void CalcNormal(vec3_t a, vec3_t b, vec3_t c);
    // zwraca jaka jest odlego�jakiego punktu od paszczyzny
    float GetDistance(vec3_t v);
    // zwraca typ paszczyzny
    int GetType();
    // sprawdza czy dana wizka przechodzi przez paszczyzn�
    bool GetIntersection(vec3_t rStart, vec3_t rDir, vec3_t & res);
    // zwraca punkt przeci�ia si�3 paszczyzn
    bool GetIntersection(HPlane *a, HPlane *b, vec3_t &v);
};

#endif // HPLANE_H

