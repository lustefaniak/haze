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
#include "hguimouse.h" // class's header file

// class constructor
HGUIMouse::HGUIMouse() {
    // insert your code here
}

// class destructor
HGUIMouse::~HGUIMouse() {
    // insert your code here
}

// renderuje kursor
void HGUIMouse::Render() {
    /* TODO (#1#): Implement HGUIMouse::Render() */
    glBegin(GL_QUADS);
    glTexCoord2f(40.0f/128, 64.0f/128);
    glVertex2f(CursorPos[0], CursorPos[1]);
    glTexCoord2f(56.0f/128, 64.0f/128);
    glVertex2f(CursorPos[0]+16, CursorPos[1]);
    glTexCoord2f(56.0f/128, 48.0f/128);
    glVertex2f(CursorPos[0]+16, CursorPos[1]+16);
    glTexCoord2f(40.0f/128, 48.0f/128);
    glVertex2f(CursorPos[0], CursorPos[1]+16);
    glEnd();
}

// robi updejt
void HGUIMouse::Update() {
    /* TODO (#1#): Implement HGUIMouse::Update() */
    if (CursorPos[0]<0)CursorPos[0]=0;
    if (CursorPos[1]<0)CursorPos[1]=0;
    if (CursorPos[0]>HRendererWindow::GetSingleton().GetWidth())CursorPos[0]=HRendererWindow::GetSingleton().GetWidth();
    if (CursorPos[1]>HRendererWindow::GetSingleton().GetHeight())CursorPos[1]=HRendererWindow::GetSingleton().GetHeight();
}

