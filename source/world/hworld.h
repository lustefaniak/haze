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

#ifndef HWORLD_H
#define HWORLD_H

#include "../camera/hcamera.h"
#include "../geometry/hgbrush.h"
class HGBrush;

/*
 * wiat w kt�ym wszystko si�dzieje
 */
class HWorld {
public:
    // class constructor
    HWorld();
    // class destructor
    virtual ~HWorld();
    // wczytuje stan wiata i takie tam
    int Load(string geometry, string savegame="");
    List<HGBrush*> m_Brushes;
    List<HGBrush*> m_WorldBrushes;
    HBSP m_BSP;
    List<vec3_t> m_LightPoints;
    List<vec3_t> m_LightPointsColors;
    // tworzy nowy brush w wiecie
    HGBrush * CreateBrush();
    HLightSystem m_LightSystem;
    // wykonuje update swiata
    virtual void Update();
    // renderuje z widoku tej kamery
    void Render(HCamera * cam);
    // generuje takie co
    int GenerateNormalizationCubeMap();
    unsigned int m_uiNormalizationCubeMap;
};

#endif // HWORLD_H

