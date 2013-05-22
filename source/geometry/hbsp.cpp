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
#include "hbsp.h" // class's header file

// class constructor
HBSP::HBSP() {
    // insert your code here
    m_WaitingPolys=NULL;
    RootNode=NULL;
}

// class destructor
HBSP::~HBSP() {
    // insert your code here
}

// dodaje poly do listy poly dla budowania drzewa
int HBSP::AddPoly(HGPoly * poly) {
    /* TODO (#1#): Implement HBSP::AddPoly() */
    if (m_WaitingPolys!=NULL) {
        m_WaitingPolys->BSP_Prev=poly;
    }
    poly->BSP_Next=m_WaitingPolys;
    m_WaitingPolys=poly;
}

// buduje drzewo
int HBSP::Build() {
    /* TODO (#1#): Implement HBSP::Build() */
//  RootNode=new HBSPNode;



}

// wybiera najlepszy poly do ci�ia drzewa
HGPoly * HBSP::ChooseSplitter(HGPoly * polylist, HGBBox * box) {
    /* TODO (#1#): Implement HBSP::ChooseSplitter() */
    HGPoly *Cur1,*Cur2,*BestSurf;              // Liczniki p�li oraz najepszy splitter
    float fBestDiv,fValue,fDist;                 // Najlepszy podzia, aktualny podzia, odlego�od paszczyzny
    int iSplits,iAxis,iBest;                     // Ilo�split�, g�na o paszczyzny, najlepszy wynik
    iBest = 1000000;
    fBestDiv = 10000000.0f;
    BestSurf = NULL;
    HGPlane * Plane;
    HGPoly * Poly;

    // Sprawd wszystkie paszczyzny. Kt�a z nich moe by�najlepszym splitterem
    for (Cur1=polylist;Cur1;Cur1=Cur1->BSP_Next) {
        // Jeeli ciana bya ju splitterem, pomi�ja.
//  if (Cur1->bWasSplitter) continue;

        // Pobierz paszczyzn�ciany
        Plane = Cur1->p;

        // Narazie jeszcze ciana nic nie poci�
        iSplits = 0;

        // Przejd wszystkie inne paszczyzny
        for (Cur2=polylist;Cur2;Cur2=Cur2->BSP_Next) {
            // Opr�z tej kt� aktualnie sprawdzamy
            if (Cur1 == Cur2) continue;

            // Pomi�take te, kt�e byy ju splitterami
//   if (Cur2->bWasSplitter) continue;

            // Zlicz ciany, kt�e zostaly przeci�e przez paszczynze (Cur1 - tesowany splitter)
            for (Poly=polylist;Poly;Poly=Poly->BSP_Next) {
                // Sprawd, po kt�ej stronie paszczynzy ley ciana
                int iSide = Poly->PlaneSide(Plane);

                // Jeeli paszczyzna j przecina, zapamietaj to.
                if ((iSide==SIDE_SPLIT)) {
                    iSplits++;

                    // Jeeli przekroczylimy aktualnie najlepsz warto�nie ma sensu sprawdza�dalej
                    if (iSplits >= iBest) break;
                }
            }

            // Jeeli przekroczylimy aktualnie najlepsz warto�nie ma sensu sprawdza�dalej
            if (iSplits > iBest) break;
        }

        // Jeeli przekroczylimy najlepsz warto�dalsze sprawdzanie nie ma sensu
        if (iSplits > iBest) continue;

        // Jeeli aktualnie badana ciana ma lepszy winik od aktualnie uwaanej za najlepsza
        // lub jeeli ma taki sam wynik, ale ley na g�nych osiach (wtedy moe mie�lepszy podzia).
        if ((iSplits < iBest) || ((iSplits == iBest) && (Plane->iType < PLANE_ANYX))) {
            // Paszczyzna ley na g�nych osiach
            if (Plane->iType<PLANE_ANYX) {
                // G�na o paszczyzny
                iAxis = Plane->iType;

                // Policz stosunek podziau
                fValue = 0;
                for (int j=0;j<3;j++) {
                    if (j == iAxis) {
                        fDist = Plane->d * Plane->n[iAxis];
                        fValue += (box->max[iAxis] - fDist) * (box->max[iAxis] - fDist);
                        fValue += (fDist - box->min[iAxis]) * (fDist - box->min[iAxis]);
                    } else {
                        fValue += 2 * (box->max[j] - box->min[j]) * (box->max[j] - box->min[j]);
                    }
                }

                // Jeeli jest lepszy gorszy pomi�
                if ((fValue > fBestDiv) && (iSplits == iBest)) continue;

                // Zapisz
                fBestDiv = fValue;
            }

            // Zapisz najlepszy wynik
            iBest = iSplits;

            // Zapisz najlepsz ciane
            BestSurf = Cur1;
        }
    }

// Zwr� najlepsz cian�
    return BestSurf;

}

// przygotowuje wszystko do renderowania
//void HBSP::Prepare(HCamera * cam)
//{
/* TODO (#1#): Implement HBSP::Prepare() */
//}

// renderuje drzewo bsp
void HBSP::Render() {
    /* TODO (#1#): Implement HBSP::Render() */
}

