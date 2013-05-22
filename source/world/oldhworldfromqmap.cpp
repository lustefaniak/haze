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
#include "hworldfromqmap.h" // class's header file

// class constructor
HWorldFromQMap::HWorldFromQMap() {
    // insert your code here
    m_pParser=NULL;
}

// class destructor
HWorldFromQMap::~HWorldFromQMap() {
    // insert your code here
}

// parsuje map�quake'ow
int HWorldFromQMap::Import(string filename, int flags) {
    /* TODO (#1#): Implement HWorldFromQMap::Import() */

    if (filename.empty()) {
        hlog("-HWorldFromQMap::Import() - no filename given!!!\n");
        return 0;
    }
    hlog("-HWorldFromQMap::Import()...\n");
    m_pParser=new HParser;
    assert(m_pParser);
    if (!m_pParser->StartParse(filename)) {
        delete m_pParser;
        m_pParser=NULL;
        return 0;
    }
    HEngineCore::GetSingleton().SetLoadingScreenTitle("Parsing map \""+filename+"\"");
    HEngineCore::GetSingleton().LoadingScreenUpdate(0);
    hlog("-HWorldFromQMap::Import() parsing %s...\n",filename.c_str());
    float start=HTimer::GetSingleton().GetCurrentTime();
    start=HTimer::GetSingleton().GetCurrentTime();
    start=HTimer::GetSingleton().GetCurrentTime();
    Parse();
    HEngineCore::GetSingleton().LoadingScreenUpdate(1);
    hlog("-HWorldFromQMap::Import() parsing done... (%.2f seconds elapsed)\n",(float)(HTimer::GetSingleton().GetCurrentTime()-start)/1000);
    fflush(stdout);
    delete m_pParser;
    m_pParser=NULL;
    int i=0;
    int j=0;
    int k=0;

    hlog("-HWorldFromQMap::Import() compiling brushes...\n");
    HEngineCore::GetSingleton().SetLoadingScreenTitle("Compiling geometry");
    HEngineCore::GetSingleton().LoadingScreenUpdate(0);
    start=HTimer::GetSingleton().GetCurrentTime();
    for (i=0;i<m_Brushes.num;i++) {
        HEngineCore::GetSingleton().LoadingScreenUpdate((float)i/m_Brushes.num);
        m_Brushes[i]->Compile();
    }
    hlog("-HWorldFromQMap::Import() compilation done... (%.2f seconds elapsed)\n",(float)(HTimer::GetSingleton().GetCurrentTime()-start)/1000);
    fflush(stdout);
    hlog("-HWorldFromQMap::Import() performing csg on brushes...\n");
    HEngineCore::GetSingleton().SetLoadingScreenTitle("Compiling geometry");
    HEngineCore::GetSingleton().LoadingScreenUpdate(0);
    start=HTimer::GetSingleton().GetCurrentTime();

    /*  HGBBox box;
        for(i=0;i<m_WorldBrushes.num;i++){
        box.Expand(m_WorldBrushes[i]->m_BBox.min);
        box.Expand(m_WorldBrushes[i]->m_BBox.max);
        }
        HGBrush *outside=NULL;
        outside=CreateBrush();
        HGBrushPlane plane;
        plane.n=vec3_t(0,0,-1);
        plane.d=box.max[2];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);
        outside=CreateBrush();
        plane.n=vec3_t(0,1,0);
        plane.d=box.min[1];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);
        outside=CreateBrush();
        plane.n=vec3_t(0,-1,0);
        plane.d=box.max[1];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);
        outside=CreateBrush();
        plane.n=vec3_t(-1,0,0);
        plane.d=box.max[0];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);
    */


    /*  outside=CreateBrush();
        m_WorldBrushes.Add(outside);
        plane.n=vec3_t(0,-1,0);
        plane.d=box.max[1];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);
        outside=CreateBrush();
        plane.n=vec3_t(0,1,0);
        plane.d=box.min[1];
        outside->AddPlane(plane);
        m_WorldBrushes.Add(outside);*/
//  outside=CreateBrush();

    HGPoly * poly=NULL;
    bool removed=false;
    for (i=0;i<m_WorldBrushes.num;i++) {
        HEngineCore::GetSingleton().LoadingScreenUpdate((float)i/(m_WorldBrushes.num*2));
        for (j=0;(j>=0)&&(j<m_WorldBrushes[i]->m_Polys.num);) {
            poly=m_WorldBrushes[i]->m_Polys[j];
            removed=false;
            for (k=0;k<m_WorldBrushes.num;k++) {
                if (k==i) continue;
                if (m_WorldBrushes[k]->PolyInside(poly)) {
                    m_WorldBrushes[i]->m_Polys.Remove(poly);
                    delete poly;
                    poly=NULL;
                    removed=true;
                    break;
                }
            }
            if (!removed)j++;
        }
    }

    for (i=0;i<m_WorldBrushes.num;i++) {
        HEngineCore::GetSingleton().LoadingScreenUpdate((0.5f+(float)i/(m_WorldBrushes.num*2)));
        for (j=0;(j>=0)&&(j<m_WorldBrushes[i]->m_BasePolys.num);) {
            poly=m_WorldBrushes[i]->m_BasePolys[j];
            removed=false;
            for (k=0;k<m_WorldBrushes.num;k++) {
                if (k==i) continue;
                if (m_WorldBrushes[k]->PolyInside(poly)) {
                    /*  debug("Removing base poly\n");
                        debug("i %d j %d k %d\n",i,j,k);*/
                    fflush(stdout);
                    m_WorldBrushes[i]->m_BasePolys.Remove(poly);
                    delete poly;
                    poly=NULL;
                    removed=true;
                    break;
                } /*else {
                    HGPoly *newpoly;
                    newpoly=new HGPoly;
                    *newpoly=*poly;
                    m_WorldBrushes[i]->m_Polys.Add(newpoly);
                    }*/
            }
            if (!removed)j++;
        }
    }
//  debug("numBrushes: %d\n",m_WorldBrushes.num);
    for (i=0;i<m_WorldBrushes.num;i++) {
//  for(i=0;i<3;i++){
        for (j=0;j<m_WorldBrushes.num;j++) {
//  for(j=0;j<5;j++){
            if (i==j) continue;
//  debug("brush%d->CSGUnion(brush%d)\n",i,j);
//  fflush(stdout);
            m_WorldBrushes[i]->CSGUnion(m_WorldBrushes[j]);

        }
    }
    hlog("-HWorldFromQMap::Import() csg done... (%.2f seconds elapsed)\n",(float)(HTimer::GetSingleton().GetCurrentTime()-start)/1000);
    fflush(stdout);
    hlog("-HWorldFromQMap::Import() building bsp tree...\n");
    start=HTimer::GetSingleton().GetCurrentTime();
    for (i=0;i<m_WorldBrushes.num;i++) {
        for (j=0;j<m_WorldBrushes[i]->m_Polys.num;j++) {
            m_BSP.AddPoly(m_WorldBrushes[i]->m_Polys[j]);

        }
    }
    m_BSP.Build();

    hlog("-HWorldFromQMap::Import() bsp operations done... (%.2f seconds elapsed)\n",(float)(HTimer::GetSingleton().GetCurrentTime()-start)/1000);
    fflush(stdout);

    if (!(flags&HMAP_NOLIGHT)) {
        hlog("-HWorldFromQMap::Import() lighting brushes...\n");
        HEngineCore::GetSingleton().SetLoadingScreenTitle("Generating lightmaps");
        HEngineCore::GetSingleton().LoadingScreenUpdate(0);
        start=HTimer::GetSingleton().GetCurrentTime();
        for (i=0;i<m_Brushes.num;i++) {
            HEngineCore::GetSingleton().LoadingScreenUpdate((float)i/m_Brushes.num);
            for (j=0;j<m_Brushes[i]->m_Polys.num;j++) {
                HLightmapGenerator::GetSingleton().Generate(this,m_Brushes[i]->m_Polys[j]);
            }
        }
        hlog("-HWorldFromQMap::Import() lighting done... (%.2f seconds elapsed)\n",(float)(HTimer::GetSingleton().GetCurrentTime()-start)/1000);
    }
    hlog("-HWorldFromQMap::Import() done...\n");
    fflush(stdout);
}

