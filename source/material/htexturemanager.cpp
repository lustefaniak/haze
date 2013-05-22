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

#include <cctype>       // std::tolower
#include "../Haze.h"
#include "htexturemanager.h" // class's header file
#include "htexturefile.h"

template<> HTextureManager* Singleton<HTextureManager>::ms_Singleton = 0;

int TextureCounter=1;

HTextureManager * gHTextureManager=NULL;

// class constructor
HTextureManager::HTextureManager() {
    // insert your code here
    if (gHTextureManager==NULL) {
        gHTextureManager=this;
    }
}

// class destructor
HTextureManager::~HTextureManager() {
    tTextures::iterator iter;
    pair<int,HTexture*> p;
    HTexture *tex;
    for (iter=m_pTextures.begin();iter!=m_pTextures.end();++iter) {
        p=*iter;
        tex=p.second;
        delete tex;
    }
    if (gHTextureManager==this) {
        gHTextureManager=NULL;
    }
}

// aduje tekstur�z pliku lub z czego innego i zwraca wewn�rzny id
int HTextureManager::Load(string name) {
    /* TODO (#1#): Implement HTextureManager::Load() */
    std::transform(name.begin(), name.end(), name.begin(),
                   (int(*)(int)) std::tolower);

    tTextures::iterator iter;
    pair<int,HTexture*> p;
    int i=-1;
    HTexture *tex=NULL;
//    if(m_pTexturesByName.count(name)){
    tex=m_pTexturesByName[name];
    if (tex) {
        int id=tex->m_iManagerID;
//    debug("--returning texture id of %s: %d\n",name.c_str(),id);
        tex->m_iReferences++;
        return id;
        /*  for(iter=m_pTextures.begin();iter!=m_pTextures.end();++iter){
            p=*iter;
            tex=p.second;
            if(tex->GetName()==name){
            i=p.first;
            return i;
            }*/
    }

    HTextureFile * tex2=NULL;
    hlog("--loading texture %s\n",name.c_str());
    tex2=new HTextureFile("textures/"+name+".png");

    if (!tex2->GetOpenGLID()) {
//    debug("error loading!!!\n");
    }
    tex2->m_iReferences=1;
    m_pTextures[TextureCounter]=tex2;
    m_pTexturesByName[name]=tex2;
    i=TextureCounter;
    tex2->m_iManagerID=TextureCounter;
    TextureCounter++;
//  debug("TextureCounter = %d\n",TextureCounter);
//    TextureCounter++;

    if (!tex2->GetOpenGLID()) {
        return -1;
    }

    //  if(i==-1)debug("co jest bardzo nie tak z managerem tekstur!!!\n");
    return i;
}

// wysya tekstur�do karty
int HTextureManager::Bind(int texmgrid) {
    /* TODO (#1#): Implement HTextureManager::Bind() */
    HTexture * tex;
    if (m_pTextures.count(texmgrid)) {
        tex=m_pTextures[texmgrid];
        glEnable(GL_TEXTURE_2D);
        return tex->Bind();
    } else {
        glBindTexture(GL_TEXTURE_2D,0);
        glDisable(GL_TEXTURE_2D);
    }
    return 0;
}

// zwraca wskanik do konkretnej tekstury
HTexture * HTextureManager::GetTexture(int texmgrid) {
    /* DONE (#1#): Implement HTextureManager::GetTexture() */
    if (m_pTextures.count(texmgrid)) {
        return m_pTextures[texmgrid];
    }
    return NULL;
}

// robi updejt teksturom
int HTextureManager::Update() {
    /* DONE (#1#): Implement HTextureManager::Update() */
    tTextures::iterator iter;
    pair<int,HTexture*> p;
    HTexture *tex;
    for (iter=m_pTextures.begin();iter!=m_pTextures.end();++iter) {
        p=*iter;
        tex=p.second;
        if (tex==NULL) continue;
        tex->Update();
    }
    return 1;
}

// zwalnia tekstur�o danym id
int HTextureManager::UnLoad(int id) {
    /* TODO (#1#): Implement HTextureManager::UnLoad() */
    HTexture * tex;
    if (m_pTextures.count(id)) {
        tex=m_pTextures[id];
        if (tex->m_iReferences>1) {
            tex->m_iReferences--;
            return tex->m_iReferences;
        }
//    delete tex;
        return 0;
    } else {
        hlog("Texture %d was already unloaded!\n",id);
    }
    return 0;
}

// wywala wszystko co si�da
void HTextureManager::FlushData() {
    /* TODO (#1#): Implement HTextureManager::FlushData() */
}

// wywala raport na temat wykoystania zasob�
void HTextureManager::DumpReport() {
    /* TODO (#1#): Implement HTextureManager::DumpReport() */

    tTextures::iterator iter;
    pair<int,HTexture*> p;
    int num=0;
    HTexture *tex=NULL;
    hlog("Texture report:\n");
    for (iter=m_pTextures.begin();iter!=m_pTextures.end();++iter) {
        num++;
        p=*iter;
        tex=p.second;
        hlog("\t%s\n",tex->m_sName.c_str());
        hlog("\t\tid: %d | w:%d | h:%d | references:%d\n",tex->m_iManagerID,tex->m_uiWidth,tex->m_uiHeight,tex->m_iReferences);
    }
    hlog("%d textures in memory\n",num);
}

