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
#include "hguiwindow.h" // class's header file

// class constructor
HGUIWindow::HGUIWindow(int w, int h, int x, int y) {
    m_bVisible=true;
    m_iHeight=h;
    m_iWidth=w;
    m_ix=x;
    m_iy=y;
    m_bCanClose=true;
    m_pFuncOnClose=NULL;
    m_pFuncOnShow=NULL;
}

// class destructor
HGUIWindow::~HGUIWindow() {
    list<HGUIPanel*>::iterator piter;
    for (piter=m_plPanels.begin();piter!=m_plPanels.end();++piter) {
        delete (*piter);
    }
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        delete (*biter);
    }
    list<HGUILabel*>::iterator liter;
    for (liter=m_plLabels.begin();liter!=m_plLabels.end();++liter) {
        delete (*liter);
    }
}

// renderuje okno
void HGUIWindow::Render() {
    /* DONE (#1#): Implement HGUIWindow::Render() */
    if (m_bVisible) {
        HGUI::GetSingleton().SetupColor(1,1,1);
        glPushMatrix();
        glTranslatef(m_ix, m_iy, 0);
        glBegin(GL_QUADS);

        // top left corner of window.
        glTexCoord2f( 0.0f/128.0f, 1.0f);
        glVertex2f(0, 0);
        glTexCoord2f( 0.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(0, 27);
        glTexCoord2f(64.0f/128.0f, 1-27/128.0f);
        glVertex2f(63, 27);
        glTexCoord2f(64.0f/128.0f, 1.0f);
        glVertex2f(63, 0);

        // top of window.
        glTexCoord2f(64.0f/128.0f, 1.0f);
        glVertex2f(63, 0);
        glTexCoord2f(64.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(63, 27);
        glTexCoord2f(96.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(m_iWidth-32, 27);
        glTexCoord2f(96.0f/128.0f, 1.0f);
        glVertex2f(m_iWidth-32, 0);

        // top right corder of window.
        glTexCoord2f(96.0f/128.0f, 1.0f);
        glVertex2f(m_iWidth-32, 0);
        glTexCoord2f(96.0f/128.0f, 1.0f-27/128.0f);
        glVertex2f(m_iWidth-32, 27);
        glTexCoord2f(1.0f, 1.0f-27.0f/128.0f);
        glVertex2f(m_iWidth, 27);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(m_iWidth, 0);

        // left side of window.
        glTexCoord2f(0.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(0, 27);
        glTexCoord2f(0.0f/128.0f, 27.0f/128.0f);
        glVertex2f(0, m_iHeight-27);
        glTexCoord2f(6.0f/128.0f, 27.0f/128.0f);
        glVertex2f(6,m_iHeight-27);
        glTexCoord2f(6.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(6, 27);

        // draw the main body of the window
        glTexCoord2f( 9.0f/128.0f, 96.0f/128.0f);
        glVertex2f(6, 27);
        glTexCoord2f( 9.0f/128.0f, 64.0f/128.0f);
        glVertex2f(6, m_iHeight-25);
        glTexCoord2f(39.0f/128.0f, 64.0f/128.0f);
        glVertex2f(m_iWidth-7, m_iHeight-25);
        glTexCoord2f(39.0f/128.0f, 96.0f/128.0f);
        glVertex2f(m_iWidth-7, 27);

        // right side of window.
        glTexCoord2f(1.0f-7.0f/128.0f, 1.0f-27.0f/128.0f);
        glVertex2f(m_iWidth-7, 27);
        glTexCoord2f(1.0f-7.0f/128.0f, 27.0f/128.0f);
        glVertex2f(m_iWidth-7, m_iHeight-27);
        glTexCoord2f(1.0f,   27.0f/128.0f);
        glVertex2f(m_iWidth,m_iHeight-27);
        glTexCoord2f(1.0f, 1.0f-27.0f/128.0f);
        glVertex2f(m_iWidth, 27);

        // bottom left corner of window.
        glTexCoord2f( 0.0f/128.0f, 27.0f/128.0f);
        glVertex2f(0, m_iHeight-27);
        glTexCoord2f( 0.0f/128.0f,  0.0f/128.0f);
        glVertex2f(0, m_iHeight);
        glTexCoord2f(64.0f/128.0f,  0.0f/128.0f);
        glVertex2f(63, m_iHeight);
        glTexCoord2f(64.0f/128.0f, 27.0f/128.0f);
        glVertex2f(63, m_iHeight-27);

        // bottom of window.
        glTexCoord2f(64.0f/128.0f, 27.0f/128.0f);
        glVertex2f(63, m_iHeight-27);
        glTexCoord2f(64.0f/128.0f, 0.0f/128.0f);
        glVertex2f(63, m_iHeight);
        glTexCoord2f(96.0f/128.0f, 0.0f/128.0f);
        glVertex2f(m_iWidth-32, m_iHeight);
        glTexCoord2f(96.0f/128.0f, 27.0f/128.0f);
        glVertex2f(m_iWidth-32, m_iHeight-27);

        // bottom right corder of window.
        glTexCoord2f(96.0f/128.0f, 27.0f/128.0f);
        glVertex2f(m_iWidth-32, m_iHeight-27);
        glTexCoord2f(96.0f/128.0f, 0.0f/128.0f);
        glVertex2f(m_iWidth-32, m_iHeight);
        glTexCoord2f(1.0f, 0.0f/128.0f);
        glVertex2f(m_iWidth, m_iHeight);
        glTexCoord2f(1.0f, 27.0f/128.0f);
        glVertex2f(m_iWidth, m_iHeight-27);
        glEnd();
        if (m_bCanClose) {
            if (m_bClosing) {
                glBegin(GL_QUADS);
                // window close button
                glTexCoord2f(104.0f/128.0f, 80.0f/128.0f);
                glVertex2f(m_iWidth-22, 8);
                glTexCoord2f(104.0f/128.0f, 64.0f/128.0f);
                glVertex2f(m_iWidth-22, 24);
                glTexCoord2f(120.0f/128.0f, 64.0f/128.0f);
                glVertex2f(m_iWidth-6, 24);
                glTexCoord2f(120.0f/128.0f, 80.0f/128.0f);
                glVertex2f(m_iWidth-6, 8);
                glEnd();
            } else {
                glBegin(GL_QUADS);
                // window close button
                glTexCoord2f(104.0f/128.0f, 96.0f/128.0f);
                glVertex2f(m_iWidth-22, 8);
                glTexCoord2f(104.0f/128.0f, 80.0f/128.0f);
                glVertex2f(m_iWidth-22, 24);
                glTexCoord2f(120.0f/128.0f, 80.0f/128.0f);
                glVertex2f(m_iWidth-6, 24);
                glTexCoord2f(120.0f/128.0f, 96.0f/128.0f);
                glVertex2f(m_iWidth-6, 8);
                glEnd();
            }
        }
        if (!m_sCaption.empty()) {
            HGUI::GetSingleton().DrawText(8,8,14,m_sCaption.c_str());

        }
        glTranslatef(4,27,0);
        list<HGUIPanel*>::iterator piter;
        for (piter=m_plPanels.begin();piter!=m_plPanels.end();++piter) {
            (*piter)->Render();
        }
        list<HGUIButton*>::iterator biter;
        for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
            (*biter)->Render();
        }
        list<HGUILabel*>::iterator liter;
        for (liter=m_plLabels.begin();liter!=m_plLabels.end();++liter) {
            (*liter)->Render();
        }
        glPopMatrix();
    }
}


// tworzy na pulpicie panel
HGUIPanel * HGUIWindow::NewPanel(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIPanel * panel=NULL;
    panel=new HGUIPanel(w,h,x,y);
    assert(panel);
    m_plPanels.push_back(panel);
    return panel;
//  debug("created panel\n");
}

// tworzy na pulpicie button
HGUIButton * HGUIWindow::NewButton(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIButton * button=NULL;
    button=new HGUIButton(w,h,x,y);
    assert(button);
    m_plButtons.push_back(button);
    return button;
//  debug("created button\n");
}

// tworzy na pulpicie label
HGUILabel * HGUIWindow::NewLabel(int x, int y, string text) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUILabel * button=NULL;
    button=new HGUILabel;
    assert(button);
    m_plLabels.push_back(button);
    button->m_ix=x;
    button->m_iy=y;
    button->m_sText=text;
    return button;
//  debug("created label\n");
}

// robi updejt okna
void HGUIWindow::Update() {
    /* TODO (#1#): Implement HGUIWindow::Update() */
    if (m_ix<0) m_ix=0;
    if (m_iy<0) m_iy=0;
    if (m_iHeight<27+25+1) m_iHeight=27+25+1;
    if (m_iWidth<60) m_iWidth=60;
    if (m_ix+m_iWidth>HRendererWindow::GetSingleton().GetWidth()) m_ix=HRendererWindow::GetSingleton().GetWidth()-m_iWidth;
    if (m_iy+m_iHeight>HRendererWindow::GetSingleton().GetHeight()) m_iy=HRendererWindow::GetSingleton().GetHeight()-m_iHeight;
}

// zamyka okno
void HGUIWindow::Close() {
    /* TODO (#1#): Implement HGUIWindow::Close() */
    if (!m_bCanClose) return;
    m_bVisible=false;
    if (m_pFuncOnClose!=NULL) {
        m_pFuncOnClose();
    }
}

// otwiera okno
void HGUIWindow::Open() {
    /* TODO (#1#): Implement HGUIWindow::Open() */
    m_bVisible=true;
}

// odbiera zdarzenie wcini�ia klawisza myszy
void HGUIWindow::MouseDown(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseDown() */

    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth)
            if (y>=win->m_iy&&y<=win->m_iy+win->m_iHeight) {
                win->m_bPressed=true;
            }

    }

}

void HGUIWindow::MouseUp(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseUp() */
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        if (!win->m_bPressed) continue;
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth)
            if (y>=win->m_iy&&y<=win->m_iy+win->m_iHeight) {
                win->Click();
            }
        win->m_bPressed=false;
    }

}

// ustawia stan guziczk�
void HGUIWindow::MouseReleasedOutside() {
    /* TODO (#1#): Implement HGUIWindow::MouseReleasedOutside() */
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        win->m_bPressed=false;
    }
    m_bClosing=false;
}

