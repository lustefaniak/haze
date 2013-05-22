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

#ifndef HPARTICLESYSTEM_H
#define HPARTICLESYSTEM_H

typedef struct HParticle_s {
    vec3_t pos;
    vec3_t vel;
//vec3_t color;
    float size;
    float life;
    bool alive;
//unsigned char flags;
}
HParticle_t;

/*
 * taka sobie klasa zajmujca si�particlami
 */
class HParticleSystem {
public:
    // class constructor
    HParticleSystem(int num=1000);
    // class destructor
    virtual ~HParticleSystem();
    HParticle_s * m_Particles;
    int m_numParticles;
    int m_numParticlesAlive;
    // robi updejt wszystkich particl�
    virtual void Update() = 0L;
    HGBBox m_BBox;
    float m_fParam1;
    float m_fParam2;
    float m_fParam3;
    float m_fParam4;
    vec3_t m_vOrigin;
    vec3_t m_vParam1;
    vec3_t m_vParam2;
};

#endif // HPARTICLESYSTEM_H

