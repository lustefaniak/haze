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
#include "hrendererwindow.h" // class's header file
#include "../input/hinputsystem.h"

template<> HRendererWindow* Singleton<HRendererWindow>::ms_Singleton = 0;

HRendererWindow * gHRendererWindow=NULL;

// class constructor
HRendererWindow::HRendererWindow() {
    // insert your code here
    guard ( HRendererWindow::HRendererWindow() );
    m_iOpened=false;
    if ( gHRendererWindow==NULL ) {
        gHRendererWindow=this;
    }
    unguard;
}

// class destructor
HRendererWindow::~HRendererWindow() {
    guard ( HRendererWindow::~HRendererWindow() );
    SDL_VideoQuit();
    if ( gHRendererWindow==this ) {
        gHRendererWindow=NULL;
    }
    unguard;
}

// otwiera okno renderujce
int HRendererWindow::Open ( int w, int h, int bpp, int flags ) {
    guard ( HRendererWindow::Open() );

    SDL_InitSubSystem ( SDL_INIT_VIDEO );
    SDL_WM_SetCaption ( "Haze",NULL );
    SDL_SetVideoMode ( w,h,bpp,SDL_OPENGL|SDL_DOUBLEBUF|SDL_HWPALETTE| ( ( flags&RW_FULLSCREEN ) ? SDL_FULLSCREEN : 0 ) );
    SDL_ShowCursor ( SDL_DISABLE );
    SDL_WarpMouse ( w / 2,h / 2 );
    SDL_WarpMouse ( w / 2,h / 2 );
    glewExperimental=1;
    GLenum err = glewInit();
    if ( GLEW_OK != err ) {
        /* Problem: glewInit failed, something is seriously wrong. */
        //error( "Error: %s\n", glewGetErrorString ( err ) );
        return false;
    }

    if ( !GLEW_ARB_multitexture ) error ( "GL_ARB_multitexture unsupported!!!" );
    if ( !GLEW_ARB_texture_env_combine ) error ( "GL_ARB_texture_env_combine unsuppoerted!!!" );
    if ( !GLEW_ARB_texture_env_dot3 ) error ( "GL_ARB_texture_env_dot3 unsuppoerted!!!" );
//if(!GL_ARB_vertex_program_Flag) error("GL_ARB_vertex_program unsupported!!!");


    glViewport ( 0, 0, w, h );                  // Reset The Current Viewport
    glMatrixMode ( GL_PROJECTION );                     // Select The Projection Matrix
    glLoadIdentity();                           // Reset The Projection Matrix
// Calculate The Aspect Ratio Of The Window
    gluPerspective ( 45.0f, ( GLfloat ) w/ ( GLfloat ) h,0.1f,20000.0f );

    glMatrixMode ( GL_MODELVIEW );                      // Select The Modelview Matrix
    glLoadIdentity();

    glShadeModel ( GL_SMOOTH );

    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear ( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
    SDL_GL_SwapBuffers();
    glClearDepth ( 1.0f );                          // Depth Buffer Setup
    glEnable ( GL_DEPTH_TEST );                     // Enables Depth Testing
    glDepthFunc ( GL_LEQUAL );                          // The Type Of Depth Test To Do

    glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );           // Really Nice Perspective Calculations
    glHint ( GL_LINE_SMOOTH_HINT, GL_NICEST );              // Use The Good Calculations
    glEnable ( GL_LINE_SMOOTH );
    glEnable ( GL_NORMALIZE );
    /* DONE (#1#): trzeba zreperowa�sortowanie wierzchok� */
    glEnable ( GL_CULL_FACE );
//glDisable (GL_CULL_FACE);
    glEnable ( GL_DEPTH_TEST ); // Hidden surface removal
    glFrontFace ( GL_CCW ); // Counter clock -wise polygons face out
//glEnable(GL_CULL_FACE); // Do not calculate inside of jet

    m_iWidth=w;
    m_iHeight=h;
    m_iBPP=bpp;

//SDL_SetGamma(1.5,1.5,1.5);
    m_iOpened=true;
    return 1;
    unguard;
}

// robi updejt
int HRendererWindow::Update() {
    guard ( HRendererWindow::Update() );
    if ( !m_iOpened ) return 0;
    /* DONE (#1#): Implement HRendererWindow::Update() */
    Uint8 state;
    SDL_Event event;
    while ( SDL_PollEvent ( &event ) ) {
        switch ( event.type ) {
            /*                case SDL_ACTIVEEVENT:
                            SDL_WarpMouse( m_iWidth/ 2,m_iHeight / 2);
                            SDL_WarpMouse( m_iWidth/ 2,m_iHeight / 2);
                            break;*/
        case SDL_QUIT:
            HEngineCore::GetSingleton().Exit();
            break;
        case SDL_MOUSEMOTION:
            int deltax, deltay;
            deltax=- ( event.button.x - m_iWidth / 2 );
            deltay=- ( event.button.y - m_iHeight / 2 );
            HInputSystem::GetSingleton().MouseMove ( deltax,deltay );//(event.button.button,event.button.state,event.button.x,event.button.y);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            HInputSystem::GetSingleton().HandleSDLEvent ( event );
            break;
        }
    }
    state=SDL_GetAppState();
    if ( state&SDL_APPINPUTFOCUS&&state&SDL_APPACTIVE ) SDL_WarpMouse ( m_iWidth/ 2,m_iHeight / 2 );


    return 1;
    unguard;
}


// returns the value of m_iWidth
int HRendererWindow::GetWidth() {
    return m_iWidth;
}


// returns the value of m_iHeight
int HRendererWindow::GetHeight() {
    return m_iHeight;
}


// returns the value of m_iBPP
int HRendererWindow::GetBPP() {
    return m_iBPP;
}


// returns the value of m_iOpened
bool HRendererWindow::IsOpened() {
    return m_iOpened;
}

// zamuka aktualnie otwarte okno
int HRendererWindow::Close() {
    /* DONE (#1#): Implement HRendererWindow::Close() */
//  if(!m_iOpened) return 0;
    SDL_VideoQuit();
    m_iOpened=false;
    return 1;
}


