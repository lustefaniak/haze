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
#include "hgbrush.h" // class's header file

// class constructor
HGBrush::HGBrush() {
    // insert your code here
    m_bSolid=true;
    m_bCastShadows=true;
    m_bVisible=true;
}

// class destructor
HGBrush::~HGBrush() {
    // insert your code here
    int i;
    for (i=0;i<m_BasePolys.num;i++) {
        delete m_BasePolys[i];
    }
    for (i=0;i<m_Planes.num;i++) {
        delete m_Planes[i];
    }
    for (i=0;i<m_Polys.num;i++) {
        delete m_Polys[i];
    }

}

// dodaje plane do listy
int HGBrush::AddPlane(HGBrushPlane plane) {
    /* TODO (#1#): Implement HGBrush::AddPlane() */
    HGBrushPlane * p=NULL;
    p=new HGBrushPlane;
    assert(p);
    *p=plane;
    m_Planes.Add(p);
//  debug("added plane... %d count...\n",m_Planes.num);
    return 1;
}

static int PolyCounter=0;

// zamienia plane'y na polygony
int HGBrush::Compile() {
    /* TODO (#1#): Implement HGBrush::Compile() */
    if (m_Planes.num<4) {
        debug("\tnumplanes<4!!!\n");
        return 0;
    }
    int i;
    int j;
    int k;
    int m;
    bool illegal;
    HGPoly * poly=NULL;
    HGVert vert;
    vec3_t point;
    for (i=0;i<m_Planes.num;i++) {
        poly=new HGPoly;
        assert(poly);
        poly->m_BaseID=PolyCounter;
        PolyCounter++;
        poly->p=m_Planes[i];
        for (j=0;j<m_Planes.num;j++) {
            for (k=0;k<m_Planes.num;k++) {
                illegal=false;
                if (!(i!=j!=k)) continue;
                if (!m_Planes[i]->GetIntersection(m_Planes[j],m_Planes[k],point)) continue;
                vert.pos=point;
                for (m=0;m<m_Planes.num;m++) {
                    if (m_Planes[m]->GetPointDistance(point)>epsilon) {
                        illegal=true;
                        break;
                    }
                }
                if (!illegal) {
                    poly->AddVert(vert);
                    m_BBox.Expand(point);
                }

            }
        }
        if (poly->m_Verts.num>2) {
//  debug("\tsorting vertices...\n");
            poly->SortVerticesCCW();
//  debug("\tcalculating texture coordinates...\n");
            poly->CalculateTextureUV();
        } else {
            debug("\tBad poly!!!");
            delete poly;
            continue;
        }
        m_BasePolys.Add(poly);
    }
//  int numverts=0;
//  debug("\tnum polys: %d\n",m_BasePolys.num);
    for (i=0;i<m_BasePolys.num;i++) {
//  debug("\t\tpoly%d\n",i);
//  debug("\t\t%d verts\n",m_BasePolys[i]->m_Verts.num);
        poly=new HGPoly;
        assert(poly);
        m_BasePolys[i]->p->CalcNormal(m_BasePolys[i]->m_Verts[2].pos,m_BasePolys[i]->m_Verts[1].pos,m_BasePolys[i]->m_Verts[0].pos);
        *poly=*m_BasePolys[i];
        m_Polys.Add(poly);
//  numverts+=m_BasePolys[i]->m_Verts.num;
    }

//    debug("\ttotally %d verts...\n",numverts);
//    debug("\tbbox min:[%f %f %f] max:[%f %f %f] diagonal: %f\n",m_BBox.min[0],m_BBox.min[1],m_BBox.min[2]
//    ,m_BBox.max[0],m_BBox.max[1],m_BBox.max[2],(m_BBox.max-m_BBox.min).Length());

    return 1;
}

// sprawdza czy poly jest wewntrz brusha
bool HGBrush::PolyInside(HGPoly * poly) {
    /* TODO (#1#): Implement HGBrush::PolyInside() */
    int i=0;
    int j=0;
    for (i=0;i<m_Planes.num;i++) {
        for (j=0;j<poly->m_Verts.num;j++) {
            if (m_Planes[i]->GetPointDistance(poly->m_Verts[j].pos)>epsilon) return false;

        }
    }

    return true;
}

