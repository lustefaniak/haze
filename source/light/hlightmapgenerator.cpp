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
#include "hlightmapgenerator.h" // class's header file

template<> HLightmapGenerator* Singleton<HLightmapGenerator>::ms_Singleton = 0;

// class constructor
HLightmapGenerator::HLightmapGenerator() {
    // insert your code here
}

// class destructor
HLightmapGenerator::~HLightmapGenerator() {
    // insert your code here
}

static void lmap_blur(int w, int h, unsigned char * buff) {
    int x,y,gsum,bsum,rsum,size3 = w * 3;
    unsigned char *shadow,*inp,*outp;
    shadow = (unsigned char*)malloc(w *h * 3);
    memset(shadow,0,w * h * 3);
    inp = buff + size3;
    outp = shadow + size3;
    for (y = 1; y < h - 1; y++) {
        inp += 3;
        outp += 3;
        for (x = 1; x < w - 1; x++) {
            rsum = inp[-size3 - 3] + inp[-size3]*2 + inp[-size3 + 3] +
                   inp[-3]*2 + inp[0]*4 + inp[3]*2 +
                   inp[size3 - 3] + inp[size3]*2 + inp[size3 + 3];
            rsum /= 16;
            gsum = inp[-size3 - 3+1] + inp[-size3+1]*2 + inp[-size3 + 3+1] +
                   inp[-3+1]*2 + inp[0+1]*4 + inp[3+1]*2 +
                   inp[size3 - 3+1] + inp[size3+1]*2 + inp[size3 + 3+1];
            gsum /= 16;
            bsum = inp[-size3 - 3+2] + inp[-size3+2]*2 + inp[-size3 + 3+2] +
                   inp[-3+2]*2 + inp[0+2]*4 + inp[3+2]*2 +
                   inp[size3 - 3+2] + inp[size3+2]*2 + inp[size3 + 3+2];
            bsum /= 16;
            inp += 3;
            *outp++ = rsum;
            *outp++ = gsum;
            *outp++ = bsum;
        }
        inp += 3;
        outp += 3;
    }
    memcpy(buff,shadow,w * h * 3);
    free(shadow);
}

#define powercheck(a) if(a>256) a=256;\
else if(a>128) a=128;\
else if(a>64) a=64;\
else if(a>32) a=32;\
else if(a>16) a=16;\
else if(a>8) a=8;\
else a=4;

/*#define powercheck(a) if(a>64) a=64;\
else if(a>32) a=32;\
else if(a>16) a=16;\
else if(a>8) a=8;\
else if(a>4) a=4;\
else a=2;\*/

//#define powercheck(a) a=HPower2(a)/2; if(a>128) a=128; if(a<2) a=2;
//#define powercheck(a) a=HPower2(a); if(a>64) a=64; if(a<16) a=16;
//#define powercheck(a) a=HPower2(a); a=16;

