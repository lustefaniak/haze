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

#ifndef HGUIDESKTOP_H
#define HGUIDESKTOP_H

#include "hguiwindow.h"
#include "hguipanel.h"
#include "hguibutton.h"

/*
 * przechowuje aktualnie widoczny pulpit
 */
class HGUIDesktop {
public:
    // class constructor
    HGUIDesktop();
    // class destructor
    ~HGUIDesktop();
    // tworzy na pulpicie okno
    HGUIWindow * NewWindow(int w, int h, int x=0, int y=0);
    HGUIPanel * NewPanel(int w, int h, int x=0, int y=0);
    HGUIButton * NewButton(int w, int h, int x=0, int y=0);
    // renderuje pulpit
    void Render();
    // robi updejt pulpitu
    void Update();
    struct {
        bool isDraging;
        int dragstartx;
        int dragstarty;
        HGUIObject startdraginfo;
        HGUIObject * obj;
    }
    m_DragInfo;
    // odbiera zdarzenie puszczenia klawisza myszy
    void MouseUp(int x, int y);
    // odbiera zdarzenie wcini�ia klawisza myszy
    void MouseDown(int x, int y);
    // odbiera wcini�ie klawiszy
    void HandleKey(int key);
    // przenosi okno na szczyt
    void BringToFront(HGUIWindow * win);
    // ustawia okno jako modalne
    void ShowModal(HGUIWindow * window);
    int (*m_pFuncOnMouseDown) ();
    int (*m_pFuncOnKeyDown) (int);
protected:
    list<HGUIWindow *> m_plWindows;
    list<HGUIPanel *> m_plPanels;
    list<HGUIButton *> m_plButtons;
    HGUIWindow * m_pWindowModal;

};

#endif // HGUIDESKTOP_H

