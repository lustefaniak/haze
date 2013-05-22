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
#include "hparticlesystemrain.h" // class's header file

// class constructor
HParticleSystemRain::HParticleSystemRain(int numdrops)
        : HParticleSystem(numdrops) {
    m_fParam1=128;
    m_fParam2=0.01;
    m_fParam3=1024;
    m_fTimeToNextSpawn=m_fParam2;
    m_vParam1.Set(0,-1,0);
    m_vOrigin.Set(0,0,0);
}

// class destructor
HParticleSystemRain::~HParticleSystemRain() {
    if (m_Particles)    free(m_Particles);
    m_Particles=NULL;
}

// robi updejt systemu
void HParticleSystemRain::Update() {
    /* TODO (#1#): Implement HParticleSystemRain::Update() */
    m_BBox.Reset();
    int i;
    float delta=HTimer::GetSingleton().GetDelta()/100;
    for (i=0;i<m_numParticles;i++) {
        if (!m_Particles[i].alive) continue;
        m_Particles[i].life-=delta;
        if (m_Particles[i].life<=0) {
            m_Particles[i].alive=false;
            m_numParticlesAlive--;
            continue;
        }
        m_Particles[i].pos+=m_Particles[i].vel*delta*60*m_Particles[i].size;
        m_BBox.Expand(m_Particles[i].pos);
    }
    m_BBox.max+=vec3_t(2,2,2);
    m_BBox.min-=vec3_t(2,2,2);
    m_fTimeToNextSpawn-=delta;
    if (m_fTimeToNextSpawn<=0/*||m_numParticlesAlive<m_numParticles/4*/) {
        if (m_numParticlesAlive<m_numParticles/4) m_fTimeToNextSpawn=m_fParam2/4;
        else m_fTimeToNextSpawn=m_fParam2;
        SpawnWaterDrop();
    }
}

// tworzy now kropl�
void HParticleSystemRain::SpawnWaterDrop() {
    /* TODO (#1#): Implement HParticleSystemRain::SpawnWaterDrop() */
    if (m_numParticlesAlive==m_numParticles) return;
    HParticle_s particle;
    vec3_t pos;
    pos.Set(HRandom(-m_fParam1,m_fParam1),0,0);
    pos.RotateY(HRandom(-360,360),pos);
    vec3_t vel;
    vel=m_vParam1;
    vel.RotateX(HRandom(-5,5),vel);
    vel.RotateZ(HRandom(-5,5),vel);
    vel.Normalize();
    int i;
    for (i=0;i<m_numParticles;i++) {
        if (m_Particles[i].life<=0) {
            m_Particles[i].pos=m_vOrigin+pos;
            m_Particles[i].vel=vel;
            m_Particles[i].life=m_fParam3;
            m_Particles[i].size=HRandom(0.5,1);
            m_Particles[i].alive=true;
            m_numParticlesAlive++;
            return;
        }
    }
}