// generuje lightmap�dla takiego czego
int HLightmapGenerator::Generate(HWorld * world, HGPoly * poly) {
    /* TODO (#1#): Implement HLightmapGenerator::Generate() */
    HGBBox box;
    int i=0;
    for (i=0;i<poly->m_Verts.num;i++) {
        box.Expand(poly->m_Verts[i].pos);
    }
    enum planetype{
        xy,
        xz,
        yz
    } planetype;

    unsigned int lmapwidth=16;
    unsigned int lmapheight=16;

    if (fabs(poly->p->n[0])>=fabs(poly->p->n[1])&&fabs(poly->p->n[0])>=fabs(poly->p->n[2])) {//x najwi�szy
        planetype=yz;
    } else  if (fabs(poly->p->n[1])>=fabs(poly->p->n[0])&&fabs(poly->p->n[1])>=fabs(poly->p->n[2])) {//y najwi�szy
        planetype=xz;
    } else  if (fabs(poly->p->n[2])>=fabs(poly->p->n[1])&&fabs(poly->p->n[2])>=fabs(poly->p->n[0])) {//z najwi�szy
        planetype=xy;
    } else planetype=xy;
    for (i=0;i<poly->m_Verts.num;i++) {
        if (planetype==xy) {
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].pos[0];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].pos[1];
        }
        if (planetype==xz) {
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].pos[0];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].pos[2];
        }
        if (planetype==yz) {
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].pos[1];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].pos[2];
        }
    }
    float deltau=1;
    float deltav=1;
    float deltax;
    float deltay;
    float deltaz;
    deltax=fabs((box.max[0]-box.min[0]));
    deltay=fabs((box.max[1]-box.min[1]));
    deltaz=fabs((box.max[2]-box.min[2]));
    if (planetype==xy) {
        deltau=box.max[0]-box.min[0];
        lmapwidth=(box.max[0]-box.min[0])/2;
        deltav=box.max[1]-box.min[1];
        lmapheight=(box.max[1]-box.min[1])/2;
    }
    if (planetype==xz) {
        deltau=box.max[0]-box.min[0];
        lmapwidth=(box.max[0]-box.min[0])/2;
        deltav=box.max[2]-box.min[2];
        lmapheight=(box.max[2]-box.min[2])/2;
    }
    if (planetype==yz) {
        deltau=box.max[1]-box.min[1];
        lmapwidth=(box.max[1]-box.min[1])/2;
        deltav=box.max[2]-box.min[2];
        lmapheight=(box.max[2]-box.min[2])/2;
    }
//    lmapheight<<=1;
    /*    lmapwidth/=2;
        lmapheight/=2;*/
    lmapwidth*=2;
    lmapheight*=2;
    powercheck(lmapheight);
//    lmapwidth<<=1;
    powercheck(lmapwidth);
//    debug("lmap [%d %d]\n",lmapwidth,lmapheight);
//    fflush(stdout);
    /*    if(lmapwidth>64) lmapwidth=64;
        if(lmapwidth<1) lmapwidth=1;
        if(lmapheight>64) lmapheight=64;
        if(lmapheight<2) lmapheight=2;   */

    for (i=0;i<poly->m_Verts.num;i++) {
        if (planetype==xy) {
            poly->m_Verts[i].tex2[0]-=box.min[0];
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].tex2[0]/deltau;
            poly->m_Verts[i].tex2[1]-=box.min[1];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].tex2[1]/deltav;
        }
        if (planetype==xz) {
            poly->m_Verts[i].tex2[0]-=box.min[0];
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].tex2[0]/deltau;
            poly->m_Verts[i].tex2[1]-=box.min[2];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].tex2[1]/deltav;
        }
        if (planetype==yz) {
            poly->m_Verts[i].tex2[0]-=box.min[1];
            poly->m_Verts[i].tex2[0]=poly->m_Verts[i].tex2[0]/deltau;
            poly->m_Verts[i].tex2[1]-=box.min[2];
            poly->m_Verts[i].tex2[1]=poly->m_Verts[i].tex2[1]/deltav;
        }
//    debug("lmapcoord: [%f %f]\n",poly->m_Verts[i].tex2[0],poly->m_Verts[i].tex2[1]);
        if (poly->m_Verts[i].tex2[0]<0.0125) poly->m_Verts[i].tex2[0]+=0.0125-poly->m_Verts[i].tex2[0];
        if (poly->m_Verts[i].tex2[1]<0.0125) poly->m_Verts[i].tex2[1]+=0.0125-poly->m_Verts[i].tex2[1];
        if (poly->m_Verts[i].tex2[0]>0.9875) poly->m_Verts[i].tex2[0]+=0.9875-poly->m_Verts[i].tex2[0];
        if (poly->m_Verts[i].tex2[1]>0.9875) poly->m_Verts[i].tex2[1]+=0.9875-poly->m_Verts[i].tex2[1];
