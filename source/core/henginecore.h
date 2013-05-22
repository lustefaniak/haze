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

#ifndef HENGINECORE_H
#define HENGINECORE_H

//#include "../Haze.h"

class HInputSystem;
class HRendererWindow;
class HConsole;
class HTextureManager;
class HRenderer;
class HGameFPP;
class HScript;
class HObjectFactory;

/*
 * czy wszystkie badziewia
 */
class HEngineCore : public Singleton<HEngineCore> {
public:
    // class constructor
    HEngineCore();
    // class destructor
    ~HEngineCore();
    HTimer *m_pTimer;
    HInputSystem *m_pInputSystem;
    HRenderer *m_pRenderer;
    HRendererWindow *m_pRenderWindow;
    HConsole *m_pConsole;
    HTextureManager *m_pTextureManager;
    HMaterialManager *m_pMaterialManager;
    HLightmapGenerator *m_pLightmapGenerator;
    HObjectFactory * m_pObjectFactory;
    HFont *m_pFont;
    HGUI * m_pGUI;
    HGameFPP * m_pGameFPP;
    // robi inicjalizacj�wszystkich rzeczy
    int Init();
    // zwalnia wszystko
    int DeInit();
    // p�la engine'u
    int Run();
    // wywouje procedur�ko�zenia dziaania enginu
    void Exit();
    // zwalnia kamer�
    int PopCamera();
    // ustawia kamer�
    int PushCamera(HCamera *);
    HCamera * m_pCamera;
    // ustawia tytu ekranu ze stanem adowania
    int SetLoadingScreenTitle(string title);
    // wyietla ekran adowania z danym procentem
    int LoadingScreenUpdate(float percent);
protected:
//      HGame * m_pGame;
    HCamera * m_pDefaultCamera;
    bool m_bLoop;
    string LoadingScreenTile;
    int m_iLoadingSlider;
    int m_iLoadingBackground;

};

#endif // HENGINECORE_H

