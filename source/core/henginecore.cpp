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


//#include "henginecore.h" // class's header file
#include "../Haze.h"
#include "../Haze_private.h"
template<> HEngineCore* Singleton<HEngineCore>::ms_Singleton = 0;

#ifdef __MINGW32_VERSION
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING" (MinGW v.%1.2f Powered) ("CPUSTRING") "__DATE__"\n",__MINGW32_VERSION
#else
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING"("CPUSTRING") "__DATE__"\n"
#endif

// class constructor
HEngineCore::HEngineCore() {
//  m_pGame=game;
    m_pTimer=new HTimer;
    assert ( m_pTimer );
    m_pInputSystem=new HInputSystem;
    assert ( m_pInputSystem );
    m_pRenderWindow=new HRendererWindow;
    assert ( m_pRenderWindow );
    m_pTextureManager=new HTextureManager;
    assert ( m_pTextureManager );
    m_pRenderer=new HRenderer;
    assert ( m_pRenderer );
//  m_pTextureManager=new HTextureManager;
    m_pMaterialManager=new HMaterialManager;
    assert ( m_pMaterialManager );
    m_pConsole=new HConsole;
    assert ( m_pConsole );
    m_pLightmapGenerator=new HLightmapGenerator;
    assert ( m_pLightmapGenerator );
    m_pDefaultCamera=new HCamera;
    assert ( m_pDefaultCamera );
    m_pFont=new HFont ( "font" );
    assert ( m_pFont );
    m_pCamera=m_pDefaultCamera;
    m_pGUI=new HGUI;
    assert ( m_pGUI );
    m_pGameFPP=new HGameFPP;
    m_pObjectFactory=new HObjectFactory;
    assert ( m_pGameFPP );
    m_iLoadingBackground=0;
    m_iLoadingSlider=0;
    m_bLoop=false;
    hlog ( "-HEngineCore object created...\n" );
}

// class destructor
HEngineCore::~HEngineCore() {
    delete m_pConsole;
    delete m_pFont;
    delete m_pInputSystem;
    delete m_pRenderWindow;
    delete m_pRenderer;
    delete m_pMaterialManager;
    delete m_pTextureManager;
    delete m_pLightmapGenerator;
    delete m_pCamera;
    delete m_pGUI;
    delete m_pObjectFactory;
    delete m_pGameFPP;
    hlog ( "-HEngineCore engine was running for %.2fs\n", ( m_pTimer->m_uiThisFrameTime-m_pTimer->m_uiStartTime ) /1000 );
    delete m_pTimer;
    hlog ( "-HEngineCore object destroyed...\n" );
}

int CameraReset() {
    HEngineCore::GetSingleton().m_pCamera->m_fYaw=0;
    HEngineCore::GetSingleton().m_pCamera->m_fPitch=0;
    HEngineCore::GetSingleton().m_pCamera->m_fRoll=0;
//HEngineCore::GetSingleton().m_pCamera->m_vPosition.Set(0);
}

int IncAlpha() {
    HGUI::GetSingleton().m_fTransparency+=0.05;
}
int DecAlpha() {
    HGUI::GetSingleton().m_fTransparency-=0.05;
}

