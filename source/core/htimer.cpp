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
#include "htimer.h" // class's header file

template<> HTimer* Singleton<HTimer>::ms_Singleton = 0;

// class constructor
HTimer::HTimer() {
    // insert your code here
    //timeBeginPeriod(1);
//  start = previous = ;
//  interval = int(fps_interval * 1000);
//  return true;

    m_fLastFPSUpdateTime=m_uiStartTime=m_uiLastFrameTime=m_uiThisFrameTime=SDL_GetTicks();//timeGetTime();
//  m_uiStartTime=m_uiLastFrameTime=m_uiThisFrameTime=SDL_GetTicks();
}

// class destructor
HTimer::~HTimer() {
    // insert your code here
}

bool needReset=true;
// roni updejt
void HTimer::Update() {
    /* TODO (#1#): Implement HTimer::Update() */

    if(needReset){
        m_fLastFPSUpdateTime=m_uiStartTime=m_uiLastFrameTime=m_uiThisFrameTime=SDL_GetTicks();
        needReset=false;
    }

    m_uiLastFrameTime=m_uiThisFrameTime;
    m_uiThisFrameTime = SDL_GetTicks();//timeGetTime();
//  dt = (current - previous) * 0.001f;

//  count++;
    m_iFramesCount++;
//    m_fFPSUpdateTimer+=m_uiThisFrameTime-m_uiLastFrameTime;
    if (m_uiThisFrameTime-m_fLastFPSUpdateTime>1000) {
        m_fFPS = m_iFramesCount*1000 / (m_uiThisFrameTime-m_fLastFPSUpdateTime);
        m_iFramesCount = 0;
        m_fLastFPSUpdateTime=m_uiThisFrameTime;
//      m_fFPSUpdateTimer=0;

  hlog("FPS:%f",m_fFPS);
    }


    /*  m_uiLastFrameTime=m_uiThisFrameTime;
        m_uiThisFrameTime=SDL_GetTicks();*/
}

// zwraca czas pomi�zy klatkami
float HTimer::GetDelta() {
    /* TODO (#1#): Implement HTimer::GetDelta() */
    return m_uiThisFrameTime-m_uiLastFrameTime;
}

// zwraca aktualny czas
float HTimer::GetCurrentTime() {
    /* TODO (#1#): Implement HTimer::GetCurrentTime() */
    //Update();
    return m_uiThisFrameTime;
}

