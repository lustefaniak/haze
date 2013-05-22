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
#include "hobjectsnow.h" // class's header file

// class constructor
HObjectSnow::HObjectSnow(HLevel * level)
        : HObject(level) {
    // insert your code here
    m_system=new HParticleSystemSnow();
    /*  m_system->m_fParam2=0.5f;
        m_system->m_fParam1=512;
        */
    m_system->m_fParam2=0.001f;
    m_system->m_fParam1=256;
//  m_system->m_vOrigin.Set(0,220,0);


    m_renderer=new HParticleRendererSnow;
}

// class destructor
HObjectSnow::~HObjectSnow() {
    // insert your code here
    delete m_system;
    delete m_renderer;
}

RegisterObject(object_snow,HObjectSnow);
RegisterObject(particle_snow,HObjectSnow);
RegisterObject(snow_source,HObjectSnow);
RegisterObject(snow,HObjectSnow);

// renderuje nieg
void HObjectSnow::Render() {
    /* TODO (#1#): Implement HObjectSnow::Render() */
//  if(!HEngineCore::GetSingleton().m_pCamera->m_pFrustum->PointInFrustum(m_system->m_BBox.min[0],m_system->m_BBox.min[1],m_system->m_BBox.min[2])&&!HEngineCore::GetSingleton().m_pCamera->m_pFrustum->PointInFrustum(m_system->m_BBox.max[0],m_system->m_BBox.max[1],m_system->m_BBox.max[2])) return;
    m_renderer->Render(HEngineCore::GetSingleton().m_pCamera,m_system);
}

// przeprowadza updejt
void HObjectSnow::Update() {
    /* TODO (#1#): Implement HObjectSnow::Update() */
    m_system->m_vOrigin=m_vOrigin;
    m_system->Update();
}

