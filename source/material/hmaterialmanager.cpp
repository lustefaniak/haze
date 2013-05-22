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
#include "hmaterialmanager.h" // class's header file

template<> HMaterialManager* Singleton<HMaterialManager>::ms_Singleton = 0;

int MaterialCounter=0;

// class constructor
HMaterialManager::HMaterialManager() {
    // insert your code here
}

// class destructor
HMaterialManager::~HMaterialManager() {
    tMaterial::iterator iter;
    pair<int,HMaterial*> p;
    HMaterial *tex;
    for (iter=m_Materials.begin();iter!=m_Materials.end();++iter) {
        p=*iter;
        tex=p.second;
        delete tex;
    }
}

// zwraca id materiau
int HMaterialManager::LoadMaterial(string name) {
    std::transform(name.begin(), name.end(), name.begin(),
                   (int(*)(int)) std::tolower);
    tMaterial::iterator iter;
    pair<int,HMaterial*> p;
    int i=-1;
    HMaterial *mat=NULL;
    if (m_MaterialsByName.count(name))
        mat=m_MaterialsByName[name];
    if (mat) {
        int id=mat->m_iManagerID;
//    debug("--returning texture id of %s: %d\n",name.c_str(),id);
        return id;
        /*  for(iter=m_pTextures.begin();iter!=m_pTextures.end();++iter){
            p=*iter;
            tex=p.second;
            if(tex->GetName()==name){
            i=p.first;
            return i;
            }*/
    }

    HMaterial * mat2=NULL;
    debug("--loading material %s\n",name.c_str());
    mat2=new HMaterial("textures/"+name+".mat");
    if (mat2->m_iNumPasses==0) {
        mat2->m_iNumPasses=2;
        mat2->m_mpPasses[0].textureid=HTextureManager::GetSingleton().Load(name);
        mat2->m_mpPasses[0].texgenmode=TGM_NORMAL;
        mat2->m_mpPasses[0].passmode=PM_NORMAL;
        mat2->m_mpPasses[1].texgenmode=TGM_LIGHTMAP;
        mat2->m_mpPasses[1].passmode=PM_LIGHTMAP;
        mat2->m_mpPasses[2].textureid=HTextureManager::GetSingleton().Load(name+"_n");
        mat2->m_mpPasses[2].texgenmode=TGM_NORMAL;
        mat2->m_mpPasses[2].passmode=PM_NORMAL;
    }
    m_Materials[MaterialCounter]=mat2;
    m_MaterialsByName[name]=mat2;
    i=MaterialCounter;
    mat2->m_iManagerID=MaterialCounter;
    MaterialCounter++;

    return i;
}

// ustawia material w opengl'u
HMaterial * HMaterialManager::GetMaterial(int id) {
    /* TODO (#1#): Implement HMaterialManager::BindMaterial() */
    if (m_Materials.count(id)) {
        return m_Materials[id];
    }
    return NULL;

}

