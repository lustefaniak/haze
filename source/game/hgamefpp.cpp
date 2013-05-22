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
//#include "hgamefpp.h" // class's header file

HObject * objwater;
HObject * objsnow;

// class constructor
HGameFPP::HGameFPP() {
    // insert your code here
    m_CurrentWeapon=1;
}

// class destructor
HGameFPP::~HGameFPP() {
    // insert your code here
}
extern bool ConfigGenerateLightmaps;
// inicjuje gr�fpp
int HGameFPP::Init() {
    /* TODO (#1#): Implement HGameFPP::Init() */
    m_pGameHUD=new HGameHUD;
    m_pGameHUD->Init();
    snowsystem=new HParticleSystemSnow(1024*4);
    snowsystem->m_fParam2=0.001f;
    snowsystem->m_fParam1=512;
    snowsystem->m_vOrigin.Set(0,220,0);
    rainsystem=new HParticleSystemRain();
    //  rainsystem->m_vOrigin.Set(0,220,0);
    rainsystem->m_fParam1=256;
    snowsystem->m_fParam2=0;
    rainsystem->m_fParam3=20;
    snowrenderer=new HParticleRendererSnow;
    rainrenderer=new HParticleRendererRain;

    m_pBulletManager=new HBulletManager(NULL);
    m_pWorld=new HWorldFromQMap;
    if (ConfigGenerateLightmaps) {
        m_pWorld->Import("maps/newmap.map");
    } else {
        m_pWorld->Import("maps/newmap.map",HMAP_NOLIGHT);
    }
    assert(gHObjectFactory);
    objwater=gHObjectFactory->CreateObject("func_water",NULL);
    assert(objwater);

    HGPoly * poly=new HGPoly;
    HGVert vert;
    vert.pos=vec3_t(64,-64,64);
    vert.tex1[0]=0;
    vert.tex1[1]=0;
    poly->AddVert(vert);
    vert.pos=vec3_t(64,-64,-64);
    vert.tex1[0]=1;
    vert.tex1[1]=0;
    poly->AddVert(vert);
    vert.pos=vec3_t(-64,-64,-64);
    vert.tex1[0]=1;
    vert.tex1[1]=1;
    poly->AddVert(vert);
    vert.pos=vec3_t(-64,-64,64);
    vert.tex1[0]=0;
    vert.tex1[1]=1;
    poly->AddVert(vert);
    objwater->AddGeometry(poly);
    objsnow=gHObjectFactory->CreateObject("particle_snow",NULL);
    objsnow->m_vOrigin.Set(0,220,0);
}

// zwalnia zasoby
int HGameFPP::DeInit() {
    /* TODO (#1#): Implement HGameFPP::DeInit() */
    delete m_pWorld;
    delete snowsystem;
    delete rainsystem;
    delete snowrenderer;
    delete rainrenderer;
    m_pGameHUD->DeInit();
    delete m_pGameHUD;
}

// robi updejt caoci
void HGameFPP::Update() {
    /* TODO (#1#): Implement HGameFPP::Update() */
    m_pWorld->Update();
    vec3_t dir=HEngineCore::GetSingleton().m_pCamera->GetDirection();
    snowsystem->Update();
    rainsystem->m_vOrigin[0]=HEngineCore::GetSingleton().m_pCamera->m_vPosition[0];//+dir[0]*256;
    rainsystem->m_vOrigin[2]=HEngineCore::GetSingleton().m_pCamera->m_vPosition[2];//+dir[2]*256;
    rainsystem->m_vOrigin[1]=HEngineCore::GetSingleton().m_pCamera->m_vPosition[1]+512;
    //  rainsystem->m_vOrigin[1]+=256;
    rainsystem->Update();
    m_pGameHUD->SetCrosshairStyle(m_CurrentWeapon);
    m_pBulletManager->Update();
    m_fNextShot-=HTimer::GetSingleton().GetDelta()/100;
    objwater->Update();
    objsnow->Update();
    if (HInputSystem::GetSingleton().m_bKeys[SDLK_RETURN]&&m_fNextShot<=0) {
        vec3_t dir=HEngineCore::GetSingleton().m_pCamera->GetDirection();
        float rangle=(m_pGameHUD->m_fCrosshairRadius/60)*4;
        dir.RotateX(HRandom(-rangle,rangle),dir);
        dir.RotateY(HRandom(-rangle,rangle),dir);
        dir.RotateZ(HRandom(-rangle,rangle),dir);
        m_pGameHUD->m_fCrosshairRadius+=20;
        m_pBulletManager->CreateBullet(Bullet9mm,HEngineCore::GetSingleton().m_pCamera->m_vPosition+vec3_t(0,-5,0),dir*HM(200));
        m_fNextShot=0.5;
        //HEngineCore::GetSingleton().m_pCamera->m_fRoll=HRandom(-1,1);
    }

}

