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
#include "hgbbox.h" // class's header file

// class constructor
HGBBox::HGBBox() {
    // insert your code here
    max.Set(-3.40282347e+38F);
    min.Set(3.40282347e+38F);

}

// class destructor
HGBBox::~HGBBox() {
    // insert your code here
}

// sprawdza czy punkt w bounding boxie si�znajduje
bool HGBBox::InBBox(vec3_t &v) {
    /* DONE (#1#): Implement HGBBox::InBBox() */
    if (v<=max&&v>=min) return true;
    return false;
}

// sprawdza czy punkt mieci si�w  bbox, jak nie to zwi�sza bboxa
bool HGBBox::Expand(vec3_t &v) {
    /* DONE (#1#): Implement HGBBox::Expand() */
    if (v[0]>max[0]) max[0]=v[0];
    if (v[1]>max[1]) max[1]=v[1];
    if (v[2]>max[2]) max[2]=v[2];
    if (v[0]<min[0]) min[0]=v[0];
    if (v[1]<min[1]) min[1]=v[1];
    if (v[2]<min[2]) min[2]=v[2];
    return true;
}

// generuje bbox z brusha
//void HGBBox::Build(HGBrush * brush)
//{
//  /* TODO (#1#): Implement HGBBox::Build() */
//  max.Set(-3.40282347e+38F);
//  min.Set(3.40282347e+38F);
//}*/

// sprawdza czy bboxy maj cz� wsp�n
bool HGBBox::Intersect(HGBBox * box) {
    /* DONE (#1#): Implement HGBBox::Intersect() */
    if ( ( min[0] > box->max[0] ) || ( box->min[0] > max[0] ) ) {
        return false;
    }

    if ( ( min[1] > box->max[1] ) || ( box->min[1] > max[1] ) ) {
        return false;
    }

    if ( ( min[2] > box->max[2] ) || ( box->min[2] > max[2] ) ) {
        return false;
    }
    return true;
}

// resetuje bbox
void HGBBox::Reset() {
    /* DONE (#1#): Implement HGBBox::Reset() */
    max.Set(-3.40282347e+38F);
    min.Set(3.40282347e+38F);
}

