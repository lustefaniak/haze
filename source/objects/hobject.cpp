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

#include "../Haze.h" // class's header file

// class constructor
HObject::HObject(HLevel * level) {
    // insert your code here
    m_pLevel=level;
}

// class destructor
HObject::~HObject() {
    // insert your code here
}

RegisterObject(object,HObject)

// dodaje poly do listy tego co ma w sobie
void HObject::AddGeometry(HGPoly * poly) {
    /* TODO (#1#): Implement HObject::AddGeometry() */
    m_Polys.Add(poly);
}

