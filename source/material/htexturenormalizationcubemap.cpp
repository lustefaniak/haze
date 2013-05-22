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
#include "htexturenormalizationcubemap.h" // class's header file

// class constructor
HTextureNormalizationCubeMap::HTextureNormalizationCubeMap(string name):HTexture(name) {
    m_uiID=0;
    m_iManagerID=0;
    this->Load(name);
}

// class destructor
HTextureNormalizationCubeMap::~HTextureNormalizationCubeMap() {
    // insert your code here
}

// wysya siebie do opengl'a
int HTextureNormalizationCubeMap::Bind() {
    /* TODO (#1#): Implement HTextureNormalizationCubeMap::Bind() */
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, m_uiID);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    debug("binding normalization_cube_map(%d)\n",m_uiID);
}

// robi updejt
int HTextureNormalizationCubeMap::Update() {
    /* TODO (#1#): Implement HTextureNormalizationCubeMap::Update() */
}

// generuje si�
int HTextureNormalizationCubeMap::Load(string) {
    /* TODO (#1#): Implement HTextureNormalizationCubeMap::Load() */
    if (glIsTexture(m_uiID)) {
        glDeleteTextures(1,&m_uiID);
    }
    glGenTextures(1,&m_uiID);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB,m_uiID);
    unsigned char * data=new unsigned char[32*32*3];
    assert(data);
    debug("generating normalization_cube_map\n");
    //some useful variables
    int size=32;
    float offset=0.5f;
    float halfSize=16.0f;
    vec3_t tempVector;
    unsigned char * bytePtr;

    //positive x
    bytePtr=data;
    int j;
    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=halfSize;
            tempVector[1]=-(j+offset-halfSize);
            tempVector[2]=-(i+offset-halfSize);

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //negative x
    bytePtr=data;

    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=(-halfSize);
            tempVector[1]=(-(j+offset-halfSize));
            tempVector[2]=((i+offset-halfSize));

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //positive y
    bytePtr=data;

    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=(i+offset-halfSize);
            tempVector[1]=(halfSize);
            tempVector[2]=((j+offset-halfSize));

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //negative y
    bytePtr=data;

    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=(i+offset-halfSize);
            tempVector[1]=(-halfSize);
            tempVector[2]=(-(j+offset-halfSize));

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //positive z
    bytePtr=data;

    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=(i+offset-halfSize);
            tempVector[1]=(-(j+offset-halfSize));
            tempVector[2]=(halfSize);

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //negative z
    bytePtr=data;

    for (j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            tempVector[0]=(-(i+offset-halfSize));
            tempVector[1]=(-(j+offset-halfSize));
            tempVector[2]=(-halfSize);

            tempVector.Normalize();
//          tempVector.PackTo01();

            bytePtr[0]=(unsigned char)(tempVector[0]*255);
            bytePtr[1]=(unsigned char)(tempVector[1]*255);
            bytePtr[2]=(unsigned char)(tempVector[2]*255);

            bytePtr+=3;
        }
    }
    glTexImage2D(   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
                    0, GL_RGBA8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete [] data;
    m_uiWidth=32;
    m_uiHeight=32;
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R_EXT, GL_CLAMP_TO_EDGE_EXT);
    return 1;
}

