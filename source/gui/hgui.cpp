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
#include "hgui.h" // class's header file

template<> HGUI * Singleton<HGUI>::ms_Singleton = 0;

HGUI * gHGUI=NULL;

// class constructor
HGUI::HGUI() : m_DefaultFont("GUI_font") {
    // insert your code here
    m_pCurrentDesktop=NULL;
    GUITextureID=-1;
    m_fTransparency=0.9;
    m_bActive=false;
    m_iFont=-1;
    m_FontSet=0;
    if (gHGUI==NULL) {
        gHGUI=this;
    }
//  GUITextureID=HTextureManager::GetSingleton().Load("GUI");
}

// class destructor
HGUI::~HGUI() {
    list<HGUIDesktop*>::iterator diter;
    for (diter=m_plDesktops.begin();diter!=m_plDesktops.end();++diter) {
        delete (*diter);
    }
    if (gHGUI==this) {
        gHGUI=NULL;
    }
}

// zwraca nowy desktop
HGUIDesktop *HGUI::CreateDesktop(bool setcurrent) {
    /* TODO (#1#): Implement HGUI::CreateDesktop() */
    HGUIDesktop * desk=NULL;
    desk=new HGUIDesktop;
    assert(desk);
    if (setcurrent) {
        m_pCurrentDesktop=desk;
    }
    m_plDesktops.push_back(desk);
    return desk;
}

// ustawia podany desktop jako aktualny
bool HGUI::SetCurrentDesktop(HGUIDesktop * desktop) {
    /* TODO (#1#): Implement HGUI::SetCurrentDesktop() */
    m_pCurrentDesktop=desktop;
}

// zwraca aktualny desktop
HGUIDesktop * HGUI::GetCurrentDesktop() {
    /* TODO (#1#): Implement HGUI::GetCurrentDesktop() */
    return m_pCurrentDesktop;
}

// wykonuje rendering aktualnego pulpitu
void HGUI::Render() {
    /* TODO (#1#): Implement HGUI::Render() */
    if (!m_bActive) return;
    if (m_pCurrentDesktop) {
        Begin2D();
        glActiveTexture(GL_TEXTURE0_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE1_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE2_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE3_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE4_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE5_ARB);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_1D);
        glActiveTexture(GL_TEXTURE0_ARB);
        glDepthMask(0);
        if (GUITextureID==-1) {
            GUITextureID=HTextureManager::GetSingleton().Load("GUI");
        }
        HTextureManager::GetSingleton().Bind(GUITextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glEnable(GL_TEXTURE_2D);
        HGUI::SetupColor(1,1,1);
        m_pCurrentDesktop->Render();
        m_Mouse.Render();
        End2D();
    }
    glDepthMask(1);
}

// rozpoczyna renderowanie w trypbie 2d
void HGUI::Begin2D() {
    /* DONE (#1#): Implement HGUI::Begin2D() */
    glPushAttrib( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT);
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0, HRendererWindow::GetSingleton().GetWidth(), HRendererWindow::GetSingleton().GetHeight(), 0 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    /*    if(m_fTransparency<1){*/
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*    } else {
        glDisable(GL_BLEND);
        }*/
}

// konczy renderowanie w trybie 2d
void HGUI::End2D() {
    /* DONE (#1#): Implement HGUI::End2D() */
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
}

// odbiera przesuni�ie myszy
void HGUI::MouseMove(int deltax, int deltay) {
    /* DONE (#1#): Implement HGUI::MouseMove() */
    if (!m_bActive) return;
    m_Mouse.CursorPos[0]+=deltax;
    m_Mouse.CursorPos[1]+=deltay;
}

// robi upejt GUI
void HGUI::Update() {
    /* TODO (#1#): Implement HGUI::Update() */
    if (!m_bActive) return;
    m_Mouse.Update();
    if (m_pCurrentDesktop) {
        m_pCurrentDesktop->Update();
    }
    if (m_fTransparency>1)m_fTransparency=1;
    if (m_fTransparency<0.2) m_fTransparency=0.2;
}

// ustawia kolor
void HGUI::SetupColor(float r, float g, float b) {
    /* TODO (#1#): Implement HGUI::SetupColor() */
    glColor4f(r,g,b,m_fTransparency);
}

// odbiera zdarzenie wcisni�ia klawisza
void HGUI::HandleKey(int key) {
    /* TODO (#1#): Implement HGUI::HandleKey() */
    if (!m_bActive) return;
    if (!m_pCurrentDesktop) return;
    m_pCurrentDesktop->HandleKey(key);

}

// odbiera wcini�ie klawisza myszy, narazie tylko lewego
void HGUI::MouseState(bool down) {
    /* TODO (#1#): Implement HGUI::MouseState() */
    if (!m_bActive) return;
    if (!m_pCurrentDesktop) return;
    if (down) {
        m_pCurrentDesktop->MouseDown(m_Mouse.CursorPos[0],m_Mouse.CursorPos[1]);
    } else {
        m_pCurrentDesktop->MouseUp(m_Mouse.CursorPos[0],m_Mouse.CursorPos[1]);
    }
}

// renderuje tekst jednoliniowy bez resetu macierzy
void HGUI::DrawText(int xpos, int ypos, int size, const char *str,...) {
    /* TODO (#1#): Implement HGUI::DrawText() */
    static char buffer[2048];
    int i, L, ascii;
    float cx, cy;
    float transcounter=0;


    // evaluate the string
    memset(buffer, '\0', 2048);
    va_list argptr;
    va_start( argptr, str );
    vsnprintf( buffer, 2048, str, argptr );
    va_end( argptr );


    L = strlen( buffer );
    if (m_iFont==-1) {
        m_iFont=HTextureManager::GetSingleton().Load("GUI_font");
    }
    // set our mode
    glPushAttrib( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT);
    glPushMatrix();
    glActiveTexture(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    HTextureManager::GetSingleton().Bind(m_iFont);
    glTranslatef( (float)xpos, (float)ypos, 0 );


    // we draw character per character
    for ( i=0; i<L; i++ ) {

        // FIXME : performance ?
        // lazy conversion
        ascii = (int)buffer[i];

        if ( buffer[i] == '^' && i+1<L ) {
            ascii = (int)buffer[i+1];
            glColor4f( (float)(ascii&4), (float)(ascii&2), (float)(ascii&1), 1.0f );
            i++;
            continue;
        } else {

            cx=float(ascii%16)/16.0f;
            cy=float(ascii/16)/16.0f;
            cy=cy+m_FontSet*0.5;
            if (ascii=='\n') {
                glTranslatef( -(float)size*0.9*transcounter, size, 0 );
                transcounter=0;
                continue;
            } else if (ascii!=' ') {
                glBegin( GL_TRIANGLE_FAN /*GL_QUADS*/ );


                glTexCoord2f( cx,cy );
                glVertex2i( 0,0 );


                glTexCoord2f( cx+0.0625f,cy );
                glVertex2i( size,0 );

                glTexCoord2f( cx+0.0625f,cy+0.0625f );
                glVertex2i( size,size );

                glTexCoord2f( cx,cy+0.0625f );
                glVertex2i( 0,size );

                glEnd();
            }
            transcounter+=1;
            glTranslatef( (float)size*0.9, 0, 0 );

        }

    }
    glPopMatrix();
    glPopAttrib();
}


// returns the value of m_FontSet
int HGUI::GetFontSet() {
    return m_FontSet;
}


// sets the value of m_FontSet
void HGUI::SetFontSet(int x) {
    if (x==0||x==1) m_FontSet = x;
}

