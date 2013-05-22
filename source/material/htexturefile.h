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

#ifndef HTEXTUREFILE_H
#define HTEXTUREFILE_H

#include "htexture.h" // inheriting class's header file

/*
 * klasa adowana z pliku
 */
class HTextureFile : public HTexture {
public:
    // class constructor
    HTextureFile(string filename);
    // class destructor
    ~HTextureFile();
    // wczytuje tekstur�z pliku
    int Load(string filename);
    // aduje tekstur�do karty
    int Bind();
    // pusta funkcja ale musi by�
    int Update();
};

class HTextureFileAnim : public HTexture {
public:
    // class constructor
    HTextureFileAnim(string filename);
    // class destructor
    ~HTextureFileAnim();
    // wczytuje tekstur�z pliku
    int Load(string filename);
    // aduje tekstur�do karty
    int Bind();
    // pusta funkcja ale musi by�
    int Update();
    int numFrames;
    unsigned int Frames[32];
    int CurrentFrame;
};

#endif // HTEXTUREFILE_H

