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
#include "hgpoly.h" // class's header file

// class constructor
HGPoly::HGPoly() {
    // insert your code here
    p=NULL;
    BSP_Next=NULL;
    BSP_Prev=NULL;
    Rendering_Next=NULL;
    m_Lightmap=NULL;

}

// class destructor
HGPoly::~HGPoly() {
    // insert your code here
    if (m_Lightmap) {
        delete m_Lightmap;
    }

}

// sortuje wszystkie wierzchoki
void HGPoly::SortVerticesCCW() {
    /* TODO (#1#): Implement HGPoly::SortVerticesCW() */
    // Calculate center of polygon
    //
    /*  p->n[0]=-p->n[0];
    p->n[1]=-p->n[1];
    p->n[2]=-p->n[2];*/
    if (m_Verts.num<3) return;
    if (p==NULL) return;

    int i=0;
    int j=0;
    for ( i = 0; i < m_Verts.num; i++ ) {
        m_vCenter = m_vCenter + m_Verts[ i ].pos;
    }

    m_vCenter = m_vCenter / m_Verts.num;

    //
    // Sort vertices
    //
    for ( i = 0; i < m_Verts.num - 2; i++ ) {
        vec3_t  a;
        HGPlane tp;
        float   SmallestAngle   = -1;
        int     Smallest        = -1;

        a = m_Verts[ i ].pos - m_vCenter;
        a.Normalize ( );

        tp.CalcNormal ( m_Verts[ i ].pos, m_vCenter, m_vCenter + p->n );

        for ( j = i + 1; j < m_Verts.num; j++ ) {
            if ( tp.GetPointDistance( m_Verts[ j ].pos ) > -epsilon ) {
                vec3_t  b;
                float   Angle;

                b = m_Verts[ j ].pos - m_vCenter;
                b.Normalize ( );

                Angle = a.Dot ( b );

                if ( Angle > SmallestAngle ) {
                    SmallestAngle   = Angle;
                    Smallest        = j;
                }
            }
        }

        if ( Smallest == -1 ) {
            hlog("Error: Degenerate polygon!\n");

            abort ( );
        }

        HGVert  t           = m_Verts[ Smallest ];
        m_Verts[ Smallest ] = m_Verts[ i + 1 ];
        m_Verts[ i + 1 ]        = t;
    }

    //
    // Check if vertex order needs to be reversed for back-facing polygon
    //
    /*  p->n[0]=-p->n[0];
        p->n[1]=-p->n[1];
        p->n[2]=-p->n[2];*/
    HGPlane tface;
    tface.CalcNormal(m_Verts[0].pos,m_Verts[1].pos,m_Verts[2].pos);
//  if (tface.n!=m_pFace->n)
    //CalculatePlane ( );
    //debug("normals dot: %f",m_pFace->n.Dot ( tface.n ));
    if ( p->n.Dot ( tface.n ) > -epsilon ) {
        j = m_Verts.num;
        //debug("reversing vertex order\n");

        for ( i = 0; i < j / 2; i++ ) {
            HGVert v            = m_Verts[ i ];
            m_Verts[ i ]            = m_Verts[ j - i - 1 ];
            m_Verts[ j - i - 1 ]    = v;
        }
    }

}

// dodaje wierzchoek do polygonu
void HGPoly::AddVert(HGVert vert) {
    /* TODO (#1#): Implement HGPoly::AddVert() */
    int i=0;
    for (i=0;i<m_Verts.num;i++) {
        if (m_Verts[i].pos==vert.pos) return;
    }
    m_Verts.Add(vert);
}

