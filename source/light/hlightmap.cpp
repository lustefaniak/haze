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
#include "hlightmap.h" // class's header file

// class constructor
HLightmap::HLightmap() {
    // insert your code here
    m_OpenGLID=0;
}

// class destructor
HLightmap::~HLightmap() {
    // insert your code here
}

#define GL_CLAMP_TO_EDGE                  0x812F

// aduj�tekstur�do opengl'a
void HLightmap::Upload(int textureunit) {
    /* TODO (#1#): Implement HLightmap::Upload() */
    glActiveTextureARB(textureunit);
    if (!m_OpenGLID) {
        glDisable(GL_TEXTURE_2D);
        return;
    }
    glBindTexture(GL_TEXTURE_2D,m_OpenGLID);
    glEnable(GL_TEXTURE_2D);
    
//    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
/*    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);*/
}

// zwalnia zasoby
void HLightmap::Unload() {
    /* TODO (#1#): Implement HLightmap::Unload() */
    if (glIsTexture(m_OpenGLID)) {
        glDeleteTextures(1,&m_OpenGLID);
    }
    m_OpenGLID=0;
}

// wysya dane do gl'a
int HLightmap::Load(unsigned int w, unsigned int h, unsigned char *data) {
    /* TODO (#1#): Implement HLightmap::Load() */
    // Generate a texture with the associative texture ID stored in the array
    Unload();
    glGenTextures(1, &m_OpenGLID);

    // This sets the alignment requirements for the start of each pixel row in memory.
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

    // Bind the texture to the texture arrays index and init the texture
    glBindTexture(GL_TEXTURE_2D, m_OpenGLID);

    // Change the lightmap gamma values by our desired gamma
//  ChangeGamma(pImageBits, width*height*3, g_Gamma);

    // Build Mipmaps (builds different versions of the picture for distances - looks better)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);

    //Assign the mip map levels
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    return m_OpenGLID;
}


int HLightmap::GetOpenGLID() {
    return m_OpenGLID;
}
