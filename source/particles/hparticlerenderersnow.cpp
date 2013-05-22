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
const int buffsize=1024;
// class constructor
HParticleRendererSnow::HParticleRendererSnow() {
    // insert your code here
    m_tSnow=HTextureManager::GetSingleton().Load("particles/snow");
    m_coordBuffer=(int*)malloc(sizeof(int)*buffsize*8+1);
    assert(m_coordBuffer);
    memset(m_coordBuffer,0,sizeof(int)*buffsize*8+1);
    m_posBuffer=(vec3_t*)malloc(sizeof(vec3_t)*buffsize*4+1);
    assert(m_posBuffer);
    memset(m_posBuffer,0,sizeof(vec3_t)*buffsize*4+1);
    int i;
    for (i=0;i<buffsize*8;i+=8) {
        m_coordBuffer[i]=0;
        m_coordBuffer[i+1]=0;
        m_coordBuffer[i+2]=0;
        m_coordBuffer[i+3]=1;
        m_coordBuffer[i+4]=1;
        m_coordBuffer[i+5]=1;
        m_coordBuffer[i+6]=1;
        m_coordBuffer[i+7]=0;

        /*  m_Buffer[i].coord[0]=0;
            m_Buffer[i].coord[1]=0;
            m_Buffer[i].coord[0]=1;
            m_Buffer[i].coord[1]=0;
            m_Buffer[i].coord[0]=1;
            m_Buffer[i].coord[1]=1;
            m_Buffer[i].coord[0]=1;
            m_Buffer[i].coord[1]=0;*/
    }
}

// class destructor
HParticleRendererSnow::~HParticleRendererSnow() {
    // insert your code here
    HTextureManager::GetSingleton().UnLoad(m_tSnow);
    free(m_coordBuffer);
    free(m_posBuffer);
}

// renderuje nieg
void HParticleRendererSnow::Render(HCamera * cam, HParticleSystem * system) {
    /* TODO (#1#): Implement HParticleRendererSnow::Render() */
    int i,gi;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    HTextureManager::GetSingleton().Bind(m_tSnow);// HTextureManager::GetSingleton().Load("loading_slider"));
    //glDisable(GL_TEXTURE_2D);
    //glPointSize(20);


    matrix_t mat, tmat; // static?
    vec3_t x, y;

    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    mat.Transpose(tmat);

    x.Set(tmat[0], tmat[1], tmat[2]);
    y.Set(tmat[4], tmat[5], tmat[6]);
#define sfsize 2
    vec3_t pts[4];
    vec3_t mx = -x;
    vec3_t my = -y;

    int buffcount=0;

    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_posBuffer);

    glClientActiveTextureARB(GL_TEXTURE0_ARB);
    glTexCoordPointer(2, GL_INT, 0, m_coordBuffer);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDepthMask(0);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6);

    for (gi=0;gi<=system->m_numParticlesAlive/buffsize;gi++) {
        buffcount=0;
        for (i=gi*buffsize;i<system->m_numParticles;i++) {
            if (!system->m_Particles[i].alive) continue;
            m_posBuffer[buffcount*4]= system->m_Particles[i].pos + ((mx + my) * system->m_Particles[i].size);
            m_posBuffer[buffcount*4+1]= system->m_Particles[i].pos + ((x + my) * system->m_Particles[i].size);
            m_posBuffer[buffcount*4+2]= system->m_Particles[i].pos + ((x + y) * system->m_Particles[i].size);
            m_posBuffer[buffcount*4+3]= system->m_Particles[i].pos + ((mx + y) * system->m_Particles[i].size);
            buffcount++;
            if (buffcount>=buffsize) break;
        }

        glDrawArrays(GL_QUADS, 0, buffcount);
        /*      glBegin(GL_QUADS);
            for(i=0;i<system->m_numParticles;i++){
            if(!system->m_Particles[i].alive) continue;

              pts[0] = system->m_Particles[i].pos + ((mx + my) * system->m_Particles[i].size);
              pts[1] = system->m_Particles[i].pos + ((x + my) * system->m_Particles[i].size);
              pts[2] = system->m_Particles[i].pos + ((x + y) * system->m_Particles[i].size);
              pts[3] = system->m_Particles[i].pos + ((mx + y) * system->m_Particles[i].size);
              glTexCoord2f(0.0f, 0.0f);
              glVertex3fv(pts[0]);
                 glTexCoord2f(1.0f, 0.0f);
                 glVertex3fv(pts[1]);
                 glTexCoord2f(1.0f, 1.0f);
                 glVertex3fv(pts[2]);
                 glTexCoord2f(0.0f, 1.0f);
                 glVertex3fv(pts[3]);
            }
            glEnd();*/


    }
    glDepthMask(1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

