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
#include "htexture.h" // class's header file

// class constructor
HTexture::HTexture(string name) {
    m_uiID=0;
    m_sName=name;
    m_uiHeight=0;
    m_uiWidth=0;
    m_iManagerID=0;
    m_iReferences=0;
// insert your code here
}

// class destructor
HTexture::~HTexture() {
    // insert your code here
    if (glIsTexture(m_uiID)) {
        glDeleteTextures(1,&m_uiID);
    }
}


// returns the value of m_uiID
GLuint HTexture::GetOpenGLID() {
    return m_uiID;
}


// returns the value of m_sName
string HTexture::GetName() {
    return m_sName;
}


// returns the value of m_uiWidth
unsigned int HTexture::GetWidth() {
    return m_uiWidth;
}


// returns the value of m_uiHeight
unsigned int HTexture::GetHeight() {
    return m_uiHeight;
}


