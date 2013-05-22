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
      (10/02/00)
         - added an mLib prefix to everyting, makes more sense now
   TODO  
      - the #define and static const is ick.  need to change it
*/
#ifndef __MATHLIBH__
#define __MATHLIBH__

#include <stdlib.h>
#include <math.h>

#ifndef uint
typedef unsigned int uint;
#endif

#define mLibFab(a)    (a >= 0 ? a : -a) 
#define mLibMax(a, b) (a > b ? a : b)

static const double mLibPi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446;
static const float mLibEpsilon = 1.0e-05f;
static const double mLibTwoPi = 2 * mLibPi;
static const double mLibPiDivTwo = mLibPi / 2;

static float mLibCos(float angle)
 {return (float) cos(mLibPi * ((double) angle / 180));}
static float mLibSin(float angle)
 {return (float) sin(mLibPi * ((double) angle / 180));}

inline float HRandom(float lo, float hi)
{
   int r = rand();
   float	x = (float)(r & 0x7fff) / (float)0x7fff;
   return (x * (hi - lo) + lo);
}

inline unsigned int HPower2(unsigned int x)
	{
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return x+1;
	}

#include "vector.h"
#include "matrix.h"

#endif

