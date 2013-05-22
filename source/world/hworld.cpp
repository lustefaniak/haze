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
#include "hworld.h" // class's header file

bool drawBumps=false;
bool drawColor=false;

// class constructor
HWorld::HWorld() {
    // insert your code here
//  GenerateNormalizationCubeMap();
}

// class destructor
HWorld::~HWorld() {
    // insert your code here
    int i;
    for (i=0;i<m_Brushes.num;i++) {
        delete m_Brushes[i];
    }
}

// wczytuje stan wiata i takie tam
int HWorld::Load(string geometry, string savegame) {
    /* TODO (#1#): Implement HWorld::Load() */





    return 1;
    if (savegame=="") return 1;


}

// tworzy nowy brush w wiecie
HGBrush * HWorld::CreateBrush() {
    /* TODO (#1#): Implement HWorld::CreateBrush() */
    HGBrush * brush=NULL;
    brush=new HGBrush;
    assert(brush);
    m_Brushes.Add(brush);
    return brush;
}

// wykonuje update swiata
void HWorld::Update() {
    /* TODO (#1#): Implement HWorld::Update() */
}

// renderuje z widoku tej kamery
void HWorld::Render(HCamera * cam) {
    glLoadIdentity();

    cam->Upload();
    int i;
    int j;
    int k;

    //Get the inverse model matrix
    matrix_t inverseModelMatrix;
    HLight * nearestlight=NULL;
    float nearestdistance=1000000000;
    for (i=0;i<m_LightSystem.m_Lights.num;i++) {
        float dist=m_LightSystem.m_Lights[i].m_Position.GetDistance(cam->m_vPosition);
        if (dist<nearestdistance) {
            nearestlight=&m_LightSystem.m_Lights[i];
            nearestdistance=dist;
        }
        /*  nearestlight=&m_LightSystem.m_Lights[i];
            break;*/
    }
    map<int,HGPoly*> renderingmap;

    for (i=0;i<m_WorldBrushes.num;i++) {
        if (!m_WorldBrushes[i]->m_bVisible)continue;
        for (j=0;j<m_WorldBrushes[i]->m_Polys.num;j++) {
            if (renderingmap.count(m_WorldBrushes[i]->m_Polys[j]->p->material)==0) {
                m_WorldBrushes[i]->m_Polys[j]->Rendering_Next=NULL;
                renderingmap[m_WorldBrushes[i]->m_Polys[j]->p->material]=m_WorldBrushes[i]->m_Polys[j];

            } else {
                m_WorldBrushes[i]->m_Polys[j]->Rendering_Next=renderingmap[m_WorldBrushes[i]->m_Polys[j]->p->material];
                renderingmap[m_WorldBrushes[i]->m_Polys[j]->p->material]=m_WorldBrushes[i]->m_Polys[j];
            }
        }
    }
    map<int,HGPoly*>::iterator iter;
    pair<int,HGPoly*> p;
    for (iter=renderingmap.begin();iter!=renderingmap.end();++iter) {
        p=*iter;
        HRenderer::GetSingleton().Render(p.second,nearestlight);
    }

    renderingmap.clear();
    for (i=m_WorldBrushes.num;i<m_Brushes.num;i++) {
        if (!m_Brushes[i]->m_bVisible)continue;
        for (j=0;j<m_Brushes[i]->m_Polys.num;j++) {
            if (renderingmap.count(m_Brushes[i]->m_Polys[j]->p->material)==0) {
                m_Brushes[i]->m_Polys[j]->Rendering_Next=NULL;
                renderingmap[m_Brushes[i]->m_Polys[j]->p->material]=m_Brushes[i]->m_Polys[j];

            } else {
                m_Brushes[i]->m_Polys[j]->Rendering_Next=renderingmap[m_Brushes[i]->m_Polys[j]->p->material];
                renderingmap[m_Brushes[i]->m_Polys[j]->p->material]=m_Brushes[i]->m_Polys[j];
            }
        }
    }
    for (iter=renderingmap.begin();iter!=renderingmap.end();++iter) {
        p=*iter;
        HRenderer::GetSingleton().Render(p.second,nearestlight);
    }


    /*    glBegin(GL_POINTS);
        glColor4f(1,1,1,1);
        for(i=0;i<m_LightPoints.num;i++){
        glVertex3fv(m_LightPoints[i]);
        }
        glEnd();*/
    return;
    /*    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(i=0;i<m_WorldBrushes.num;i++){
        if(!m_WorldBrushes[i]->m_bVisible)continue;
        for(j=0;j<m_WorldBrushes[i]->m_Polys.num;j++){
        if(m_WorldBrushes[i]->m_Polys[j]->m_Verts.num==3) glBegin(GL_TRIANGLES);
        if(m_WorldBrushes[i]->m_Polys[j]->m_Verts.num==4) glBegin(GL_QUADS);
        if(m_WorldBrushes[i]->m_Polys[j]->m_Verts.num>4) glBegin(GL_POLYGON);
        glNormal3f(m_WorldBrushes[i]->m_Polys[j]->p->n[0],m_Brushes[i]->m_Polys[j]->p->n[1],m_Brushes[i]->m_Polys[j]->p->n[2]);
        for(k=0;k<m_WorldBrushes[i]->m_Polys[j]->m_Verts.num;k++){
        glVertex3f(m_WorldBrushes[i]->m_Polys[j]->m_Verts[k].pos[0],m_WorldBrushes[i]->m_Polys[j]->m_Verts[k].pos[1],m_WorldBrushes[i]->m_Polys[j]->m_Verts[k].pos[2]);
        }
        glEnd();
        }
        }
*/
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor4f(1,1,1,1);
        for(i=0;i<m_WorldBrushes.num;i++){
        if(!m_WorldBrushes[i]->m_bVisible)continue;
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.min[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.min[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.min[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.min[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.min[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.min[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.min[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.max[2]);
        glVertex3f(m_WorldBrushes[i]->m_BBox.max[0],m_WorldBrushes[i]->m_BBox.max[1],m_WorldBrushes[i]->m_BBox.min[2]);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    

}