#define gettoken() m_pParser->GetToken()
#define getstring() m_pParser->GetString()
#define prewind() m_pParser->RewindLast()
#define tif(a) if (( strcmp ( a, m_pParser->GetBuffer() ) == 0 ))
#define tcheck(a) {if ( strcmp ( a, m_pParser->GetBuffer() ) != 0 )\
{       printf("Expected:\t%s\nFound:\t%s(%d)\n",a,m_pParser->GetBuffer(),__LINE__); return false;}}
#define bufferf() atof(m_pParser->GetBuffer())
#define bufferi() atof(m_pParser->GetBuffer())


// parsuje bufor
int HWorldFromQMap::Parse() {
    /* TODO (#1#): Implement HWorldFromQMap::Parse() */
    gettoken();
    tcheck("{");
    gettoken();
    tcheck("\"classname\"");
    gettoken();
    tcheck("\"worldspawn\"");
    while (getstring()) {

    }
    HGBrush *b=NULL;
    HGBrushPlane plane;
    vec3_t points[3];
    int i=0;
    while (true) {//parsuje brushe
        gettoken();
        tif("{") {
            b=CreateBrush();
            assert(b);
            m_WorldBrushes.Add(b);
            while (true) {//parsuje plane'y
                gettoken();
                tif("(") {
                    for (i=0;i<3;i++) {
                        tcheck("(");
                        gettoken();
                        points[i][0]=bufferf();
                        gettoken();
                        points[i][2]=-bufferf();
                        gettoken();
                        points[i][1]=bufferf();
                        gettoken();
                        tcheck(")");
                        gettoken();
                    }
                    plane.CalcNormal(points[0],points[1],points[2]);
                    plane.material=HMaterialManager::GetSingleton().LoadMaterial(m_pParser->GetBuffer());
                    plane.texture=HTextureManager::GetSingleton().Load(m_pParser->GetBuffer());
//debug("texture id:%d\n",plane.texture);
//teraz w buforze jest tekstura
                    gettoken();
                    for (i=0;i<2;i++) {
                        tcheck("[");
                        gettoken();
                        plane.texplanes[i].n[0]=bufferf();
                        gettoken();
                        plane.texplanes[i].n[2]=-bufferf();
                        gettoken();
                        plane.texplanes[i].n[1]=bufferf();
                        gettoken();
                        plane.texplanes[i].d=bufferf();
                        gettoken();
                        tcheck("]");
                        gettoken();
                    }
//teraz ju co mamy
                    plane.texrotation=bufferf();
                    gettoken();
                    plane.texscale[0]=bufferf();
                    gettoken();
                    plane.texscale[1]=bufferf();

                    b->AddPlane(plane);

                }
                else {
                    prewind();
                    break;
                }
            }



            gettoken();
            tcheck("}");

        }
        else {
            prewind();
            break;
        }
    }

    gettoken();
    tcheck("}");
    HLight light;
    while (true) {
//    memset(&light,0,sizeof(HLight));
        gettoken();
        tif("{") {
        }
        else {
            return 1;
        }

        tcheck("{");
        gettoken();
        tcheck("\"classname\"");
        gettoken();
        tif("\"light\"") {
//  debug("omni light found...\n");
            light.m_bSpotlight=false;
            while (getstring()) {
                tif("origin") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f",&light.m_Position[0],&light.m_Position[2],&light.m_Position[1]);
                    light.m_Position[2]=-light.m_Position[2];
                }
                else tif("_light") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f %f",&light.m_Color[0],&light.m_Color[1],&light.m_Color[2],&light.m_Brightness);
                }
                else {
                    getstring();
                }
            }
//    debug("light params: pos[%f %f %f] color[%f %f %f] brightness[%f]\n",light.m_Position[0],light.m_Position[1],light.m_Position[2],light.m_Color[0],light.m_Color[1],light.m_Color[2],light.m_Brightness);
            m_LightSystem.AddLight(light);
            gettoken();
            tcheck("}");
            continue;
        }
        else tif("\"info_player_start\"") {
//  debug("player start location found...\n");
            while (getstring()) {
                tif("origin") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f",&HEngineCore::GetSingleton().m_pCamera->m_vPosition[0],&HEngineCore::GetSingleton().m_pCamera->m_vPosition[2],&HEngineCore::GetSingleton().m_pCamera->m_vPosition[1]);
                    HEngineCore::GetSingleton().m_pCamera->m_vPosition[2]=-HEngineCore::GetSingleton().m_pCamera->m_vPosition[2];
                }
                else tif("angles") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f",&HEngineCore::GetSingleton().m_pCamera->m_fYaw,&HEngineCore::GetSingleton().m_pCamera->m_fPitch,&HEngineCore::GetSingleton().m_pCamera->m_fRoll);
                }
                else {
                    getstring();
                }
            }
            gettoken();
            tcheck("}");
            continue;
        }
        else tif("\"light_spot\"") {
//  debug("spot light found...\n");
            light.m_bSpotlight=true;
            light.m_Direction.Set(0,-1,0);
            while (getstring()) {
                tif("origin") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f",&light.m_Position[0],&light.m_Position[2],&light.m_Position[1]);
                    light.m_Position[2]=-light.m_Position[2];
                }
                else tif("_light") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f %f",&light.m_Color[0],&light.m_Color[1],&light.m_Color[2],&light.m_Brightness);
                }
                else tif("direction") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f %f %f",&light.m_Direction[0],&light.m_Direction[1],&light.m_Direction[2]);
                    light.m_Direction.Normalize();
                }
                else tif("_cone") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f",&light.m_InnerAngle);
                }
                else tif("_cone2") {
                    getstring();
                    sscanf(m_pParser->GetBuffer(),"%f",&light.m_OuterAngle);
                }
                else {
                    getstring();
                }
            }
