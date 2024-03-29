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
   TODO
      - should i have all this stuff inlined?

   0  4  8  12
   1  5  9  13
   2  6  10 14
   3  7  11 15
*/

#include "matrix.h"

matrix_t matrix_t::operator*(const matrix_t &src)
{
   matrix_t ret;

   ret.m[0] = m[0]  * src.m[0] + m[1]  * src.m[4] + m[2]  * src.m[8]  + m[3] * src.m[12];
   ret.m[1] = m[0]  * src.m[1] + m[1]  * src.m[5] + m[2]  * src.m[9]  + m[3] * src.m[13];
   ret.m[2] = m[0]  * src.m[2] + m[1]  * src.m[6] + m[2]  * src.m[10] + m[3] * src.m[14];
   ret.m[3] = m[0]  * src.m[3] + m[1]  * src.m[7] + m[2]  * src.m[11] + m[3] * src.m[15];

   ret.m[4] = m[4]  * src.m[0] + m[5]  * src.m[4] + m[6]  * src.m[8]  + m[7] * src.m[12];
   ret.m[5] = m[4]  * src.m[1] + m[5]  * src.m[5] + m[6]  * src.m[9]  + m[7] * src.m[13];
   ret.m[6] = m[4]  * src.m[2] + m[5]  * src.m[6] + m[6]  * src.m[10] + m[7] * src.m[14];
   ret.m[7] = m[4]  * src.m[3] + m[5]  * src.m[7] + m[6]  * src.m[11] + m[7] * src.m[15];

   ret.m[8] = m[8]  * src.m[0] + m[9]  * src.m[4] + m[10] * src.m[8]  + m[11] * src.m[12];
   ret.m[9] = m[8]  * src.m[1] + m[9]  * src.m[5] + m[10] * src.m[9]  + m[11] * src.m[13];
   ret.m[10]= m[8]  * src.m[2] + m[9]  * src.m[6] + m[10] * src.m[10] + m[11] * src.m[14];
   ret.m[11]= m[8]  * src.m[3] + m[9]  * src.m[7] + m[10] * src.m[11] + m[11] * src.m[15];

   ret.m[12]= m[12] * src.m[0] + m[13] * src.m[4] + m[14] * src.m[8]  + m[15] * src.m[12];
   ret.m[13]= m[12] * src.m[1] + m[13] * src.m[5] + m[14] * src.m[9]  + m[15] * src.m[13];
   ret.m[14]= m[12] * src.m[2] + m[13] * src.m[6] + m[14] * src.m[10] + m[15] * src.m[14];
   ret.m[15]= m[12] * src.m[3] + m[13] * src.m[7] + m[14] * src.m[11] + m[15] * src.m[15];

   return ret;
}

void matrix_t::operator*=(const matrix_t &src)
{
   (*this) = (*this) * src;
}

// Took this from the OpenGL man pages for glRotate
void matrix_t::Rotate(float angle, vec3_t vec)
{
   matrix_t ret;
   float c = mLibCos(angle);
   float s = mLibSin(angle);
   float mc = 1 - c;
   float x = vec[0];
   float y = vec[1];
   float z = vec[2];

   ret.m[0] = (x * x * mc) + c;
   ret.m[1] = (y * x * mc) + (z * s);
   ret.m[2] = (x * z * mc) - (y * s);
   ret.m[4] = (x * y * mc) - (z * s);
   ret.m[5] = (y * y * mc) + c;
   ret.m[6] = (y * z * mc) + (x * s);
   ret.m[8] = (x * z * mc) + (y * s);
   ret.m[9] = (y * z * mc) - (x * s);
   ret.m[10] = (z * z * mc) + c;

   (*this) = (*this) * ret;
}

void matrix_t::Translate(vec3_t vec)
{
   matrix_t t;
   
   t.m[12] = vec[0];
   t.m[13] = vec[1];
   t.m[14] = vec[2];
   
   (*this) = (*this) * t;
}

void matrix_t::Translate(float x, float y, float z)
{
   matrix_t t;
   
   t.m[12] = x;
   t.m[13] = y;
   t.m[14] = z;
   
   (*this) = (*this) * t;
}

void matrix_t::RotateX(float angle)
{
   float c = mLibCos(angle);
   float s = mLibSin(angle);

   m[5] = c;   
   m[6] = s;
   m[9] = -s;  
   m[10] = c;   
}

void matrix_t::RotateY(float angle)
{
   float c = mLibCos(angle);
   float s = mLibSin(angle);

   m[0] = c;   
   m[2] = -s;
   m[8] = s;  
   m[10] = c;
}

void matrix_t::RotateZ(float angle)
{
   float c = mLibCos(angle);
   float s = mLibSin(angle);

   m[0] = c;   
   m[1] = s;
   m[4] = -s;  
   m[5] = c;
}
// taken from SGI's sample GL implementation, should work 
bool matrix_t::Inverse(matrix_t &inv)
{
   int i, j, k, swap;
   float t;
   float temp[4][4];

   for (i = 0; i < 4; i++)
	   for (j = 0; j < 4; j++)
         temp[i][j] = m[(i * 4) + j];

   inv.Identity();

   for (i = 0; i < 4; i++)
   {
      /*
      ** Look for largest element in column
      */
      swap = i;
      for (j = i + 1; j < 4; j++)
         if (fabs(temp[j][i]) > fabs(temp[i][i]))
            swap = j;
   
      if (swap != i)
      {
         /*
         ** Swap rows.
         */
         for (k = 0; k < 4; k++)
         {
            t = temp[i][k];
            temp[i][k] = temp[swap][k];
            temp[swap][k] = t;

            t = inv.m[(i * 4) + k];
            inv.m[(i * 4) + k] = inv.m[(swap * 4) + k];
            inv.m[(swap * 4) + k] = t;
         }
      }

      /*
      ** No non-zero pivot.  The matrix is singular, which shouldn't
      ** happen.  This means the user gave us a bad matrix.
      */
      if (temp[i][i] == 0)
         return 0;

      t = temp[i][i];
      for (k = 0; k < 4; k++)
      {
         temp[i][k] /= t;
         inv.m[(i * 4) + k] /= t;
      }
      for (j = 0; j < 4; j++)
      {
         if (j != i)
         {
            t = temp[j][i];
            for (k = 0; k < 4; k++)
            {
               temp[j][k] -= temp[i][k] * t;
               inv.m[(j * 4) + k] -= inv.m[(i * 4) + k] * t;
            }
         }
      }
   }
   return 1;
}
