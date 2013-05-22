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

#ifndef HMATERIAL_H
#define HMATERIAL_H

//#include "../Haze.h"

enum eTexGenMode{
    TGM_NORMAL=0,
    TGM_LIGHTMAP,
    TGM_ENVIRONMENT,
    TGM_NONE
};

enum ePassMode{
    PM_NORMAL=0,
    PM_BUMPMAP,
    PM_LIGHTMAP,
    PM_MASK,
    PM_GLOW,
    PM_CARTOON,
    PM_NONE
};

/*
 * material taki sobie po prostu
 */
class HMaterial {
public:
    // class constructor
    HMaterial(string name);
    HMaterial();
    // class destructor
    ~HMaterial();
    typedef struct hmaterialpass_s {
        ePassMode passmode;
        int textureid;
        int cullmode;
        eTexGenMode texgenmode;
    }
    hmaterialpass_t;
    hmaterialpass_s m_mpPasses[6];
    int m_iNumPasses;
    string m_sName;
    int m_iManagerID;
    // wczytuje material z pliku
    int Load(string filename);
};

#endif // HMATERIAL_H

