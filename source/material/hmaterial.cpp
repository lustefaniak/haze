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
#include "hmaterial.h" // class's header file

// class constructor
HMaterial::HMaterial(string name) {
    // insert your code here
    m_iNumPasses=0;
    m_sName=name;
    memset(&m_mpPasses[0],0,sizeof(hmaterialpass_s)*6);
    Load(name);
}

HMaterial::HMaterial() {
    HMaterial("");
}

// class destructor
HMaterial::~HMaterial() {
    // insert your code here
}

#define gettoken() parser.GetToken()
#define getstring() parser.GetString()
#define prewind() parser.RewindLast()
#define tif(a) if (( strcmp ( a, parser.GetBuffer() ) == 0 ))
#define tcheck(a) {if ( strcmp ( a, parser.GetBuffer() ) != 0 )\
{       hlog("Expected:\t%s\nFound:\t%s(%d)\n",a,parser.GetBuffer(),__LINE__); return false;}}
#define bufferf() atof(parser.GetBuffer())
#define bufferi() atof(parser.GetBuffer())
#define buffer() parser.GetBuffer()

// wczytuje material z pliku
int HMaterial::Load(string filename) {
    guard(HMaterial::Load());
    /* TODO (#1#): Implement HMaterial::Load() */
    if (filename.empty())return 0;
    HParser parser;
    if (!parser.StartParse(filename)) return 0;
    gettoken();
    tif("{") {
        hlog("Parsing material %s\n",filename.c_str());
        while (gettoken()) {
            tif("map") {
                getstring();
                m_mpPasses[m_iNumPasses].textureid=HTextureManager::GetSingleton().Load(strdup(buffer()));
                m_mpPasses[m_iNumPasses].texgenmode=TGM_NORMAL;
                m_mpPasses[m_iNumPasses].passmode=PM_NORMAL;
                m_iNumPasses+=1;
            }
            else tif("lightmap") {
                m_mpPasses[m_iNumPasses].texgenmode=TGM_LIGHTMAP;
                m_mpPasses[m_iNumPasses].passmode=PM_LIGHTMAP;
                m_iNumPasses+=1;
            }
            else tif("glow") {
                getstring();
                m_mpPasses[m_iNumPasses].textureid=HTextureManager::GetSingleton().Load(buffer());
                m_mpPasses[m_iNumPasses].texgenmode=TGM_NORMAL;
                m_mpPasses[m_iNumPasses].passmode=PM_GLOW;
                m_iNumPasses+=1;
            }
            else tif("env") {
                getstring();
                m_mpPasses[m_iNumPasses].textureid=HTextureManager::GetSingleton().Load(buffer());
                m_mpPasses[m_iNumPasses].texgenmode=TGM_ENVIRONMENT;
                m_mpPasses[m_iNumPasses].passmode=PM_NORMAL;
                m_iNumPasses+=1;
            }
            else tif("mask") {
                getstring();
                m_mpPasses[m_iNumPasses].textureid=HTextureManager::GetSingleton().Load(strdup(buffer()));
                m_mpPasses[m_iNumPasses].texgenmode=TGM_NORMAL;
                m_mpPasses[m_iNumPasses].passmode=PM_MASK;
                m_iNumPasses+=1;
            }
            else tif("bump") {
                getstring();
                m_mpPasses[m_iNumPasses].textureid=HTextureManager::GetSingleton().Load(buffer());
                m_mpPasses[m_iNumPasses].texgenmode=TGM_NORMAL;
                if (m_iNumPasses==0)    m_mpPasses[m_iNumPasses].passmode=PM_BUMPMAP;
                else {
                    m_mpPasses[m_iNumPasses].passmode==PM_NONE;
                    m_mpPasses[m_iNumPasses].texgenmode=TGM_NONE;
                    debug("Bumpmap must be first pass!!!");
                    //fflush(stdout);
                }
                m_iNumPasses+=1;
            }

            tif("}") {
//  prewind();
                break;
            }
        }
        /*  gettoken();
            tcheck("}");*/
    }

    return 1;
    unguard;
}

