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

#ifndef HTEXTURE_H
#define HTEXTURE_H


/*
 * klasa do przechowywania openglowej tekstury oraz do obsugi tekstur
 * dynamicznych i z moliwoci rysowania z wew. j�yka programowania
 */
class HTexture {
public:
    // class constructor
    HTexture(string name);
    // class destructor
    virtual ~HTexture();
    // robi updejt
    virtual int Update() = 0L;
    // wczytuje si�z pliku
    virtual int Load(string filename) = 0L;
    // wysya tekstur�do opengl'a
    virtual int Bind() = 0L;
    unsigned int GetOpenGLID(); // returns the value of m_uiID
    string GetName(); // returns the value of m_sName
    unsigned int GetWidth(); // returns the value of m_iWidth
    unsigned int GetHeight(); // returns the value of m_uiHeight
    // przechowuje jaki id ma tekstura w managerze
    int m_iManagerID;
    int m_iReferences;
//  protected:
    // przechowuje id opengl'owy
    unsigned int m_uiID;
    // przechowuje nazw�tekstury
    string m_sName;
    // szeroko�tekstury
    unsigned int m_uiWidth;
    // wysoko�tekstury
    unsigned int m_uiHeight;


};

#endif // HTEXTURE_H

