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

#include "../Haze.h"
#include "hgplane.h" // class's header file

// class constructor
HGPlane::HGPlane(vec3_t a, vec3_t b, vec3_t c) {
    CalcNormal(a,b,c);
}
HGPlane::HGPlane() {
    // insert your code here
    n.Set(0);
    n[1]=1;
    d=0;
}

// class destructor
HGPlane::~HGPlane() {
    // insert your code here
}

// tworzy paszczyzn�z punkt�
void HGPlane::CalcNormal(vec3_t a, vec3_t b, vec3_t c) {
    /* DONE (#1#): Implement HGPlane::PointsToPlane() */
    n = ( c - b ).Cross ( a - b );
    n.Normalize ( );
    d = -n.Dot ( a );

}

// podaje odlefo�punktu od paszczyzny
float HGPlane::GetPointDistance(vec3_t &v) {
    /* DONE (#1#): Implement HGPlane::Distance() */
    return ( n.Dot ( v ) + d );
}

// punkt przeci�ia 3 paszczyzn
bool HGPlane::GetIntersection(HGPlane *a, HGPlane *b, vec3_t &v) {
    /* TODO (#1#): Implement HGPlane::GetIntersection() */
    float   denom;
    vec3_t tmp;
    denom = this->n.Dot(a->n.Cross(b->n));
#ifdef _DEBUG
    //debug("denom=%f\t",denom);
#endif
    if ( fabs ( denom ) < epsilon ) {
#ifdef _DEBUG
        //debug("coplanar faces\n");
#endif
        return false;
    }
    v=(-this->d*(a->n.Cross(b->n))-a->d*(b->n.Cross(this->n))-b->d*(this->n.Cross(a->n)))/this->n.Dot(a->n.Cross(b->n));
//      debug("point: %f %f %f\n\n",v[0],v[1],v[2]);
    GetPlaneType();
    return true;
}

// zwraca punkt przeci�ia paszczyzny przez wizk�
bool HGPlane::RayIntersect(vec3_t rStart, vec3_t rDir, vec3_t & res) {
    float denom, numer, u;

    denom = n.Dot(rDir);

    // Line is parallel to the plane or plane normal faces away from ray
    if (denom > -mLibEpsilon)
        return 0;

    numer = -(n.Dot(rStart) + d);
    u = numer / denom;

    // Intersection before the rays origin
    if (u <= 0.0f)
        return 0;
    bool onRay=1;
    // Intersection on the length of the ray?
    if (onRay && u > 1.0f)
        return 0;

    res = rStart + rDir * u;

    return 1;

}

// zwraca jakiego typu paszczyzn jest ta paszczyzna
int HGPlane::GetPlaneType() {
    /* TODO (#1#): Implement HGPlane::GetPlaneType() */
    if ((n[0] == 1.0f) || (n[0] == -1.0f)) {
        iType = PLANE_X;
    } else if ((n[1] == 1.0f) || (n[1] == -1.0f)) {
        iType = PLANE_Y;
    } else if ((n[2] == 1.0f) || (n[2] == -1.0f)) {
        iType = PLANE_Z;
    } else {
        float fNX,fNY,fNZ;

        fNX = (float)fabs(n[0]);
        fNY = (float)fabs(n[1]);
        fNZ = (float)fabs(n[2]);

        if ((fNX >= fNY) && (fNX >= fNZ)) {
            iType = PLANE_ANYX;
        } else if ((fNY >= fNX) && (fNY >= fNZ)) {
            iType = PLANE_ANYY;
        } else {
            iType = PLANE_ANYZ;
        }
    }
    return iType;
}

