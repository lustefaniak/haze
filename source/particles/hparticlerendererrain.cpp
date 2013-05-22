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

#include "../Haze.h" // class's header file

// class constructor
HParticleRendererRain::HParticleRendererRain() {
    // insert your code here
}

// class destructor
HParticleRendererRain::~HParticleRendererRain() {
    // insert your code here
}

// renderuje deszcz
void HParticleRendererRain::Render(HCamera * cam, HParticleSystem * system) {
    /* TODO (#1#): Implement HParticleRendererRain::Render() */
    int i;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glDisable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glDisable(GL_TEXTURE_2D);
    //glPointSize(20);


    glDepthMask(0);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    for (i=0;i<system->m_numParticles;i++) {
        if (!system->m_Particles[i].alive) continue;
        glColor4f(0.6,0.8,1,0.6);
        glVertex3fv(system->m_Particles[i].pos);
        glColor4f(0.6,0.8,1,0.0);
        glVertex3fv(system->m_Particles[i].pos-system->m_Particles[i].vel*20*system->m_Particles[i].size);
    }
    glEnd();
    glLineWidth(1);
    glDepthMask(1);

}

