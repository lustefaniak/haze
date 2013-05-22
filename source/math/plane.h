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

   TODO  

*/
#ifndef __PLANEH__
#define __PLANEH__

#include <stdio.h>
#include "mathlib.h"

struct plane_t
{
   plane_t()                           {d = 0;}
   virtual ~plane_t()                  { }
   
   void Reset(void)                    {n.Set(0, 0, 0); d = 0;}
   bool IsFront(vec3_t &pt)
    {return (GetPointDistance(pt) > 0.0f) ? 1 : 0;}
   bool IsBehind(vec3_t &pt)           {return !(IsFront(pt));}   
   void CalcD(vec3_t &pt)              {d = -pt.Dot(n);}
   inline bool IsOn(vec3_t &pt);   
   inline void CalcNormal(vec3_t pta, vec3_t ptb, vec3_t ptc);
   inline bool LineIntersect(vec3_t &start, vec3_t &end, vec3_t &point,
    vec3_t &result);
   inline bool RayIntersect(vec3_t rStart, vec3_t rDir, vec3_t &res,
    bool onRay = 0);
   inline bool PlanesIntersection(plane_t *a, plane_t *b, vec3_t &v);
   float GetPointDistance(vec3_t &pt)  {return n.Dot(pt) + d;} 
   const vec3_t &GetNormal(void)       {return n;}
   const float &GetD(void)             {return d;}
   

//protected:
   vec3_t n;
   float d;
};

inline bool plane_t::IsOn(vec3_t &pt)
{
   float d = GetPointDistance(pt);
   return (d > -mLibEpsilon && d < mLibEpsilon) ? 1 : 0;
}

inline void plane_t::CalcNormal(vec3_t pta, vec3_t ptb, vec3_t ptc)
{
   n.Cross(ptb - pta, ptc - pta);
   n.Normalize();
   d = -ptc.Dot(n);
}

inline bool plane_t::LineIntersect(vec3_t &start, vec3_t &end, vec3_t &point,
 vec3_t &result)
{
	float denom, numer, u;
	vec3_t dir;

	dir = end - start;

	denom = n.Dot(dir);

   // No divide by zero!
	if (denom > -mLibEpsilon && denom < mLibEpsilon)
		return 0; // Line is parallel to the plane

	numer = n.Dot(point - start);

	u = numer / denom;

   // Is there an intersection along the line?
	if (u <= 0.0f || u > 1.0f)
		return 0;

	result = start + dir * u;

	return 1;
}

inline bool plane_t::RayIntersect(vec3_t rStart, vec3_t rDir, vec3_t &res,
 bool onRay)
{
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
   
   // Intersection on the length of the ray?
   if (onRay && u > 1.0f)
      return 0;

	res = rStart + rDir * u;

	return 1;
}

// punkt przeciêcia 3 p³aszczyzn
inline bool plane_t::PlanesIntersection(plane_t *a, plane_t *b, vec3_t &v)
{
	/* TODO (#1#): Implement HGPlane::GetIntersection() */
		float	denom;
		vec3_t tmp;
		denom = this->n.Dot(a->n.Cross(b->n));
		#ifdef _DEBUG
		//debug("denom=%f\t",denom);		
		#endif
        if ( fabs ( denom ) < epsilon )
		{
		#ifdef _DEBUG
		//debug("coplanar faces\n");			
		#endif
   return false;
		}
		v=(-this->d*(a->n.Cross(b->n))-a->d*(b->n.Cross(this->n))-b->d*(this->n.Cross(a->n)))/this->n.Dot(a->n.Cross(b->n));
//		debug("point: %f %f %f\n\n",v[0],v[1],v[2]);
		return true;
}

#endif
