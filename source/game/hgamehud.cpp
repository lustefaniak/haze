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

// class constructor
HGameHUD::HGameHUD() {
    // insert your code here
    m_vHudColor.Set ( 1,0,0 );
    m_fHudAlpha=0.9;
    m_fCrosshairRadius=0;
    m_fCrosshairRadiusGrow=0;
    m_iCrosshairStyle=2;
    m_cCrosshairMoveDirection=1;
}

// class destructor
HGameHUD::~HGameHUD() {
    // insert your code here
}

// inicjalizuje HUD
int HGameHUD::Init() {
    /* TODO (#1#): Implement HGameHUD::Init() */
    m_tCrosshair1=HTextureManager::GetSingleton().Load ( "crosshair1" );
    m_tCrosshair2=HTextureManager::GetSingleton().Load ( "crosshair2" );
    m_vLastCamDir=HEngineCore::GetSingleton().m_pCamera->GetDirection();
}

// zwalnia zasoby
int HGameHUD::DeInit() {
    /* TODO (#1#): Implement HGameHUD::DeInit() */
    HTextureManager::GetSingleton().UnLoad ( m_tCrosshair1 );
    HTextureManager::GetSingleton().UnLoad ( m_tCrosshair2 );
}

// renderuje HUD
void HGameHUD::Render() {
    /* TODO (#1#): Implement HGameHUD::Render() */
    glPushAttrib ( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT );
    glMatrixMode ( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
//    gluOrtho2D( 0, HRendererWindow::GetSingleton().GetWidth(), HRendererWindow::GetSingleton().GetHeight(), 0 );
    gluOrtho2D ( 0, 800, 600, 0 );
    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_LIGHTING );
    glDisable ( GL_CULL_FACE );
    static float screenwcenter=400;
    static float screenhcenter=300;
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    /*    glColor4f(m_vHudColor[0],m_vHudColor[1],m_vHudColor[2],m_fHudAlpha);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex2f(screenwcenter,screenhcenter);
        glEnd();
        glPointSize(1);*/
//    if(m_vLastCamDir.Dot(HEngineCore::GetSingleton().m_pCamera->GetDirection())){
    float dot=m_vLastCamDir.Dot ( HEngineCore::GetSingleton().m_pCamera->GetDirection() );
//    if(dot>0.8f) dot-=0.2f;
    m_fCrosshairRadiusGrow+= ( 10-10*dot ) *120;
//    } else {
    m_fCrosshairRadiusGrow-= ( HTimer::GetSingleton().GetDelta() /100 ) *4;
//    }
    if ( m_fCrosshairRadiusGrow>100 ) m_fCrosshairRadiusGrow=100;
    if ( m_fCrosshairRadiusGrow<0 ) {
        m_fCrosshairRadiusGrow=0;
    }
//    sprintf(HEngineCore::GetSingleton().m_pConsole->m_szBuffer,"m_fCrosshairRadiusGrow=%f, dot=%f",m_fCrosshairRadiusGrow,m_vLastCamDir.Dot(HEngineCore::GetSingleton().m_pCamera->GetDirection()));

    if ( m_fCrosshairRadius<60 ) {
        m_fCrosshairRadius+= ( HTimer::GetSingleton().GetDelta() /100 ) *m_fCrosshairRadiusGrow*10;
    }
    if ( m_fCrosshairRadius>60 ) m_fCrosshairRadius=60;
    if ( m_fCrosshairRadius>0 ) {
        m_fCrosshairRadius-= ( m_fCrosshairRadius/10 ) * ( HTimer::GetSingleton().GetDelta() /100 );
    }
    if ( m_fCrosshairRadius<1 ) {
        m_fCrosshairRadius=1;
//    m_cCrosshairMoveDirection=-m_cCrosshairMoveDirection;
    }
    switch ( m_iCrosshairStyle ) {

    case 1: {
        glActiveTextureARB ( GL_TEXTURE0_ARB );
        glEnable ( GL_TEXTURE_2D );
        glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        HTextureManager::GetSingleton().Bind ( m_tCrosshair1 );// HTextureManager::GetSingleton().Load("loading_slider"));
        glTranslatef ( screenwcenter,screenhcenter,0 );
        glRotatef ( 90+m_cCrosshairMoveDirection* ( 90*m_fCrosshairRadius/60 ),0,0,1 );
        glColor4f ( m_vHudColor[0],m_vHudColor[1],m_vHudColor[2],m_fHudAlpha-m_fHudAlpha*m_fCrosshairRadius/80 );
        for ( int i=0;i<4;i++ ) {
            glRotatef ( 90,0,0,1 );
            glBegin ( GL_QUADS );
            glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,0 );
            glVertex2f ( m_fCrosshairRadius,-8 );

            glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,0 );
            glVertex2f ( m_fCrosshairRadius+16,-8 );

            glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,1 );
            glVertex2f ( m_fCrosshairRadius+16,8 );

            glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,1 );
            glVertex2f ( m_fCrosshairRadius,8 );
            glEnd();

        }
    }
    break;
    case 2: {
        glActiveTextureARB ( GL_TEXTURE0_ARB );
        glEnable ( GL_TEXTURE_2D );
        glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        HTextureManager::GetSingleton().Bind ( m_tCrosshair2 );// HTextureManager::GetSingleton().Load("loading_slider"));
        glTranslatef ( screenwcenter,screenhcenter,0 );
//    glRotatef(90+m_cCrosshairMoveDirection*(90*m_fCrosshairRadius/60),0,0,1);
        glColor4f ( m_vHudColor[0],m_vHudColor[1],m_vHudColor[2],m_fHudAlpha-m_fHudAlpha*m_fCrosshairRadius/80 );
        glBegin ( GL_QUADS );
        glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,0 );
        glVertex2f ( -m_fCrosshairRadius-8,-m_fCrosshairRadius-8 );

        glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,0 );
        glVertex2f ( m_fCrosshairRadius+8,-m_fCrosshairRadius-8 );

        glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,1 );
        glVertex2f ( m_fCrosshairRadius+8,m_fCrosshairRadius+8 );

        glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,1 );
        glVertex2f ( -m_fCrosshairRadius-8,m_fCrosshairRadius+8 );
        glEnd();

    }
    break;


    }

    m_vLastCamDir=HEngineCore::GetSingleton().m_pCamera->GetDirection();


    glMatrixMode ( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode ( GL_MODELVIEW );
    glPopMatrix();
    glBindTexture ( GL_TEXTURE_2D, 0 );
    glPopAttrib();
}

// ustawia aktualny styl celownika
bool HGameHUD::SetCrosshairStyle ( int style ) {
    /* TODO (#1#): Implement HGameHUD::SetCrosshairStyle() */
    if ( style==1||style==2 ) {
        m_iCrosshairStyle=style;
        return true;
    }
    return false;
}

