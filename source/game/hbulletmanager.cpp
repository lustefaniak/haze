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
HBulletManager::HBulletManager(HLevel * level) {
    // insert your code here
    memset(m_Bullets,0,sizeof(HBullet_s)*(MAX_BULLETS+1));
}

// class destructor
HBulletManager::~HBulletManager() {
    // insert your code here
}

// tworzy pocisk
void HBulletManager::CreateBullet(BulletType type, vec3_t start, vec3_t velocity) {
    /* TODO (#1#): Implement HBulletManager::CreateBullet() */
    int i;
    for (i=0;i<MAX_BULLETS;i++) {
        if (m_Bullets[i].type==0) {
            m_Bullets[i].pos=start;
            m_Bullets[i].type=type;
            m_Bullets[i].vel=velocity;
            return;
        }
    }

}

// robi updejt pociskow
void HBulletManager::Update() {
    /* TODO (#1#): Implement HBulletManager::Update() */
    float delta=HTimer::GetSingleton().GetDelta()/100;
    for (int i=0;i<MAX_BULLETS;i++) {
        if (m_Bullets[i].type==BulletNone) continue;
        m_Bullets[i].pos+=m_Bullets[i].vel*delta;
        if (m_Bullets[i].pos.GetDistance(vec3_t(0,0,0))>10000) m_Bullets[i].type=BulletNone;
    }
}

// renderuje pociski
void HBulletManager::Render() {
    /* TODO (#1#): Implement HBulletManager::Render() */
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(3);
    glDepthMask(0);
    glBegin(GL_LINES);
    for (int i=0;i<MAX_BULLETS;i++) {
        if (m_Bullets[i].type==BulletNone) continue;
        glColor4f(0.75,0.75,0,1);
        glVertex3fv(m_Bullets[i].pos);
        glColor4f(0.75,0.75,0,0);
        glVertex3fv(m_Bullets[i].pos-m_Bullets[i].vel/100);
    }
    glEnd();
    glLineWidth(1);
    glDepthMask(1);
}

