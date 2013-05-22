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

#ifndef HMATERIALMANAGER_H
#define HMATERIALMANAGER_H

#include "hmaterial.h"

typedef map<int,HMaterial*> tMaterial;

//class HMaterial;

/*
 * klasa przechowujca matriay
 */
class HMaterialManager : public Singleton<HMaterialManager> {
public:
    // class constructor
    HMaterialManager();
    // class destructor
    ~HMaterialManager();
    // ustawia material w opengl'u
    HMaterial * GetMaterial(int id);
    // zwraca id materiau
    int LoadMaterial(string name);
protected:
    map<int,HMaterial*> m_Materials;
    map<string,HMaterial*> m_MaterialsByName;
};

#endif // HMATERIALMANAGER_H