//    debug("corrected lmapcoord: [%f %f]\n",poly->m_Verts[i].tex2[0],poly->m_Verts[i].tex2[1]);
    }

    if (!poly->m_Lightmap) {
        poly->m_Lightmap=new HLightmap;
        assert(poly->m_Lightmap);
    } else {
        poly->m_Lightmap->Unload();
    }
    unsigned char *buff=NULL;
    buff=(unsigned char*)malloc(sizeof(unsigned char)*lmapwidth*lmapheight*3);
    assert(buff);
    vec3_t color;
    vec3_t pos;
    float tmp;
    vec3_t dir;
    for (int h=0;h<lmapheight;h++) {
        for (int w=0;w<lmapwidth;w++) {
            color.Set(0);

            if (planetype==xy) {
                pos[0]=box.min[0]+(deltax/lmapwidth)*w+(deltax/lmapwidth)/2;
                pos[1]=box.min[1]+(deltay/lmapheight)*h+(deltay/lmapheight)/2;
                pos[2]=-(poly->p->n[0]*pos[0]+poly->p->n[1]*pos[1]+poly->p->d)/poly->p->n[2];

            }
            if (planetype==xz) {
                pos[0]=box.min[0]+(deltax/lmapwidth)*w+(deltax/lmapwidth)/2;
                pos[2]=box.min[2]+(deltaz/lmapheight)*h+(deltaz/lmapheight)/2;
                pos[1]=-(poly->p->n[0]*pos[0]+poly->p->n[2]*pos[2]+poly->p->d)/poly->p->n[1];

            }
            if (planetype==yz) {
                pos[1]=box.min[1]+(deltay/lmapwidth)*w+(deltay/lmapwidth)/2;
                pos[2]=box.min[2]+(deltaz/lmapheight)*h+(deltaz/lmapheight)/2;
                pos[0]=-(poly->p->n[1]*pos[1]+poly->p->n[2]*pos[2]+poly->p->d)/poly->p->n[0];
            }


            if (poly->PointOnPoly(pos)) {

//    world->m_LightPoints.Add(pos);
                for (i=0;i<world->m_LightSystem.m_Lights.num;i++) {
                    if (!world->m_LightSystem.m_Lights[i].m_bSpotlight) {
                        float dist = pos.GetDistance(world->m_LightSystem.m_Lights[i].m_Position);
                        dir=world->m_LightSystem.m_Lights[i].m_Position-pos;
                        dir.Normalize();
                        float dot=poly->p->n.Dot(dir);
                        if (dot<=0) continue;
                        if (dist>world->m_LightSystem.m_Lights[i].m_Brightness*8) continue;
                        tmp=1;
                        tmp*=world->m_LightSystem.m_Lights[i].m_Brightness*world->m_LightSystem.m_Lights[i].m_Brightness;
                        tmp*=dot;
                        tmp*=Visible(pos,world->m_LightSystem.m_Lights[i].m_Position,world,poly->m_BaseID);
                        tmp/=dist*dist;
//  tmp+=tmp*0.4f;
                        if (tmp>1) tmp=1;
                        if (tmp<0) tmp=0;
                        color+=world->m_LightSystem.m_Lights[i].m_Color*tmp;
                    } else {//this is spotlight
                        dir=world->m_LightSystem.m_Lights[i].m_Position-pos;
                        dir.Normalize();
                        float dot=poly->p->n.Dot(dir);
                        if (dot<=0) continue;
                        vec3_t lumdir=pos-world->m_LightSystem.m_Lights[i].m_Position;
                        lumdir.Normalize();
                        float spotdot=lumdir.Dot(world->m_LightSystem.m_Lights[i].m_Direction);
                        float angle=INVCOS(spotdot);
                        if (angle>=world->m_LightSystem.m_Lights[i].m_OuterAngle) continue;
                        float dist = pos.GetDistance(world->m_LightSystem.m_Lights[i].m_Position);
                        if (dist>world->m_LightSystem.m_Lights[i].m_Brightness*6) continue;
                        if (angle<=world->m_LightSystem.m_Lights[i].m_InnerAngle) {
                            spotdot=1;
                        } else {
                            spotdot=1-(angle-world->m_LightSystem.m_Lights[i].m_InnerAngle)/(world->m_LightSystem.m_Lights[i].m_OuterAngle-world->m_LightSystem.m_Lights[i].m_InnerAngle);
                        }
                        tmp=1;

                        tmp*=world->m_LightSystem.m_Lights[i].m_Brightness*world->m_LightSystem.m_Lights[i].m_Brightness;
                        tmp*=Visible(pos,world->m_LightSystem.m_Lights[i].m_Position,world,poly->m_BaseID);
                        tmp*=spotdot;
//    tmp*=dot;
                        tmp/=dist*dist;
//  tmp+=tmp*0.4f;
                        if (tmp>1) tmp=1;
                        if (tmp<0) tmp=0;
                        color=color+(world->m_LightSystem.m_Lights[i].m_Color*tmp);
                    }
                }
                //color+=vec3_t(20,20,20);
                color+=vec3_t(5,5,5);

                if (color[0]>255) color[0]=255;
                if (color[1]>255) color[1]=255;
                if (color[2]>255) color[2]=255;
                if (color[0]<0) color[0]=0;
                if (color[1]<0) color[1]=0;
                if (color[2]<0) color[2]=0;
                /*  world->m_LightPoints.Add(pos);
                    world->m_LightPointsColors.Add(color);*/
                buff[w*3+h*lmapwidth*3]=(unsigned char)color[0];
                buff[w*3+h*lmapwidth*3+1]=(unsigned char)color[1];
                buff[w*3+h*lmapwidth*3+2]=(unsigned char)color[2];
            } else {
                //nie jest na poly
                buff[w*3+h*lmapwidth*3]=(unsigned char)0;
                buff[w*3+h*lmapwidth*3+1]=(unsigned char)0;
                buff[w*3+h*lmapwidth*3+2]=(unsigned char)0;

            }

        }
    }

    lmap_blur(lmapwidth,lmapheight,buff);

    poly->m_Lightmap->Load(lmapwidth,lmapheight,buff);
    free(buff);
}