// oblicza wsp�dne tekstury
void HGPoly::CalculateTextureUV() {
    /* TODO (#1#): Implement HGPoly::CalculateTextureUV() */
    float U, V;
    int i=0;
    int i2=0;
//  for ( i = 0; i < m_iNumPolys; i++ )
//  {
    int w=0;
    int h=0;
//   float d=0;
//   d=p->texplanes[0].d;
    if (HTextureManager::GetSingleton().GetTexture(p->texture)) {
        w=HTextureManager::GetSingleton().GetTexture(p->texture)->GetWidth();// Textures[m_pFace->texid]->width;
        h=HTextureManager::GetSingleton().GetTexture(p->texture)->GetHeight();// Textures[m_pFace->texid]->width;
    } else {
        w=128;
        h=128;
        debug("!!!Can't get texture dimension!!!\n");
    }
//   h=Textures[m_pPolys[i]->m_pFace->texid]->height;
    for ( i2=0;i2<m_Verts.num;i2++) {
        U = p->texplanes[ 0 ].n.Dot ( m_Verts[ i2 ].pos );
        U = U / ( w ) / p->texscale[0];
        U = U +   p->texplanes[0].d/w;
        V = p->texplanes[ 1 ].n.Dot ( m_Verts[ i2 ].pos );
        V = V / ( h ) / p->texscale[1];
        V = V +   p->texplanes[1].d/h;
#ifdef _DEBUG
        hlog("tex coord: %f %f\n",U,V);
#endif
        m_Verts[ i2 ].tex1[0]=U;
        m_Verts[ i2 ].tex1[1]=V;
    }
//  }

    //
    // Check which axis should be normalized
    //
    bool    bDoU = true;
    bool    bDoV = true;
//  for(i=0;i<m_iNumPolys;i++){
    bDoU = true;
    bDoV = true;
    for ( i2 = 0; i2 < m_Verts.num; i2++ ) {
        if ( ( m_Verts[ i2 ].tex1[ 0 ] < 1 ) && ( m_Verts[ i2 ].tex1[ 0 ] > -1 ) ) {
            bDoU = false;
        }

        if ( (m_Verts[ i2 ].tex1[ 1 ] < 1 ) && ( m_Verts[ i2 ].tex1[ 1 ] > -1 ) ) {
            bDoV = false;
        }
    }

    //
    // Calculate coordinate nearest to 0
    //
    if ( bDoU || bDoV ) {
        float   NearestU = 0;
        float   U = m_Verts[ 0 ].tex1[ 0 ];

        float   NearestV = 0;
        float   V = m_Verts[ 0 ].tex1[ 1 ];

        if ( bDoU ) {
            if ( U > 1 ) {
                NearestU = floor ( U );
            } else {
                NearestU = ceil ( U );
            }
        }

        if ( bDoV ) {
            if ( V > 1 ) {
                NearestV = floor ( V );
            } else {
                NearestV = ceil ( V );
            }
        }

        for ( i2 = 0; i2 < m_Verts.num; i2++ ) {
            if ( bDoU ) {
                U = m_Verts[ i2 ].tex1[ 0 ];

                if ( fabs ( U ) < fabs ( NearestU ) ) {
                    if ( U > 1 ) {
                        NearestU = floor ( U );
                    } else {
                        NearestU = ceil ( U );
                    }
                }
            }

            if ( bDoV ) {
                V = m_Verts[ i2 ].tex1[ 1 ];

                if ( fabs ( V ) < fabs ( NearestV ) ) {
                    if ( V > 1 ) {
                        NearestV = floor ( V );
                    } else {
                        NearestV = ceil ( V );
                    }
                }
            }
        }

        //
        // Normalize texture coordinates
        //
        for ( i2 = 0; i2 < m_Verts.num; i2++ ) {
            m_Verts[ i2 ].tex1[ 0 ] = m_Verts[ i2 ].tex1[ 0 ] - NearestU;
            m_Verts[ i2 ].tex1[ 1 ] = m_Verts[ i2 ].tex1[ 1 ] - NearestV;
            //debug("\tnew texcoord: %f %f\n",m_pPolys[i]->m_sVerts[ i2 ].texcoord[ 0 ],m_pPolys[i]->m_sVerts[ i2 ].texcoord[ 1 ]);
        }
    }
    vec3_t point0;
    vec3_t point1;

    stangent=p->texplanes[0].n;
    stangent.Normalize();
    ttangent=p->texplanes[1].n;
    ttangent.Normalize();

}

