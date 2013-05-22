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
#include "hguipanel.h" // class's header file

// class constructor
HGUIPanel::HGUIPanel(int w, int h, int x, int y) {
    // insert your code here
    m_bVisible=true;
    m_iHeight=h;
    m_iWidth=w;
    m_ix=x;
    m_iy=y;
}

// class destructor
HGUIPanel::~HGUIPanel() {
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        delete (*biter);
    }
}

// renderuje si�
void HGUIPanel::Render() {
    /* TODO (#1#): Implement HGUIPanel::Render() */
    if (m_bVisible) {
        HGUI::GetSingleton().SetupColor(1,1,1);
        glBegin(GL_QUADS);

        //left, bottom
        //left, top
        //right, bottom
        //right, top

        // top left corner of panel.
        glTexCoord2f( 8.0f/128, 64.0f/128);
        glVertex2f(m_ix, m_iy);
        glTexCoord2f( 8.0f/128, 54.0f/128);
        glVertex2f(m_ix, m_iy+10);
        glTexCoord2f(18.0f/128, 54.0f/128);
        glVertex2f(m_ix+10, m_iy+10);
        glTexCoord2f(18.0f/128, 64.0f/128);
        glVertex2f(m_ix+10, m_iy);

        // top of panel.
        glTexCoord2f(18.0f/128, 64.0f/128);
        glVertex2f(m_ix+10, m_iy);
        glTexCoord2f(18.0f/128, 54.0f/128);
        glVertex2f(m_ix+10, m_iy+10);
        glTexCoord2f(30.0f/128, 54.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy+10);
        glTexCoord2f(30.0f/128, 64.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy);

        // top right corder of panel.
        glTexCoord2f(30.0f/128, 64.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy);
        glTexCoord2f(30.0f/128, 54.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy+10);
        glTexCoord2f(40.0f/128, 54.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy+10);
        glTexCoord2f(40.0f/128, 64.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy);

        // left side of panel.
        glTexCoord2f( 8.0f/128, 54.0f/128);
        glVertex2f(m_ix, m_iy+10);
        glTexCoord2f( 8.0f/128, 42.0f/128);
        glVertex2f(m_ix, m_iy+m_iHeight-10);
        glTexCoord2f(18.0f/128, 42.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight-10);
        glTexCoord2f(18.0f/128, 54.0f/128);
        glVertex2f(m_ix+10, m_iy+10);

        // middle of panel.
        glTexCoord2f(18.0f/128, 54.0f/128);
        glVertex2f(m_ix+10, m_iy+10);
        glTexCoord2f(18.0f/128, 42.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight-10);
        glTexCoord2f(30.0f/128, 42.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy+m_iHeight-10);
        glTexCoord2f(30.0f/128, 54.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy+10);

        // right side of panel.
        glTexCoord2f(30.0f/128, 54.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy+10);
        glTexCoord2f(30.0f/128, 42.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy+m_iHeight-10);
        glTexCoord2f(40.0f/128, 42.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy+m_iHeight-10);
        glTexCoord2f(40.0f/128, 54.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy+10);

        // bottom left corner of panel.
        glTexCoord2f( 8.0f/128, 42.0f/128);
        glVertex2f(m_ix, m_iy+m_iHeight-10);
        glTexCoord2f( 8.0f/128, 32.0f/128);
        glVertex2f(m_ix, m_iy+m_iHeight);
        glTexCoord2f(18.0f/128, 32.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight);
        glTexCoord2f(18.0f/128, 42.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight-10);

        // bottom middle of panel.
        glTexCoord2f(18.0f/128, 42.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight-10);
        glTexCoord2f(18.0f/128, 32.0f/128);
        glVertex2f(m_ix+10, m_iy+m_iHeight);
        glTexCoord2f(30.0f/128, 32.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy+m_iHeight);
        glTexCoord2f(30.0f/128, 42.0f/128);
        glVertex2f(m_ix+10+(m_iWidth-20), m_iy+m_iHeight-10);

        // bottom right corner of panel.
        glTexCoord2f(30.0f/128, 42.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy+m_iHeight-10);
        glTexCoord2f(30.0f/128, 32.0f/128);
        glVertex2f(m_ix+m_iWidth-10, m_iy+m_iHeight);
        glTexCoord2f(40.0f/128, 32.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy+m_iHeight);
        glTexCoord2f(40.0f/128, 42.0f/128);
        glVertex2f(m_ix+m_iWidth, m_iy+m_iHeight-10);

        glEnd();
        HGUI::GetSingleton().SetupColor(1,1,1);
        glPushMatrix();
        glTranslatef(m_ix+2, m_iy+2, 0);
        list<HGUIButton*>::iterator biter;
        for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
            (*biter)->Render();
        }
        glPopMatrix();
    }

}

// odbiera zdarzenie wcini�ia klawisza myszy
void HGUIPanel::MouseDown(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseDown() */
//  debug("mouse down on panel");
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        if (x>=win->m_ix&&x<=win->m_ix+win->m_iWidth)
            if (y>=win->m_iy&&y<=win->m_iy+win->m_iHeight) {
                win->m_bPressed=true;
            }

    }

}

void HGUIPanel::MouseUp(int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::MouseUp() */
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        if (!win->m_bPressed) continue;
        if (x>=win->m_ix+2&&x<=win->m_ix+win->m_iWidth-2)
            if (y>=win->m_iy+2&&y<=win->m_iy+win->m_iHeight-2) {
                win->Click();
            }
        win->m_bPressed=false;
    }

}

// ustawia stan guziczk�
void HGUIPanel::MouseReleasedOutside() {
    /* TODO (#1#): Implement HGUIWindow::MouseReleasedOutside() */
    list<HGUIButton*>::iterator biter;
    for (biter=m_plButtons.begin();biter!=m_plButtons.end();++biter) {
        HGUIButton *win=(*biter);
        win->m_bPressed=false;
    }
}


// tworzy na pulpicie button
HGUIButton * HGUIPanel::NewButton(int w, int h, int x, int y) {
    /* TODO (#1#): Implement HGUIDesktop::CreateWindow() */
    HGUIButton * button=NULL;
    button=new HGUIButton(w,h,x,y);
    assert(button);
    m_plButtons.push_back(button);
    return button;
//  debug("created button\n");
}