// robi inicjalizacj�wszystkich rzeczy
int HEngineCore::Init() {
    /* TODO (#1#): Implement HEngineCore::Init() */
    hlog ( "-HEngineCore::Init()...\n" );
//  m_pRenderWindow->Open(1024,768,32,RW_FULLSCREEN);
    m_pRenderWindow->Open ( 800,600,32,0 );
    assert(m_pRenderer->InitShaders());
    SetLoadingScreenTitle ( "Initializing Engine" );
    LoadingScreenUpdate ( 0 );
    m_pConsole->Init();
    LoadingScreenUpdate ( 0.5f );
    m_pGameFPP->Init();
    LoadingScreenUpdate ( 1 );
    hlog ( "-HEngineCore::Init() done...\n" );
    static HGUIDesktop * desk;
    static HGUIButton * butt;
    static HGUIPanel * panel;
    static HGUIWindow * win=NULL;
    desk = m_pGUI->CreateDesktop(true);
    assert(desk);
    butt=desk->NewButton(90,20,5,20);
    butt->m_sCaption="Haze";
    butt->m_pFuncOnClick=CameraReset;
    panel=desk->NewPanel(160,HRendererWindow::GetSingleton().GetHeight(),HRendererWindow::GetSingleton().GetWidth()-160,0);
    butt=panel->NewButton(120,20,20,20);
    butt->m_pFuncOnClick=CameraReset;
    butt->m_sCaption="Cam reset";
    win=desk->NewWindow(320,200,70,50);
    win->m_sCaption="MainWindow 1";
    win=desk->NewWindow(320,200,90,20);
    win->m_sCaption="MainWindow 2";
    win->m_bCanClose=false;

    butt=win->NewButton(70,20,5,5);
    butt->m_pFuncOnClick=IncAlpha;
    butt->m_sCaption="+";
    butt=win->NewButton(70,20,5,27);
    butt->m_pFuncOnClick=DecAlpha;
    butt->m_sCaption="-";
    win->NewPanel(50,20,90,0);
    win->NewPanel(150,20,30,70);

//  m_pGame->Init();

}

// zwalnia wszystko
int HEngineCore::DeInit() {
    /* TODO (#1#): Implement HEngineCore::DeInit() */
//  m_pGame->DeInit();
    hlog ( "-HEngineCore::DeInit()...\n" );
//  SetLoadingScreenTitle("DeInitializing Engine");
//  LoadingScreenUpdate(0);
    m_pConsole->DeInit();
//  LoadingScreenUpdate(0.5f);
    m_pGameFPP->DeInit();
    m_pRenderWindow->Close();
    hlog ( "-HEngineCore::DeInit() done...\n" );
}

// p�la engine'u
int HEngineCore::Run() {
    guard ( HEngineCore::Run() );
    /* TODO (#1#): Implement HEngineCore::Run() */
    hlog ( "-HEngineCore::Run()...\n" );
    m_bLoop=true;
//int wait=0;
    hlog ( "-HEngineCore::Run() entering engine loop...\n" );
    while ( m_bLoop ) {
        m_pTimer->Update();
        m_pRenderWindow->Update();
        m_pInputSystem->Update();
        m_pGUI->Update();
        m_pConsole->Update();
        m_pGameFPP->Update();
        //glClear ( GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );//GL_COLOR_BUFFER_BIT|
        m_pGameFPP->Render();
        m_pFont->DrawText ( 1,1,10,HINFO );
        m_pFont->DrawText ( 5,HRendererWindow::GetSingleton().GetHeight()-25,26,"^\4FPS: %0.2f",m_pTimer->m_fFPS );
        m_pGUI->Render();
        m_pConsole->Draw();
        SDL_GL_SwapBuffers();
    }

    m_pRenderWindow->Close();
    m_bLoop=false;
    hlog ( "-HEngineCore::Run() done...\n" );
    return 0;
    unguard;
}

// wywouje procedur�ko�zenia dziaania enginu
void HEngineCore::Exit() {
    /* TODO (#1#): Implement HEngineCore::Exit() */
    hlog ( "-HEngineCore::Exit()...\n" );
    m_bLoop=false;
}

// ustawia kamer�
int HEngineCore::PushCamera ( HCamera * cam ) {
    /* TODO (#1#): Implement HEngineCore::PushCamera() */
    if ( cam==NULL ) return 0;
    m_pCamera=cam;
    return 1;
}

// zwalnia kamer�
int HEngineCore::PopCamera() {
    /* TODO (#1#): Implement HEngineCore::PopCamera() */
    m_pCamera=m_pDefaultCamera;
}

