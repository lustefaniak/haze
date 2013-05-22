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

#ifndef HRENDERERWINDOW_H
#define HRENDERERWINDOW_H


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../core/singleton.h"

#define RW_FULLSCREEN (1<<1)

/*
 * okno renderujce
 */
class HRendererWindow : public Singleton<HRendererWindow> {
public:
    // class constructor
    HRendererWindow();
    // class destructor
    ~HRendererWindow();
    // robi updejt
    int Update();
    // otwiera okno renderujce
    int Open(int w=800, int h=600, int bpp=32, int flags=0);
    int GetWidth(); // returns the value of m_iWidth
    int GetHeight(); // returns the value of m_iHeight
    int GetBPP(); // returns the value of m_iBPP
    bool IsOpened(); // returns the value of m_iOpened
    // zamuka aktualnie otwarte okno
    int Close();
private:
    // szeroko�okna
    int m_iWidth;
    // wysoko�okna renderujcego
    int m_iHeight;
    // g�ia kolor�
    int m_iBPP;
    // sprawdza czy okno zostao otwarte
    bool m_iOpened;
};

extern HRendererWindow * gHRendererWindow;

#endif // HRENDERERWINDOW_H

