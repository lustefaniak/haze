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
#include "../Haze.h"
static const float Delta = 1.0e-05f;

// Thanks Hasty
bool u3dPointInTriangle(const vec3_t &point, const vec3_t &normal,
 const vec3_t &p1, const vec3_t &p2, const vec3_t &p3)
{
	float u0, u1, u2;
	float v0, v1, v2;
	float a, b;
	float max;
	int i, j;
	bool bInter = 0;

	max = MAX(MAX(ABS(normal[0]), ABS(normal[1])), ABS(normal[2]));
	if (max == ABS(normal[0])) {i = 1; j = 2;} // y, z
	if (max == ABS(normal[1])) {i = 0; j = 2;} // x, z
	if (max == ABS(normal[2])) {i = 0; j = 1;} // x, y
	
	u0 = point[i] - p1[i];
	v0 = point[j] - p1[j];
	u1 = p2[i] - p1[i];
	v1 = p2[j] - p1[j];
	u2 = p3[i] - p1[i];
	v2 = p3[j] - p1[j];

	if (u1 > -Delta && u1 < Delta)// == 0.0f)
	{
		b = u0 / u2;
		if (0.0f <= b && b <= 1.0f)
		{
			a = (v0 - b * v2) / v1;
			if ((a >= 0.0f) && (( a + b ) <= 1.0f))
				bInter = 1;
		}
	}
	else
	{
		b = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
		if (0.0f <= b && b <= 1.0f)
		{
			a = (u0 - b * u2) / u1;
			if ((a >= 0.0f) && (( a + b ) <= 1.0f ))
				bInter = 1;
		}
	}

	return bInter;
}

void u3dReflectVector(vec3_t &vel, vec3_t &n)
{
   vec3_t vn = n * (n.Dot(vel));
   vec3_t vt = vel - vn;
   vel = vt - vn;
}

bool u3dRayPlaneInter(vec3_t &rStart, vec3_t &rDir, vec3_t &pNorm,
 vec3_t &pOrig, float &dest)
{
   float d = -pNorm.Dot(pOrig);
   float denom = pNorm.Dot(rDir);

   if (denom > -mLibEpsilon && denom < mLibEpsilon)
		return 0; // Line is parallel to the plane

   float numer = -(pNorm.Dot(rStart) + d);

   dest = numer / denom;

   return 1;
}

static vec3_t axis[3] = 
{
   vec3_t(1.0f, 0.0f, 0.0f),
   vec3_t(0.0f, 1.0f, 0.0f),
   vec3_t(0.0f, 0.0f, 1.0f)
};

// Get the right and up vectors for a given normal.
void u3dGetRightUp(const vec3_t &n, vec3_t &right, vec3_t &up)
{
   vec3_t fn(mLibFab(n[0]), mLibFab(n[1]), mLibFab(n[2]));

   int major = 0;

   // find the major axis
   if (fn[1] > fn[major])
      major = 1;
   if (fn[2] > fn[major])
      major = 2;

   // build right vector by hand
   if (fn[0] == 1 || fn[1] == 1 || fn[2] == 1)
   {
      if (major == 0 && n[0] > 0.0f)
         right.Set(0.0f, 0.0f, -1.0f);
      else if (major == 0)
         right.Set(0.0f, 0.0f, 1.0f);
      
      if (major == 1 || (major == 2 && n[2] > 0.0f))
         right.Set(1.0f, 0.0f, 0.0f);
   
      if (major == 2 && n[2] < 0.0f)
         right.Set(-1.0f, 0.0f, 0.0f);
   }
   else
      right.Cross(axis[major], n);
  
   up.Cross(n, right);
   right.Normalize();
   up.Normalize();
}

// Project a vector 'b' onto the vector 'a'
void u3dProjectVector(const vec3_t &b, const vec3_t &a, vec3_t &res)
{
   res.Set(a);
   res.Scale((a.Dot(b) / a.Dot(a)));
}

/*
   Project the 'src' vector on to the plane created by 'v1' and 'v2'.  'v1' and
'v2' MUST be perpindicular to eachother. 
*/
void u3dProjectPlane(const vec3_t &src, const vec3_t &v1, const vec3_t &v2, vec3_t &res)
{
   vec3_t t1, t2;
   
   u3dProjectVector(src, v1, t1);
   u3dProjectVector(src, v2, t2);
   res.Add(t1, t2);
}

