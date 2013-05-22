/*
   Copyright (C) 2000 Nate Miller nathanm@uci.edu

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   See gpl.txt for more information regarding the GNU General Public License.
*/
/*
   WORKLOG
      (05/15/01)
         - Added u3dGetRightUp, u3dProjectVector and u3dProjectPlane
   TODO  

*/
#ifndef __UTIL3D__
#define __UTIL3D__

#include "mathlib.h"

bool u3dPointInTriangle(const vec3_t &point, const vec3_t &normal,
 const vec3_t &p1, const vec3_t &p2, const vec3_t &p3);
void u3dReflectVector(vec3_t &vel, vec3_t &n);
bool u3dRayPlaneInter(vec3_t &rStart, vec3_t &rDir, vec3_t &pNorm,
 vec3_t &pOrig, float &dest);
void u3dGetRightUp(const vec3_t &n, vec3_t &right, vec3_t &up);
void u3dProjectVector(const vec3_t &b, const vec3_t &a, vec3_t &res);
void u3dProjectPlane(const vec3_t &src, const vec3_t &v1, const vec3_t &v2,
 vec3_t &res);
#endif

