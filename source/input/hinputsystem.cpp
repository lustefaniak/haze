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
#include "hinputsystem.h" // class's header file

template<> HInputSystem* Singleton<HInputSystem>::ms_Singleton = 0;

HInputSystem * gHInputSystem=NULL;

// class constructor
HInputSystem::HInputSystem() {
    guard(HInputSystem::HInputSystem());
    m_bKeys = SDL_GetKeyState(NULL);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    m_fMouseSens=0.2f;
    if (gHInputSystem==NULL) {
        gHInputSystem=this;
    }
    unguard;
}

// class destructor
HInputSystem::~HInputSystem() {
    guard(HInputSystem::~HInputSystem());
    if (gHInputSystem==this) {
        gHInputSystem==NULL;
    }
    unguard;
}

// robi updejt
int HInputSystem::Update() {
    /* DONE (#1#): Implement HInputSystem::Update() */
    vec3_t finaldir;
    m_bKeys = SDL_GetKeyState(NULL);

    if (m_bKeys[SDLK_ESCAPE]) {
        HEngineCore::GetSingleton().Exit(); /*delete &HEngineCore::getSingleton(); SDL_Quit();exit(0);*/
    };

    if (    !HGUI::GetSingleton().m_bActive&&!HConsole::GetSingleton().m_bOpen) {
        vec3_t dir=HEngineCore::GetSingleton().m_pCamera->GetDirection();

        if (m_bKeys[SDLK_w]) {
            finaldir+=dir;
        }
        if (m_bKeys[SDLK_s]) {
            finaldir+=-dir;
        }

        vec3_t dir2;
        vec3_t tmp(0,1,0);
        if (m_bKeys[SDLK_a]) {
            dir2=dir.Cross(tmp);
            dir2.Normalize();
            finaldir+=dir2*0.8;
        }
        if (m_bKeys[SDLK_d]) {
            dir2=dir.Cross(-tmp);
            dir2.Normalize();
            finaldir+=dir2*0.8;
        }

        finaldir.Normalize();
        HEngineCore::GetSingleton().m_pCamera->m_vPosition+=finaldir*HTimer::GetSingleton().GetDelta()/2;
    }

    return 1;
}

// odbiera zdarzenia
int HInputSystem::HandleSDLEvent(SDL_Event event) {
    /* TODO (#1#): Implement HInputSystem::HandleSDLEvent() */

    if (event.type==SDL_KEYDOWN) {
        if (HConsole::GetSingleton().m_bOpen||event.key.keysym.sym=='`'||event.key.keysym.sym=='~') {
            HConsole::GetSingleton().HandleKey(event.key.keysym.sym);
            return 1;
        }

        if (HGUI::GetSingleton().m_bActive) {
            HGUI::GetSingleton().HandleKey(event.key.keysym.sym);
        }
        HEngineCore::GetSingleton().m_pGameFPP->HandleKey(event.key.keysym.sym);
    }
    if (event.type==SDL_MOUSEBUTTONDOWN&&!HGUI::GetSingleton().m_bActive) {
        HEngineCore::GetSingleton().m_pGameFPP->HandleMouse(event.button.button);
    }

    if (event.type==SDL_KEYDOWN)
        if (event.key.keysym.sym==SDLK_SPACE) {
            HGUI::GetSingleton().m_bActive=!HGUI::GetSingleton().m_bActive;
        };

    if (event.type==SDL_MOUSEBUTTONDOWN&&event.button.button==1) {
//    debug("click");
        HGUI::GetSingleton().MouseState(true);
    }
    if (event.type==SDL_MOUSEBUTTONUP&&event.button.button==1) {
//    debug("unclick");
        HGUI::GetSingleton().MouseState(false);
    }

    /*if (event.type==SDL_MOUSEBUTTONDOWN||event.type==SDL_MOUSEBUTTONUP) {
        if (event.button.button == 4) HEngineCore::GetSingleton().m_pCamera->SetFOV(HEngineCore::GetSingleton().m_pCamera->GetFOV()+3);
        if (event.button.button == 5) HEngineCore::GetSingleton().m_pCamera->SetFOV(HEngineCore::GetSingleton().m_pCamera->GetFOV()-3);
    }*/
}

// odbiera sygna o poruszeniu mysz
void HInputSystem::MouseMove(int deltax, int deltay) {
    /* TODO (#1#): Implement HInputSystem::MouseMove() */
    if (    !HGUI::GetSingleton().m_bActive) {
        HEngineCore::GetSingleton().m_pCamera->m_fYaw+=deltax*m_fMouseSens;
        HEngineCore::GetSingleton().m_pCamera->m_fPitch+=deltay*m_fMouseSens;
    } else {
        HGUI::GetSingleton().MouseMove(-deltax, -deltay);
    };
}


// sets the value of m_fMouseSens
void HInputSystem::SetMouseSens(float x) {
    m_fMouseSens = x;
}