// renderuje ca gr�
void HGameFPP::Render() {
//    glClearColor(0, 0.0f, 0.0f, 1);
    glClear(GL_DEPTH_BUFFER_BIT);//GL_COLOR_BUFFER_BIT |
    m_pWorld->Render(HEngineCore::GetSingleton().m_pCamera);
    /*    glDisable(GL_BLEND);
        glColor4f(1,1,1,1);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    #include "out.cpp"
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/
    m_pBulletManager->Render();
    objwater->Render();
    objsnow->Render();
    snowrenderer->Render(HEngineCore::GetSingleton().m_pCamera,snowsystem);
    rainrenderer->Render(HEngineCore::GetSingleton().m_pCamera,rainsystem);
    m_pGameHUD->Render();
}

// odbiera wcini�ie klawisza
void HGameFPP::HandleKey(int key) {
    /* TODO (#1#): Implement HGameFPP::HandleKey() */
    if (key>='0'&&key<='9') {
        m_CurrentWeapon=((key-'0'));
    }

    if (key==SDLK_RETURN&&m_fNextShot<=0) {
        vec3_t dir=HEngineCore::GetSingleton().m_pCamera->GetDirection();
        float rangle=(m_pGameHUD->m_fCrosshairRadius/60)*4;
        dir.RotateX(HRandom(-rangle,rangle),dir);
        dir.RotateY(HRandom(-rangle,rangle),dir);
        dir.RotateZ(HRandom(-rangle,rangle),dir);
        m_pGameHUD->m_fCrosshairRadius+=5;
        m_pBulletManager->CreateBullet(Bullet9mm,HEngineCore::GetSingleton().m_pCamera->m_vPosition+vec3_t(0,-5,0),dir*HM(200));
        //HEngineCore::GetSingleton().m_pCamera->m_fRoll=HRandom(-1,1);
        m_fNextShot=0.5;
    }

//    sprintf(HEngineCore::GetSingleton().m_pConsole->m_szBuffer,"received_key=%d",key);
}

// odbiera wcini�ie klawisza myszy
void HGameFPP::HandleMouse(int mkey) {
    /* TODO (#1#): Implement HGameFPP::HandleMouse() */

    if (mkey==SDL_BUTTON_LEFT&&m_fNextShot<=0) {
        vec3_t dir=HEngineCore::GetSingleton().m_pCamera->GetDirection();
        float rangle=(m_pGameHUD->m_fCrosshairRadius/60)*3;
        dir.RotateX(HRandom(-rangle,rangle),dir);
        dir.RotateY(HRandom(-rangle,rangle),dir);
        dir.RotateZ(HRandom(-rangle,rangle),dir);
        m_pGameHUD->m_fCrosshairRadius+=5;
        m_pBulletManager->CreateBullet(Bullet9mm,HEngineCore::GetSingleton().m_pCamera->m_vPosition+vec3_t(0,-5,0),dir*HM(200));
        //HEngineCore::GetSingleton().m_pCamera->m_fRoll=HRandom(-1,1);
        m_fNextShot=0.5;
    }
}

