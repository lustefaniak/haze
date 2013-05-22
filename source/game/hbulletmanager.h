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

#ifndef HBULLETMANAGER_H
#define HBULLETMANAGER_H

#define MAX_BULLETS 1024*4

enum BulletType {
    BulletNone=0,
    Bullet9mm,
    BulletSniper,
    BulletLaser
};

typedef struct HBullet_s {
    BulletType type;
    vec3_t pos;
    vec3_t vel;
}
HBullet_t;




/*
 * zajmuje si�obsug latajcych pociskow po planszy
 */
class HBulletManager {
public:
    // class constructor
    HBulletManager(HLevel * level);
    // class destructor
    ~HBulletManager();
    HBullet_s m_Bullets[MAX_BULLETS+1];
    // tworzy pocisk
    void CreateBullet(BulletType type, vec3_t start, vec3_t velocity);
    // robi updejt pociskow
    void Update();
    // renderuje pociski
    void Render();
};

#endif // HBULLETMANAGER_H

