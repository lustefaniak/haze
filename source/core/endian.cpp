#include "../Haze.h"

/*
============================================================================

					BYTE ORDER FUNCTIONS

============================================================================
*/



#if !defined(ENDIAN_LITTLE) && !defined(ENDIAN_BIG)
short   (*BigShort) (short l);
short   (*LittleShort) (short l);
int     (*BigLong) (int l);
int     (*LittleLong) (int l);
float   (*BigFloat) (float l);
float   (*LittleFloat) (float l);
#endif

short   ShortSwap (short l)
{
	byte    b1,b2;

	b1 = l&255;
	b2 = (l>>8)&255;

	return (b1<<8) + b2;
}

#if !defined(ENDIAN_LITTLE) && !defined(ENDIAN_BIG)
short   ShortNoSwap (short l)
{
	return l;
}
#endif

int    LongSwap (int l)
{
	byte    b1,b2,b3,b4;

	b1 = l&255;
	b2 = (l>>8)&255;
	b3 = (l>>16)&255;
	b4 = (l>>24)&255;

	return ((int)b1<<24) + ((int)b2<<16) + ((int)b3<<8) + b4;
}

#if !defined(ENDIAN_LITTLE) && !defined(ENDIAN_BIG)
int     LongNoSwap (int l)
{
	return l;
}
#endif

float FloatSwap (float f)
{
	union
	{
		float   f;
		byte    b[4];
	} dat1, dat2;


	dat1.f = f;
	dat2.b[0] = dat1.b[3];
	dat2.b[1] = dat1.b[2];
	dat2.b[2] = dat1.b[1];
	dat2.b[3] = dat1.b[0];
	return dat2.f;
}

#if !defined(ENDIAN_LITTLE) && !defined(ENDIAN_BIG)
float FloatNoSwap (float f)
{
	return f;
}
#endif

