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

#ifndef HGUIWINDOW_H
#define HGUIWINDOW_H

#include "hguiobject.h"
#include "hguipanel.h"
#include "hguibutton.h"
#include "hguilabel.h"

/*
 * zwyke okno
 */
class HGUIWindow : public HGUIObject {
public:
    // class constructor
    HGUIWindow(int w, int h, int x, int y);
    // class destructor
    ~HGUIWindow();
    // renderuje okno
    void Render();
    HGUIPanel * NewPanel(int w, int h, int x=0, int y=0);
    HGUIButton * NewButton(int w, int h, int x=0, int y=0);
    HGUILabel * NewLabel(int x, int y, string text);
    string m_sCaption;
    // robi updejt okna
    void Update();
    // zamyka okno
    void Close();
    // otwiera okno
    void Open();
    void MouseDown(int x, int y);
    void MouseUp(int x, int y);
    bool m_bClosing;
    bool m_bCanClose;
    // ustawia stan guziczk�
    void MouseReleasedOutside();
    int (*m_pFuncOnClose) ();
    int (*m_pFuncOnShow) ();
protected:
    list<HGUIPanel *> m_plPanels;
    list<HGUIButton *> m_plButtons;
    list<HGUILabel *> m_plLabels;
};

#endif // HGUIWINDOW_H

