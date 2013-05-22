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

#ifndef HGBBOX_H
#define HGBBOX_H

//#include "hgbrush.h"

//class HGBrush;

/*
 * bounding box czego tam
 */
class HGBBox {
public:
    // class constructor
    HGBBox();
    // class destructor
    ~HGBBox();
    vec3_t min;
    vec3_t max;
    // sprawdza czy punkt w bounding boxie si�znajduje
    bool InBBox(vec3_t &v);
    // sprawdza czy punkt mieci si�w  bbox, jak nie to zwi�sza bboxa
    bool Expand(vec3_t &v);
    // sprawdza czy bboxy maj cz� wsp�n
    bool Intersect(HGBBox * box);
    // resetuje bbox
    void Reset();
    // generuje bbox z brusha
//      void Build(HGBrush * brush);
};

#endif // HGBBOX_H