// sprawdza czy punkt ley na polygonie
bool HGPoly::PointOnPoly(vec3_t point) {
    /* TODO (#1#): Implement HGPoly::PointOnPoly() */
    int i;
    for (i=1;i<m_Verts.num-1;i++) {
        int vert1;
        int vert2;
        int vert3;
        vert1=0;
        vert2=i;
        vert3=i+1;
        if (u3dPointInTriangle(point,p->n,m_Verts[vert1].pos,m_Verts[vert2].pos,m_Verts[vert3].pos)) return true;
    }
    return false;
}

// przecina poly na dwie cz�i
int HGPoly::SplitByPlane(HGPlane* plane, HGPoly * &front, HGPoly * &back) {
    /* TODO (#1#): Implement HGPoly::SplitByPlane() */
    HGPoly * tfront=NULL;
    HGPoly * tback=NULL;
    int fadd=0;
    int badd=0;
    int startvert=0;
    int endvert=0;

    if (plane->n.Dot(p->n)==1) return 0;
    if (plane->n.Dot(p->n)==-1) return 0;

    //debug("HGPoly::SplitByPlane()\n");
    //debug("%d verts count\n",m_Verts.num);
    //fflush(stdout);
    tfront=new HGPoly;
    assert(tfront);
    tfront->p=p;
    tfront->m_BaseID=m_BaseID;
    tback=new HGPoly;
    assert(tback);
    tback->p=p;
    tback->m_BaseID=m_BaseID;
    int vert;
    float dist;
    HGVert newvert;
    for (vert=0;vert<m_Verts.num;vert++) {
        startvert=vert-1;
        endvert=vert;
        if (startvert==-1) startvert=m_Verts.num-1;
        //fflush(stdout);
        if (plane->RayIntersect(m_Verts[startvert].pos,m_Verts[endvert].pos-m_Verts[startvert].pos,newvert.pos)) {
            if (p->GetPointDistance(newvert.pos)==0) {
                debug("real split vert%d on with plane %d\n",vert,plane);
                //fflush(stdout);
                tfront->AddVert(newvert);
                tback->AddVert(newvert);
                fadd++;
                badd++;
            } else {
                debug("fake split vert%d with plane %d\n",vert,plane);
                //fflush(stdout);
            }

        } else if (plane->RayIntersect(m_Verts[endvert].pos,m_Verts[startvert].pos-m_Verts[endvert].pos,newvert.pos)) {
            if (p->GetPointDistance(newvert.pos)==0) {
                debug("real split vert%d with plane %d\n",vert,plane);
                //fflush(stdout);
                tfront->AddVert(newvert);
                tback->AddVert(newvert);
                fadd++;
                badd++;
            } else {
                debug("fake split vert%d with plane %d\n",vert,plane);
                //fflush(stdout);
            }
        }

        dist=plane->GetPointDistance(m_Verts[vert].pos);
        if (dist>0) {
            tfront->AddVert(m_Verts[vert]);
            fadd++;
            debug("vert%d in front\n",vert);
            //fflush(stdout);
        } else if (dist<0) {
            tback->AddVert(m_Verts[vert]);
            debug("vert%d in back\n",vert);
            badd++;
        } else if (dist<epsilon&&dist>-epsilon) {
            tfront->AddVert(newvert);
            tback->AddVert(newvert);
            debug("vert%d on plane\n",vert);
            fadd++;
            badd++;
        }
    }

    if (fadd<3) {
        delete tfront;
        tfront=NULL;
    } else {
        tfront->SortVerticesCCW();
        tfront->CalculateTextureUV();
    }
    if (badd<3) {
        delete tback;
        tback=NULL;
    } else {
        tback->SortVerticesCCW();
        tback->CalculateTextureUV();
    }

    front=tfront;
    back=tback;
    debug("fadd %d badd %d\n",fadd,badd);
    if (fadd>2&&badd>2) return 2;
    if (fadd<3&&badd<3) return 0;
    return 1;


}