//    debug("light params: pos[%f %f %f] color[%f %f %f] direction[%f %f %f] anglei[%f] angleo[%f] brightness[%f]\n",light.m_Position[0],light.m_Position[1],light.m_Position[2],light.m_Color[0],light.m_Color[1],light.m_Color[2],light.m_Direction[0],light.m_Direction[1],light.m_Direction[2],light.m_InnerAngle,light.m_OuterAngle,light.m_Brightness);
            m_LightSystem.AddLight(light);
            gettoken();
            tcheck("}");
            continue;

        }
        else {
            prewind();
        }
        /*  gettoken();
            tcheck("\"worldspawn\"");*/
        while (getstring()) {

        }
        HGBrush *b=NULL;
        HGBrushPlane plane;
        vec3_t points[3];
        int i=0;
        while (true) {//parsuje brushe
            gettoken();
            tif("{") {
                b=CreateBrush();
                assert(b);
                while (true) {//parsuje plane'y
                    gettoken();
                    tif("(") {
                        for (i=0;i<3;i++) {
                            tcheck("(");
                            gettoken();
                            points[i][0]=bufferf();
                            gettoken();
                            points[i][2]=-bufferf();
                            gettoken();
                            points[i][1]=bufferf();
                            gettoken();
                            tcheck(")");
                            gettoken();
                        }
                        plane.CalcNormal(points[0],points[1],points[2]);
                        plane.material=HMaterialManager::GetSingleton().LoadMaterial(m_pParser->GetBuffer());
                        plane.texture=HTextureManager::GetSingleton().Load(m_pParser->GetBuffer());

//debug("texture id:%d\n",plane.texture);
//teraz w buforze jest tekstura
                        gettoken();
                        for (i=0;i<2;i++) {
                            tcheck("[");
                            gettoken();
                            plane.texplanes[i].n[0]=bufferf();
                            gettoken();
                            plane.texplanes[i].n[2]=-bufferf();
                            gettoken();
                            plane.texplanes[i].n[1]=bufferf();
                            gettoken();
                            plane.texplanes[i].d=bufferf();
                            gettoken();
                            tcheck("]");
                            gettoken();
                        }
//teraz ju co mamy
                        plane.texrotation=bufferf();
                        gettoken();
                        plane.texscale[0]=bufferf();
                        gettoken();
                        plane.texscale[1]=bufferf();

                        b->AddPlane(plane);

                    }
                    else {
                        prewind();
                        break;
                    }
                }



                gettoken();
                tcheck("}");

            }
            else {
                prewind();
                break;
            }
        }

        gettoken();
        tcheck("}");

    }


}