// ustawia tytu ekranu ze stanem adowania
int HEngineCore::SetLoadingScreenTitle ( string title ) {
    /* TODO (#1#): Implement HEngineCore::SetLoadingScreenTitle() */
    LoadingScreenTile=title;
}

// wyietla ekran adowania z danym procentem
int HEngineCore::LoadingScreenUpdate ( float percent ) {
    /* DONE (#1#): Implement HEngineCore::LoadingScreenUpdate() */
    glClear ( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );//GL_COLOR_BUFFER_BIT|
    glActiveTexture ( GL_TEXTURE0_ARB );
    glEnable ( GL_TEXTURE_2D );
    glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glEnable ( GL_BLEND );
    glColor4f ( 1,1,1,1 );
    glPushAttrib ( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT );
    glMatrixMode ( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D ( 0, HRendererWindow::GetSingleton().GetWidth(), HRendererWindow::GetSingleton().GetHeight(), 0 );
    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_LIGHTING );
    glDisable ( GL_CULL_FACE );
    glEnable ( GL_BLEND );
//    glBlendFunc( GL_ONE, GL_ONE ); // eleminate black src color
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    int leftpos;
    int rightpos;
    leftpos=HRendererWindow::GetSingleton().GetWidth() /2-256+30;
    rightpos= ( int ) ( leftpos+ ( 512-60 ) *percent );
    if ( m_iLoadingSlider==0 ) m_iLoadingSlider=HTextureManager::GetSingleton().Load ( "loading_slider" );


    HTextureManager::GetSingleton().Bind ( m_iLoadingSlider );// HTextureManager::GetSingleton().Load("loading_slider"));
    glBegin ( GL_TRIANGLE_FAN );


    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,0 );
    glVertex2i ( leftpos,HRendererWindow::GetSingleton().GetHeight() /2+4 );


    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,0 );
    glVertex2i ( rightpos,HRendererWindow::GetSingleton().GetHeight() /2+4 );

    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,1 );
    glVertex2i ( rightpos,HRendererWindow::GetSingleton().GetHeight() /2+40 );

    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,1 );
    glVertex2i ( leftpos,HRendererWindow::GetSingleton().GetHeight() /2+40 );

    glEnd();

    if ( m_iLoadingBackground==0 ) m_iLoadingBackground=HTextureManager::GetSingleton().Load ( "loading" );
    HTextureManager::GetSingleton().Bind ( m_iLoadingBackground );
    glBegin ( GL_TRIANGLE_FAN );


    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,0 );
    glVertex2i ( HRendererWindow::GetSingleton().GetWidth() /2-256,HRendererWindow::GetSingleton().GetHeight() /2-64 );


    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,0 );
    glVertex2i ( HRendererWindow::GetSingleton().GetWidth() /2+256,HRendererWindow::GetSingleton().GetHeight() /2-64 );

    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 1,1 );
    glVertex2i ( HRendererWindow::GetSingleton().GetWidth() /2+256,HRendererWindow::GetSingleton().GetHeight() /2+64 );

    glMultiTexCoord2f ( GL_TEXTURE0_ARB, 0,1 );
    glVertex2i ( HRendererWindow::GetSingleton().GetWidth() /2-256,HRendererWindow::GetSingleton().GetHeight() /2+64 );

    glEnd();



    glMatrixMode ( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode ( GL_MODELVIEW );
    glPopMatrix();
    glBindTexture ( GL_TEXTURE_2D, 0 );
    glPopAttrib();

    m_pFont->DrawText ( ( HRendererWindow::GetSingleton().GetWidth() /2 )- ( strlen ( LoadingScreenTile.c_str() ) *8 ) *0.9,HRendererWindow::GetSingleton().GetHeight() /2+60,16,LoadingScreenTile.c_str() );
    m_pFont->DrawText ( 0,0,14,HINFO );
    SDL_GL_SwapBuffers();
    HRendererWindow::GetSingleton().Update();

}

