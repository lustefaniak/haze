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

#ifndef HGUI_H
#define HGUI_H

#include "hguidesktop.h"
#include "hguimouse.h"

#define newtypedef(type) HGUI##type## * New##type##();
#define newtypeimp(parenttype,type)

/*
 * zajmuje si�obsug gui
 */
class HGUI : public Singleton<HGUI> {
public:
    // class constructor
    HGUI();
    // class destructor
    ~HGUI();
    // zwraca nowy desktop
    HGUIDesktop *CreateDesktop(bool setcurrent=true);
    HGUIDesktop *m_pCurrentDesktop;
    HGUIMouse   m_Mouse;
    HFont m_DefaultFont;
    // ustawia podany desktop jako aktualny
    bool SetCurrentDesktop(HGUIDesktop * desktop);
    // zwraca aktualny desktop
    HGUIDesktop * GetCurrentDesktop();
    // wykonuje rendering aktualnego pulpitu
    void Render();
    // konczy renderowanie w trybie 2d
    void End2D();
    // rozpoczyna renderowanie w trypbie 2d
    void Begin2D();
    int GUITextureID;
    list<HGUIDesktop *> m_plDesktops;
    // odbiera przesuni�ie myszy
    void MouseMove(int deltax, int deltay);
    // robi upejt GUI
    void Update();
    float m_fTransparency;
    // ustawia kolor
    void SetupColor(float r, float g, float b);
    bool m_bActive;
    // odbiera zdarzenie wcisni�ia klawisza
    void HandleKey(int key);
    // odbiera wcini�ie klawisza myszy, narazie tylko lewego
    void MouseState(bool down);
    // renderuje tekst jednoliniowy bez resetu macierzy
    void DrawText(int x, int y, int size, const char *str,...);
    int m_iFont;
    void SetFontSet(int x); // sets the value of m_FontSet
    int GetFontSet(); // returns the value of m_FontSet
private:
    // aktualna subczcionka
    int m_FontSet;
};

extern HGUI * gHGUI;

#endif // HGUI_H

