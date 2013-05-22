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
#include "hparticlesystemsnow.h" // class's header file

// class constructor
HParticleSystemSnow::HParticleSystemSnow(int numsnowflakes)
        : HParticleSystem(numsnowflakes) {
    // insert your code here
    m_fParam1=128;
    m_fParam2=0.25;
    m_fParam3=512;
    m_fTimeToNextSpawn=m_fParam2;
    m_vParam1.Set(0,-2.0f,0);
    m_vOrigin.Set(0,0,0);
    m_bFirstRun=true;

}

// class destructor
HParticleSystemSnow::~HParticleSystemSnow() {
    // insert your code here
    if (m_Particles)    free(m_Particles);
    m_Particles=NULL;
}

// robi updejt systemu
void HParticleSystemSnow::Update() {
    /* TODO (#1#): Implement HParticleSystemSnow::Update() */
    int i;
    if (m_bFirstRun) {
        float maxdistance=(m_vParam1*m_fParam3).Length();
        vec3_t pos;
        for (i=0;i<m_numParticles;i++) {
            pos.Set(HRandom(MIN(0,m_fParam1),MAX(0,m_fParam1)),0,0);
            pos.RotateY(HRandom(0,360),pos);
            m_Particles[i].pos=m_vOrigin+pos;
            m_Particles[i].pos[1]=HRandom(MIN(0,maxdistance),MAX(0,maxdistance));
            m_Particles[i].life=HRandom(0,m_fParam3);
            m_Particles[i].size=HRandom(0,1);
            m_Particles[i].alive=true;
            m_numParticlesAlive++;
        }
        m_bFirstRun=false;
    }

    float delta=HTimer::GetSingleton().GetDelta()/100;
    for (i=0;i<m_numParticles;i++) {
        if (!m_Particles[i].alive) continue;
        m_Particles[i].life-=delta;
        if (m_Particles[i].life<=0) {
            m_Particles[i].alive=false;
            m_numParticlesAlive--;
            continue;
        }
        m_Particles[i].pos+=m_vParam1*delta*m_Particles[i].size+delta*0.5*vec3_t(HRandom(-1,1),0,HRandom(-1,1));
    }
    m_fTimeToNextSpawn-=delta;
    if (m_fTimeToNextSpawn<=0/*||m_numParticlesAlive<m_numParticles/4*/) {
        if (m_numParticlesAlive<m_numParticles/4) m_fTimeToNextSpawn=m_fParam2/4;
        else m_fTimeToNextSpawn=m_fParam2;
        SpawnSnowFlake();
    }
}

// tworzy nowy snowflake
void HParticleSystemSnow::SpawnSnowFlake() {
    /* TODO (#1#): Implement HParticleSystemSnow::SpawnSnowFlake() */
    if (m_numParticlesAlive==m_numParticles) return;
    vec3_t pos;
    pos.Set(HRandom(0,m_fParam1),0,0);
    pos.RotateY(HRandom(0,360),pos);
    int i;
    for (i=0;i<m_numParticles;i++) {
        if (m_Particles[i].life<=0) {
            m_Particles[i].pos=m_vOrigin+pos;
            m_Particles[i].life=m_fParam3;
            m_Particles[i].size=HRandom(0,1);
            m_Particles[i].alive=true;
            m_numParticlesAlive++;
            return;
        }
    }

}

