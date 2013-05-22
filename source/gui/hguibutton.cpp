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
#include "hguibutton.h" // class's header file

// class constructor
HGUIButton::HGUIButton(int w, int h, int x, int y) {
    // insert your code here
    m_bPressed=false;
    m_bVisible=true;
    m_iHeight=h;
    m_iWidth=w;
    m_ix=x;
    m_iy=y;
    m_pFuncOnClick=NULL;
}

// class destructor
HGUIButton::~HGUIButton() {
    // insert your code here
}

// renderuje guziczek
void HGUIButton::Render() {
    /* TODO (#1#): Implement HGUIButton::Render() */
    if (m_bVisible) {
        HGUI::GetSingleton().SetupColor(1,1,1);
        if (m_bPressed) {
            glBegin(GL_QUADS);

            //left, bottom
            //left, top
            //right, bottom
            //right, top


            // left side
            glTexCoord2f(57.0f/128, 95.0f/128);
            glVertex2f(m_ix, m_iy);
            glTexCoord2f(57.0f/128, 70.0f/128);
            glVertex2f(m_ix, m_iy+m_iHeight);
            glTexCoord2f(62.0f/128, 70.0f/128);
            glVertex2f(m_ix+6,m_iy+m_iHeight);
            glTexCoord2f(62.0f/128, 95.0f/128);
            glVertex2f(m_ix+6, m_iy);

            // middle
            glTexCoord2f(62.0f/128, 95.0f/128);
            glVertex2f(m_ix+6, m_iy);
            glTexCoord2f(62.0f/128, 70.0f/128);
            glVertex2f(m_ix+6, m_iy+m_iHeight);
            glTexCoord2f(66.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy+m_iHeight);
            glTexCoord2f(66.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy);

            // right side
            glTexCoord2f(66.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy);
            glTexCoord2f(66.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy+m_iHeight);
            glTexCoord2f(71.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth, m_iy+m_iHeight);
            glTexCoord2f(71.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth, m_iy);

            glEnd();
        } else {
            glBegin(GL_QUADS);
            // left side
            glTexCoord2f(41.0f/128, 95.0f/128);
            glVertex2f(m_ix, m_iy);
            glTexCoord2f(41.0f/128, 70.0f/128);
            glVertex2f(m_ix, m_iy+m_iHeight);
            glTexCoord2f(46.0f/128, 70.0f/128);
            glVertex2f(m_ix+6,m_iy+m_iHeight);
            glTexCoord2f(46.0f/128, 95.0f/128);
            glVertex2f(m_ix+6, m_iy);

            // middle
            glTexCoord2f(46.0f/128, 95.0f/128);
            glVertex2f(m_ix+6, m_iy);
            glTexCoord2f(46.0f/128, 70.0f/128);
            glVertex2f(m_ix+6, m_iy+m_iHeight);
            glTexCoord2f(50.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy+m_iHeight);
            glTexCoord2f(50.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy);

            // right side
            glTexCoord2f(50.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy);
            glTexCoord2f(50.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth-6, m_iy+m_iHeight);
            glTexCoord2f(55.0f/128, 70.0f/128);
            glVertex2f(m_ix+m_iWidth, m_iy+m_iHeight);
            glTexCoord2f(55.0f/128, 95.0f/128);
            glVertex2f(m_ix+m_iWidth, m_iy);

            glEnd();
        }
        if (!m_sCaption.empty()) {
            HGUI::GetSingleton().DrawText(m_ix+m_iWidth/2-strlen(m_sCaption.c_str())*6*0.9f,m_iy+m_iHeight/2-6,12,m_sCaption.c_str());
        }
    }

}

// wywouje funkcj�onclick
void HGUIButton::Click() {
    /* TODO (#1#): Implement HGUIButton::Click() */
    m_bPressed=false;
    if (m_pFuncOnClick!=NULL) {
        m_pFuncOnClick();
    }
}

