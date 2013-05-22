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

#ifndef _HAZE_ENGINE_BY_LUKASZ_STEFANIAK_
#define _HAZE_ENGINE_BY_LUKASZ_STEFANIAK_

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>

#define EXT_HASH

// Note - not in the original STL, but exists in SGI STL and STLport
#ifdef EXT_HASH
#   include <ext/hash_map>
#   include <ext/hash_set>
#else
#   include <hash_set>
#   include <hash_map>
#endif

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

extern "C" {

#   include <sys/types.h>
#   include <sys/stat.h>

}

#include <SDL.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#endif

using namespace std;

#ifdef WIN32

#ifndef _DEBUG
#define BUILDSTRING "Win32"
#else
#define BUILDSTRING "Win32 DEBUG"
#endif

#ifdef _M_IX86
#define CPUSTRING   "x86"
#elif defined _M_ALPHA
#define CPUSTRING   "AXP"
#endif

#elif defined __linux__

#define BUILDSTRING "Linux"

#ifdef __i386__
#define CPUSTRING "i386"
#elif defined __alpha__
#define CPUSTRING "axp"
#else
#define CPUSTRING "Unknown"
#endif

#elif defined __sun__

#define BUILDSTRING "Solaris"

#ifdef __i386__
#define CPUSTRING "i386"
#else
#define CPUSTRING "sparc"
#endif

#else   // !WIN32

#define BUILDSTRING "NON-WIN32"
#define CPUSTRING   "NON-WIN32"

#endif

#define HAZE_VERSION "Haze 1.0 alpha("BUILDSTRING")"

typedef unsigned char       byte;
/*
#if !defined(ENDIAN_LITTLE) && !defined(ENDIAN_BIG)
# if defined(__i386__) || defined(__ia64__) || defined(WIN32) || (defined(__alpha__) || defined(__alpha)) || defined(__arm__) || (defined(__mips__) && defined(__MIPSEL__)) || defined(__LITTLE_ENDIAN__)
#  define ENDIAN_LITTLE
# else
#  define ENDIAN_BIG
# endif
#endif

short ShortSwap (short l);
int LongSwap (int l);
float FloatSwap (float f);

#ifdef ENDIAN_LITTLE
// little endian
# define BigShort(l) ShortSwap(l)
# define LittleShort(l) (l)
# define BigLong(l) LongSwap(l)
# define LittleLong(l) (l)
# define BigFloat(l) FloatSwap(l)
# define LittleFloat(l) (l)
#elif ENDIAN_BIG
// big endian
# define BigShort(l) (l)
# define LittleShort(l) ShortSwap(l)
# define BigLong(l) (l)
# define LittleLong(l) LongSwap(l)
# define BigFloat(l) (l)
# define LittleFloat(l) FloatSwap(l)
#else
// figure it out at runtime
extern short (*BigShort) (short l);
extern short (*LittleShort) (short l);
extern int (*BigLong) (int l);
extern int (*LittleLong) (int l);
extern float (*BigFloat) (float l);
extern float (*LittleFloat) (float l);
#endif

*/

#define ABS(a)      (((a)<0) ? -(a) : (a))
#define FLOOR(a)        ((a)>0 ? (int)(a) : -(int)(-a))
#define CEILING(a) \
((a)==(int)(a) ? (a) : (a)>0 ? 1+(int)(a) : -(1+(int)(-a)))
#define ROUND(a)    ((a)>0 ? (int)(a+0.5) : -(int)(0.5-a))
#define SGN(a)      (((a)<0) ? -1 : 1)
#define SQR(a)      ((a)*(a))
#define MIN(a,b)    (((a)<(b))?(a):(b))
#define MAX(a,b)    (((a)>(b))?(a):(b))
#define SWAP(a,b)   { a^=b; b^=a; a^=b; }
#define LERP(a,l,h) ((l)+(((h)-(l))*(a)))
#define CLAMP(v,l,h)    ((v)<(l) ? (l) : (v) > (h) ? (h) : v)
#define DELETE_PTR( x ) if(x != NULL) { delete x; x = NULL; }
#define DELETE_ARRAY( a ) {if(a!=NULL){delete[] a; a=NULL;}}
#define FREE_PTR( x )   if(x != NULL) { free( x ); x = NULL;}
#define RANDOM(n)       (((float)rand() / (float)RAND_MAX)*(n))
#define DESTROY_OBJ(x)  if(x != NULL) { x->Destroy(); DELETE_PTR(x); }

#define INVSIN( x ) ( (float)asin( (x) ) * ( 180.0f / 3.14159265358979323846f ) )
#define INVCOS( x ) ( (float)acos( (x) ) * ( 180.0f / 3.14159265358979323846f ) )

#define DEGTORAD 0.01745329251994329547f
#define RADTODEG 57.29577951308232286465f

#define DEG2RAD(val) (val*DEGTORAD)
#define RAD2DEG(val) (val*RADTODEG)

#define epsilon 1.0e-04f

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446
#define PIOVER180 0.017453292519943295769236907684886127134428718885417254560971914401710091146034494436822415696345094822123044925073790592483854692

#define HM(a) a

/*
// unknown pragmas are SUPPOSED to be ignored, but....
#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4051)     // ALPHA

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4305)     // truncation from const double to float
*/
#ifndef inline
#define inline __inline
#endif

/*#ifndef vsnprintf
#define vsnprintf _vsnprintf
#endif*/

//#include "core/mmgr.h"

#include "core/hlog.h"

#include "math/util3d.h"
#include "math/vector.h"
#include "math/mathlib.h"
#include "core/list.h"
#include "core/errors.h"
#include "core/singleton.h"

#include "core/htimer.h"
#include "renderer/hrendererwindow.h"
#include "renderer/hrenderer.h"
#include "input/hinputsystem.h"
#include "console/hconsole.h"
#include "material/htexturemanager.h"
#include "material/hmaterial.h"
#include "material/hmaterialmanager.h"
#include "gui/hfont.h"
#include "gui/hgui.h"

#include "geometry/hgbbox.h"
#include "geometry/hgpoly.h"
#include "light/hlightsystem.h"
#include "light/hlightmapgenerator.h"
#include "geometry/hbsp.h"
#include "world/hworld.h"
#include "world/hworldfromqmap.h"
#include "core/henginecore.h"
#include "particles/hparticlesystem.h"
#include "particles/hparticlerenderer.h"
#include "particles/hparticlerenderersnow.h"
#include "particles/hparticlesystemsnow.h"
#include "particles/hparticlesystemrain.h"
#include "particles/hparticlerendererrain.h"

#include "objects/hobject.h"
#include "objects/hobjectfactory.h"

#include "game/hbulletmanager.h"
#include "game/hlevel.h"
#include "game/hsky.h"
#include "game/hgamehud.h"
#include "game/hgamefpp.h"

#endif

