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
#include "hguidesktop.h" // class's header file

// class constructor
HGUIDesktop::HGUIDesktop() {
    // insert your code here
    m_pFuncOnMouseDown=NULL;
    m_pFuncOnKeyDown=NULL;
    m_pWindowModal=NULL;
    m_DragInfo.isDraging=false;
}

// class destructor
HGUIDesktop::~HGUIDesktop() {
    list<HGUIPanel*>::iterator piter;
    for (piter=m_plPanels.begin();piter!=m_plPanels.end();++piter) {
        delete (*piter);
    }
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        delete (*biter);
    }
    list<HGUIWindow*>::iterator witer;
    for (witer=m_plWindows.begin();witer!=m_plWindows.end();++witer) {
        delete (*witer);
    }
}

// tworzy na pulpicie okno
HGUIWindow * HGUIDesktop::NewWindow(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIWindow * win=NULL;
    win=new HGUIWindow(w,h,x,y);
    assert(win);
    m_plWindows.push_back(win);
    //debug("created window\n");
    return win;
}

// tworzy na pulpicie panel
HGUIPanel * HGUIDesktop::NewPanel(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIPanel * panel=NULL;
    panel=new HGUIPanel(w,h,x,y);
    assert(panel);
    m_plPanels.push_back(panel);
//  debug("created panel\n");
    return panel;
}

// tworzy na pulpicie button
HGUIButton * HGUIDesktop::NewButton(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIButton * button=NULL;
    button=new HGUIButton(w,h,x,y);
    assert(button);
    m_plButtons.push_back(button);
// debug("created button\n");
    return button;
}

// renderuje pulpit
void HGUIDesktop::Render() {
    /* TODO (#1#): Implement HGUIDesktop::Render() */
    list<HGUIPanel*>::iterator piter;
    for (piter=m_plPanels.begin();piter!=m_plPanels.end();++piter) {
        (*piter)->Render();
    }
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        (*biter)->Render();
    }
    list<HGUIWindow*>::iterator witer;
    for (witer=m_plWindows.begin();witer!=m_plWindows.end();++witer) {
        (*witer)->Render();
    }

}

// robi updejt pulpitu
void HGUIDesktop::Update() {
    /* TODO (#1#): Implement HGUIDesktop::Update() */
    /*  list<HGUIPanel*>::iterator piter;
        for(piter=m_plPanels.begin();piter!=m_plPanels.end();++piter){
        (*piter)->Update();
        }
        list<HGUIButton*>::iterator biter;
        for(biter=m_plButtons.begin();biter!=m_plButtons.end();++biter){
        (*biter)->Update();
        }*/

    if (m_DragInfo.isDraging) {
        int deltax=HGUI::GetSingleton().m_Mouse.CursorPos[0]-m_DragInfo.dragstartx;
        int deltay=HGUI::GetSingleton().m_Mouse.CursorPos[1]-m_DragInfo.dragstarty;
        m_DragInfo.obj->m_ix=m_DragInfo.startdraginfo.m_ix+deltax;
        m_DragInfo.obj->m_iy=m_DragInfo.startdraginfo.m_iy+deltay;
    }


    list<HGUIWindow*>::iterator witer;
    for (witer=m_plWindows.begin();witer!=m_plWindows.end();++witer) {
        (*witer)->Update();
    }
}

// odbiera zdarzenie wcini�ia klawisza myszy
void HGUIDesktop::MouseDown(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseDown() */
    bool onobj=false;

    /*  if(m_pWindowModal){
        HGUIWindow *win=m_pWindowModal;
        if(win->m_bCanClose&&y>=win->m_iy+8&&y<=win->m_iy+24&&x>win->m_ix+win->m_iWidth-22&&x<win->m_ix+win->m_iWidth-6){
        win->m_bClosing=true;
        onobj=true;
        return;
        }
        if(x>=win->m_ix&&x<=win->m_ix+win->m_iWidth){
        if(y>=win->m_iy&&y<=win->m_iy+27){
        m_DragInfo.dragstartx=x;
        m_DragInfo.dragstarty=y;
        m_DragInfo.isDraging=true;
        m_DragInfo.obj=win;
        m_DragInfo.startdraginfo=*win;
        onobj=true;
        return;
        }
        if(y>win->m_iy+27&&y<=win->m_iy+win->m_iHeight){
        win->MouseDown(x-(win->m_ix+4),y-(win->m_iy+27));
        onobj=true;
        return;
        }
        }
        return;
        }
    */
    list<HGUIWindow*>::iterator witer;
    for (witer=--m_plWindows.end();witer!=--m_plWindows.begin();--witer) {
        HGUIWindow *win=(*witer);
        if (!win->m_bVisible) continue;
        if (win->m_bCanClose&&y>=win->m_iy+8&&y<=win->m_iy+24&&x>win->m_ix+win->m_iWidth-22&&x<win->m_ix+win->m_iWidth-6) {
            win->m_bClosing=true;
            onobj=true;
            break;
        }
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth) {

            if (y>=win->m_iy&&y<=win->m_iy+27) {
                m_DragInfo.dragstartx=x;
                m_DragInfo.dragstarty=y;
                m_DragInfo.isDraging=true;
                m_DragInfo.obj=win;
                m_DragInfo.startdraginfo=*win;
                m_plWindows.erase(witer);
                m_plWindows.push_back(*witer);
                onobj=true;
                break;
            }
            if (y>win->m_iy+27&&y<=win->m_iy+win->m_iHeight) {

                win->MouseDown(x-(win->m_ix+4),y-(win->m_iy+27));
                m_plWindows.erase(witer);
                m_plWindows.push_back(*witer);
                onobj=true;
                break;
            }
        }

    }
    if (!onobj) {
        list<HGUIPanel*>::iterator piter;
        for (piter=m_plPanels.begin();piter!=m_plPanels.end();++piter) {
            HGUIPanel *win=(*piter);
            if (!win->m_bVisible) continue;
            if (x>=win->m_ix+2&&x<=win->m_ix+win->m_iWidth-2) {
                if (y>=win->m_iy+2&&y<=win->m_iy+win->m_iHeight-2) {
                    win->MouseDown(x-(win->m_ix+2),y-(win->m_iy+2));
                    onobj=true;
                    break;
                }
            }
        }
    }

    if (!onobj) {
        list<HGUIButton*>::iterator biter;
        for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
            HGUIButton *win=(*biter);
            if (!win->m_bVisible) continue;
            if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth)
                if (y>=win->m_iy&&y<=win->m_iy+win->m_iHeight) {
                    win->m_bPressed=true;
                    onobj=true;
                    break;
                }
        }
    }
    if (!onobj&&m_pFuncOnMouseDown) {
        m_pFuncOnMouseDown();
    }


}

