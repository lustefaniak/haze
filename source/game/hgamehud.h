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

#ifndef HGAMEHUD_H
#define HGAMEHUD_H

/*
 * to co widzi gracz grajc
 */
class HGameHUD {
public:
    // class constructor
    HGameHUD();
    // class destructor
    ~HGameHUD();
    // inicjalizuje HUD
    int Init();
    // zwalnia zasoby
    int DeInit();
    // renderuje HUD
    void Render();
    vec3_t m_vLastCamDir;
    vec3_t m_vHudColor;
    float m_fHudAlpha;
    float m_fCrosshairRadius;
    int m_tCrosshair1;
    int m_tCrosshair2;
    float m_fCrosshairRadiusGrow;
    int m_iCrosshairStyle;
    char m_cCrosshairMoveDirection;
    // ustawia aktualny styl celownika
    bool SetCrosshairStyle(int style);
};

#endif // HGAMEHUD_H

