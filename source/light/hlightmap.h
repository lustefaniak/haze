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

#ifndef HLIGHTMAP_H
#define HLIGHTMAP_H

#define HLIGHTMAP_SIZE 64

/*
 * przechowuje lightmap�
 */
class HLightmap {
public:
    // class constructor
    HLightmap();
    // class destructor
    ~HLightmap();
    // aduj�tekstur�do opengl'a
    void Upload(int textureunit=GL_TEXTURE1_ARB);
    // zwalnia zasoby
    void Unload();
    // wysya dane do gl'a
    int Load(unsigned int w, unsigned int h, unsigned char *);
    int GetOpenGLID();
protected:
    unsigned int m_OpenGLID;
};

#endif // HLIGHTMAP_H