// odbiera zdarzenie puszczenia klawisza myszy
void HGUIDesktop::MouseUp(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseUp() */
    m_DragInfo.isDraging=false;
    /*  if(m_pWindowModal){
        HGUIWindow *win=m_pWindowModal;
        if(!win->m_bVisible) return;
        if(win->m_bCanClose&&win->m_bClosing&&y>=win->m_iy+8&&y<=win->m_iy+24&&x>win->m_ix+win->m_iWidth-22&&x<win->m_ix+win->m_iWidth-6){
        win->Close();
        m_pWindowModal=NULL;
        return;
        }
        if(x>=win->m_ix&&x<=win->m_ix+win->m_iWidth){
        if(y>win->m_iy&&y<=win->m_iy+win->m_iHeight){
        win->MouseUp(x-(win->m_ix+4),y-(win->m_iy+27));
        }
        }
        win->MouseReleasedOutside();
        return;
        }
    */

    list<HGUIWindow*>::iterator witer;
    for (witer=--m_plWindows.end();witer!=--m_plWindows.begin();--witer) {
        HGUIWindow *win=(*witer);
        if (!win->m_bVisible) continue;
        if (win->m_bCanClose&&win->m_bClosing&&y>=win->m_iy+8&&y<=win->m_iy+24&&x>win->m_ix+win->m_iWidth-22&&x<win->m_ix+win->m_iWidth-6) {
            win->Close();
            break;
        }
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth) {
            if (y>win->m_iy&&y<=win->m_iy+win->m_iHeight) {
                win->MouseUp(x-(win->m_ix+4),y-(win->m_iy+27));
                /*  m_plWindows.erase(witer);
                    m_plWindows.push_back(*witer);
                    break;*/
            }
        }
        win->MouseReleasedOutside();
    }

    list<HGUIPanel*>::iterator piter;
    for (piter=--m_plPanels.end();piter!=--m_plPanels.begin();--piter) {
        HGUIPanel *win=(*piter);
        if (!win->m_bVisible) continue;
        if (x>=win->m_ix+2&&x<=win->m_ix+win->m_iWidth-4) {
            if (y>win->m_iy+2&&y<=win->m_iy+win->m_iHeight-4) {
                win->MouseUp(x-(win->m_ix+2),y-(win->m_iy+2));
                /*  m_plWindows.erase(witer);
                    m_plWindows.push_back(*witer);
                    break;*/
            }
        }
        win->MouseReleasedOutside();
    }

    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        if (!win->m_bVisible) continue;
        if (!win->m_bPressed) continue;
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth)
            if (y>=win->m_iy&&y<=win->m_iy+27) {
                win->Click();
            }
        win->m_bPressed=false;
    }

}

// odbiera wcini�ie klawiszy
void HGUIDesktop::HandleKey(int key) {
    /* TODO (#1#): Implement HGUIDesktop::HandleKey() */
    if (m_pFuncOnKeyDown) {
        m_pFuncOnKeyDown(key);
    }
}

// przenosi okno na szczyt
void HGUIDesktop::BringToFront(HGUIWindow * window) {
    /* TODO (#1#): Implement HGUIDesktop::BringToFront() */
    if (window==NULL) return;
    list<HGUIWindow*>::iterator witer;
    for (witer=m_plWindows.begin();witer!=m_plWindows.end();++witer) {
        HGUIWindow *win=(*witer);
        if (window==win) {
            m_plWindows.erase(witer);
            m_plWindows.push_back(*witer);
            return;
        }
    }
}

// ustawia okno jako modalne
void HGUIDesktop::ShowModal(HGUIWindow * window) {
    /* TODO (#1#): Implement HGUIDesktop::ShowModal() */
    BringToFront(window);
    m_pWindowModal=window;
}

