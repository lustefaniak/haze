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

#ifndef HGAMEFPP_H
#define HGAMEFPP_H

//#include "hgame.h" // inheriting class's header file

/*
 * manager do gry fpp
 */
class HGameFPP {
public:
    // class constructor
    HGameFPP();
    // class destructor
    ~HGameFPP();
    // inicjuje gr�fpp
    int Init();
    // zwalnia zasoby
    int DeInit();
    // robi updejt caoci
    void Update();
    // renderuje ca gr�
    void Render();
    HWorldFromQMap * m_pWorld;
    HGameHUD * m_pGameHUD;
    HBulletManager * m_pBulletManager;
          HParticleSystemSnow * snowsystem;
            HParticleSystemRain * rainsystem;
            HParticleRendererSnow * snowrenderer;
            HParticleRendererRain * rainrenderer;
    // odbiera wcini�ie klawisza
    void HandleKey(int key);
    int m_CurrentWeapon;
    float m_fNextShot;
    // odbiera wcini�ie klawisza myszy
    void HandleMouse(int mkey);
};

#endif // HGAMEFPP_H

