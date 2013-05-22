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

#ifndef HTEXTUREMANAGER_H
#define HTEXTUREMANAGER_H

#include "htexture.h"
#include "htexturenormalizationcubemap.h"

class HTexture;

typedef map<int,HTexture*> tTextures;

/*
 * manager wszystkich tekstur
 */
class HTextureManager : public Singleton<HTextureManager> {
public:
    // class constructor
    HTextureManager();
    // class destructor
    ~HTextureManager();
    // aduje tekstur�z pliku lub z czego innego i zwraca wewn�rzny id
    int Load(string name);
    // wysya tekstur�do karty
    int Bind(int texmgrid);
    // robi updejt teksturom
    int Update();
    // zwraca wskanik do konkretnej tekstury
    HTexture * GetTexture(int texmgrid);
    // zwalnia tekstur�o danym id
    int UnLoad(int id);
    // wywala raport na temat wykoystania zasob�
    void DumpReport();
    // wywala wszystko co si�da
    void FlushData();
protected:
    map<int,HTexture*> m_pTextures;
    map<string,HTexture*> m_pTexturesByName;
};

extern HTextureManager * gHTextureManager;

#endif // HTEXTUREMANAGER_H