// wykonuje operacj�csg union
int HGBrush::CSGUnion(HGBrush * brush) {
    /* TODO (#1#): Implement HGBrush::CSGUnion() */
    /*  assert(brush);
        if(brush==this) return 0;
        if(!m_BBox.Intersect(&brush->m_BBox)) return 0;
        int poly=0;
        int plane=0;
        HGPoly *front=NULL;
        HGPoly *back=NULL;
        int numsplits;
        for(poly=0;poly<m_BasePolys.num;poly++){
        for(plane=0;plane<brush->m_Planes.num;plane++){
        numsplits=m_BasePolys[poly]->SplitByPlane(brush->m_Planes[plane],front,back);
        if(numsplits!=2) {
        if(front) {
        delete front; front=NULL;
        }
        if(back){
        delete back; back=NULL;
        }
        continue;
        }
        if(numsplits==2){
    //  HGPoly * spoly=m_BasePolys[poly];
    //  delete spoly;
    //  m_Polys[poly]=front;
    if(!PolyInside(front)&&!brush->PolyInside(front)){
    m_Polys.Add(front);
    }
    if(!PolyInside(back)&&!brush->PolyInside(back)){
    m_Polys.Add(back);
    }
    //  m_Polys.Add(back);
    //  poly--;
        break;
        }


        }
        }

    //  brush->CSGUnion(this);
        return 1;*/
    /*  assert(brush);
        int poly=0;
        int plane=0;
        int vert=0;
        HGPoly *front;
        HGPoly *back;
        HGVert newvert;

        int fadd=0;
        int badd=0;
        int startvert;
        int endvert;
        for(poly=0;poly<m_Polys.num;poly++){
        front=new HGPoly;
        back=new HGPoly;
        assert(front);
        assert(back);
        front->p=m_Polys[poly]->p;
        front->m_BaseID=m_Polys[poly]->m_BaseID;
        back->p=m_Polys[poly]->p;
            back->m_BaseID=m_Polys[poly]->m_BaseID;
        for(plane=0;plane<brush->m_Planes.num;plane++){
        for(vert=0;vert<m_Polys[poly]->m_Verts.num;vert++){
        startvert=vert-1;
        endvert=vert;
        if(startvert==-1) startvert=m_Polys[poly]->m_Verts.num-1;
    //    debug("test vert%d on poly %d with plane %d\n",vert,poly,plane);
    //    fflush(stdout);
        if(brush->m_Planes[plane]->RayIntersect(m_Polys[poly]->m_Verts[startvert].pos,m_Polys[poly]->m_Verts[endvert].pos-m_Polys[poly]->m_Verts[startvert].pos,newvert.pos)){
        debug("real split vert%d on poly %d with plane %d\n",vert,poly,plane);
        fflush(stdout);
        front->AddVert(newvert);
        back->AddVert(newvert);
        fadd++;
        badd++;
    //    continue;


        }

        if(vert==-1) continue;
        if(brush->m_Planes[plane]->GetPointDistance(m_Polys[poly]->m_Verts[vert].pos)>0){
    //    debug("checking vert%d on poly %d with plane %d\n",vert,poly,plane);
    //    fflush(stdout);
        front->AddVert(m_Polys[poly]->m_Verts[vert]);
        fadd++;
    //    debug("front: vert%d on poly %d with plane %d\n",vert,poly,plane);
    //    fflush(stdout);
        } else {
        back->AddVert(m_Polys[poly]->m_Verts[vert]);
    //    debug("back: vert%d on poly %d with plane %d\n",vert,poly,plane);
    //    fflush(stdout);
        badd++;
        }


        }
        }
        if(fadd>0&&badd>0) {
        debug("poly split\n");
        fflush(stdout);
        delete m_Polys[poly];
        front->SortVerticesCCW();
        front->CalculateTextureUV();
        back->SortVerticesCCW();
        back->CalculateTextureUV();
        m_Polys[poly]=front;
        m_Polys.Add(back);
        poly--;
        break;

        } else {
        delete front;
        delete back;
        }
        fadd=0;
        badd=0;
        }
        int i;
        for(i=0;i<m_Polys.num;){
        if(brush->PolyInside(m_Polys[i])){
        m_Polys.Remove(m_Polys[i]);
        } else {
        i++;
        }

        }
    */





}

