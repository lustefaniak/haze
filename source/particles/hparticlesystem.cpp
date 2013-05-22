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

// class constructor
HParticleSystem::HParticleSystem(int numpart) {
    // insert your code here
    assert(numpart>0);
    m_Particles=NULL;
    m_Particles=(HParticle_s*)malloc(numpart*sizeof(HParticle_s));
    assert(m_Particles);
    memset(m_Particles,0,numpart*sizeof(HParticle_s));
    m_numParticles=numpart;
}

// class destructor
HParticleSystem::~HParticleSystem() {
    // insert your code here
    if (m_Particles)    free(m_Particles);
}

