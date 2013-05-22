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
#include "hplane.h" // class's header file

// class constructor
HPlane::HPlane() {
    this->n.Set(0,0,0);
    this->d=0;
    GetType();
}

HPlane::HPlane(vec3_t n, float d) {
    this->n=n;
    this->d=d;
    GetType();
}

HPlane::HPlane(vec3_t a, vec3_t b, vec3_t c) {
    this->CalcNormal(a,b,c);
}

// class destructor
HPlane::~HPlane() {
}

// oblicza wektor normalny i odlego�
void HPlane::CalcNormal(vec3_t a, vec3_t b, vec3_t c) {
    /* DONE (#1#): Implement HPlane::CalcNormal() */
    this->n = ( c - b ).Cross ( a - b );
    this->n.Normalize ( );
    this->d = -this->n.Dot ( a );
    GetType();
}

// zwraca jaka jest odlego�jakiego punktu od paszczyzny
float HPlane::GetDistance(vec3_t v) {
    /* DONE (#1#): Implement HPlane::GetDistance() */
    return ( this->n.Dot ( v ) + this->d );
}

// zwraca typ paszczyzny
int HPlane::GetType() {
    /* TODO (#1#): Implement HPlane::GetType() */
    if ((this->n[0] == 1.0f) || (this->n[0] == -1.0f)) {
        this->iType = PLANE_X;
    } else if ((this->n[1] == 1.0f) || (this->n[1] == -1.0f)) {
        this->iType = PLANE_Y;
    } else if ((this->n[2] == 1.0f) || (this->n[2] == -1.0f)) {
        this->iType = PLANE_Z;
    } else {

        float fNX,fNY,fNZ;
        fNX = (float)fabs(this->n[0]);
        fNY = (float)fabs(this->n[1]);
        fNZ = (float)fabs(this->n[2]);

        if ((fNX >= fNY) && (fNX >= fNZ)) {
            this->iType = PLANE_ANYX;
        } else if ((fNY >= fNX) && (fNY >= fNZ)) {
            this->iType = PLANE_ANYY;
        } else {
            this->iType = PLANE_ANYZ;
        }
    }
    return this->iType;
}

// sprawdza czy dana wizka przechodzi przez paszczyzn�
bool HPlane::GetIntersection(vec3_t rStart, vec3_t rDir, vec3_t & res) {
    /* TODO (#1#): Implement HPlane::GetIntersection() */
    float denom, numer, u;

    denom = this->n.Dot(rDir);

    // Line is parallel to the plane or plane normal faces away from ray
    if (denom > -mLibEpsilon) return 0;

    numer = -(this->n.Dot(rStart) + this->d);
    u = numer / denom;

    // Intersection before the rays origin
    if (u <= 0.0f) return 0;

    bool onRay=1;
    // Intersection on the length of the ray?
    if (onRay && u > 1.0f) return 0;

    res = rStart + rDir * u;

    return 1;
}

// zwraca punkt przeci�ia si�3 paszczyzn
bool HPlane::GetIntersection(HPlane *a, HPlane *b, vec3_t &v) {
    /* DONE (#1#): Implement HPlane::GetIntersection() */
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
    //debug("point: %f %f %f\n\n",v[0],v[1],v[2]);

    return true;

}