int HGPoly::SplitByPoly(HGPoly* poly, HGPoly * &front, HGPoly * &back) {
    /* TODO (#1#): Implement HGPoly::SplitByPlane() */
    assert(poly);
    HGPlane* plane=poly->p;
    assert(plane);
    HGPoly * tfront=NULL;
    HGPoly * tback=NULL;
    int fadd=0;
    int badd=0;
    int startvert=0;
    int endvert=0;

    if (plane->n.Dot(p->n)==1) return 0;
    if (plane->n.Dot(p->n)==-1) return 0;

    debug("HGPoly::SplitByPlane()\n");
    debug("%d verts count\n",m_Verts.num);
    //fflush(stdout);
    tfront=new HGPoly;
    assert(tfront);
    tfront->p=p;
    tfront->m_BaseID=m_BaseID;
    tback=new HGPoly;
    assert(tback);
    tback->p=p;
    tback->m_BaseID=m_BaseID;
    int vert;
    float dist;
    HGVert newvert;
    for (vert=0;vert<m_Verts.num;vert++) {
        startvert=vert-1;
        endvert=vert;
        if (startvert==-1) startvert=m_Verts.num-1;
        //fflush(stdout);
        if (plane->RayIntersect(m_Verts[startvert].pos,m_Verts[endvert].pos-m_Verts[startvert].pos,newvert.pos)) {
            debug("real split vert%d on with plane %d\n",vert,plane);
            //fflush(stdout);
            if (poly->PointOnPoly(newvert.pos)) {
                //fflush(stdout);
                tfront->AddVert(newvert);
                tback->AddVert(newvert);
                fadd++;
                badd++;
            } else {
                debug("Not on testing poly!!!\n");
                //fflush(stdout);
            }

        } else if (plane->RayIntersect(m_Verts[endvert].pos,m_Verts[startvert].pos-m_Verts[endvert].pos,newvert.pos)) {
            debug("real split vert%d with plane %d\n",vert,plane);
            //fflush(stdout);
            if (poly->PointOnPoly(newvert.pos)) {
                tfront->AddVert(newvert);
                tback->AddVert(newvert);
                fadd++;
                badd++;
            } else {
                debug("Not on testing poly!!!\n");
                //fflush(stdout);
            }
        }

        dist=plane->GetPointDistance(m_Verts[vert].pos);
        if (dist>0) {
            tfront->AddVert(m_Verts[vert]);
            fadd++;
            debug("vert%d in front\n",vert);
            //fflush(stdout);
        } else if (dist<0) {
            tback->AddVert(m_Verts[vert]);
            debug("vert%d in back\n",vert);
            badd++;
        } else if (dist<epsilon&&dist>-epsilon) {
            tfront->AddVert(newvert);
            tback->AddVert(newvert);
            debug("vert%d on plane\n",vert);
            fadd++;
            badd++;
        }
    }

    if (fadd<3) {
        delete tfront;
        tfront=NULL;
    } else {
        tfront->SortVerticesCCW();
        tfront->CalculateTextureUV();
    }
    if (badd<3) {
        delete tback;
        tback=NULL;
    } else {
        tback->SortVerticesCCW();
        tback->CalculateTextureUV();
    }

    front=tfront;
    back=tback;
    debug("fadd %d badd %d\n",fadd,badd);
    if (fadd>2&&badd>2) return 2;
    if (fadd<3&&badd<3) return 0;
    return 1;


}

// sprawdza po kt�ej stronie paszczyzny ley poly
int HGPoly::PlaneSide(HGPlane * plane) {
    /* TODO (#1#): Implement HGPoly::PlaneSide() */
    int iNumFront,iNumBack;
    float fDot;

    iNumFront = iNumBack = 0;

    for (int i=0;i<m_Verts.num;i++) {
        fDot = plane->GetPointDistance(m_Verts[i].pos);

        if (fDot > 0.001f) {
            iNumFront++;
            if (iNumBack) return SIDE_SPLIT;
        } else if (fDot < -0.001f) {
            iNumBack++;
            if (iNumFront) return SIDE_SPLIT;
        }
    }

    if (iNumFront) return SIDE_FRONT;
    if (iNumBack) return SIDE_BACK;

    return SIDE_ONPLANE;
}