// sprawdza czy punkt jest widoczny
float HLightmapGenerator::Visible(vec3_t lumelpos, vec3_t lightpos, HWorld *world, int polytoignore) {
    /* TODO (#1#): Implement HLightmapGenerator::Visible() */
//  return (rand()%10)/5;
    int i=0;
    int j=0;
    int k=0;
    int l=0;
    vec3_t dir=lumelpos-lightpos;
    vec3_t testpoint;
//  dir.Normalize();
    for (i=0;i<world->m_Brushes.num;i++) {
        if (!world->m_Brushes[i]->m_bCastShadows) continue;
        for (j=0;j<world->m_Brushes[i]->m_BasePolys.num;j++) {
            float lumeldist, lightdist;
            if (world->m_Brushes[i]->m_BasePolys[j]->m_BaseID==polytoignore) continue;
            lumeldist=world->m_Brushes[i]->m_BasePolys[j]->p->GetPointDistance(lumelpos);
            lightdist=world->m_Brushes[i]->m_BasePolys[j]->p->GetPointDistance(lightpos);
//  debug("a %f b %f\n",adist,bdist);
//  if(lightdist<0) continue;
            if ((lightdist<0)&&(lumeldist<0)) continue;
            if ((lightdist>0)&&(lumeldist>0)) continue;
//  return 0.0;
            if (!world->m_Brushes[i]->m_BasePolys[j]->p->RayIntersect(lightpos,dir,testpoint)) continue;
//  world->m_LightPoints.Add(testpoint);
            /*  world->m_LightPointsColors.Add(vec3_t(0,255,0));*/
            if (world->m_Brushes[i]->m_BasePolys[j]->PointOnPoly(testpoint)) {
                /*  world->m_LightPoints.Add(testpoint);
                    world->m_LightPointsColors.Add(vec3_t(255,0,0));*/
//  return MIN(1/(testpoint.GetDistance(lightpos)/testpoint.GetDistance(lumelpos)),0.5);
                return 0.0f;
            }
        }
    }

    return 1;
}

