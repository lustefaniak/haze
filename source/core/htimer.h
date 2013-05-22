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

#ifndef HTIMER_H
#define HTIMER_H

/*
 * licznik czasu
 */
class HTimer : public Singleton<HTimer> {
public:
    // class constructor
    HTimer();
    // class destructor
    ~HTimer();
    // robi updejt
    void Update();
    // zwraca czas pomi�zy klatkami
    float GetDelta();
    // zwraca aktualny czas
    float GetCurrentTime();
//  protected:
    float m_uiStartTime;
    float m_uiLastFrameTime;
    float m_uiThisFrameTime;
    float m_fFPS;
    float m_fLastFPSUpdateTime;
    float m_fFPSUpdateTimer;
    int m_iFramesCount;

};

#endif // HTIMER_H

