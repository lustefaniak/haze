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

#ifndef HBSP_H
#define HBSP_H

class HGPlane;

struct HBSPNode {
    HBSPNode() {
        FirstPoly=NULL;

    }

    HGPlane *Plane;

    bool bIsLeaf;
    bool bIsSolid;

    HGPoly *FirstPoly;
    int iNumPolys;
    HGBBox BBox;

    int iVisFrame;

    HBSPNode *FrontChild,*BackChild;
    HBSPNode *Parent;
    void AddFace(HGPoly * poly) {

    }
};


/*
 * przechowuje drzewo bsp i je generuje
 */
class HBSP {
public:
    // class constructor
    HBSP();
    // class destructor
    ~HBSP();
    // dodaje poly do listy poly dla budowania drzewa
    int AddPoly(HGPoly *);
    // buduje drzewo
    int Build();
    // wybiera najlepszy poly do ci�ia drzewa
    HGPoly * ChooseSplitter(HGPoly * polylist, HGBBox * box);
    HGPoly * m_WaitingPolys;
    HBSPNode * RootNode;
    // przygotowuje wszystko do renderowania
//      void Prepare(HCamera * cam);
    // renderuje drzewo bsp
    void Render();
};

#endif // HBSP_H

