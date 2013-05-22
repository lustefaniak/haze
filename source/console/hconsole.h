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

#ifndef HCONSOLE_H
#define HCONSOLE_H

#include "../Haze.h"

#define CONBUFFSIZE 128
#define CONLINES 100
#define CONHISTORY 10

/*
 * konsola, nic doda�nic uj�
 */
class HConsole : public Singleton<HConsole> {
public:
    // class constructor
    HConsole();
    // class destructor
    ~HConsole();
    // uwalnia zasoby
    int DeInit();
    // inicjuje konsol�
    int Init();
    // renderuje konsol�
    void Draw();
    // robi updejt konsoli
    void Update();
    // odbiera zdarzenia
    int HandleKey(int key);
//  private:
    // przechowuje tekstur�ta
    int m_iBackground;
    // czy konsola jest widoczna czy nie
    bool m_bOpen;
    float m_fHeight;
    // Wiersz polece�
    char m_szBuffer[CONBUFFSIZE+1];
    int m_iBuferLenght;
    int m_iNumLines;
    char m_Lines[CONLINES][CONBUFFSIZE+1];
    char m_History[CONHISTORY][CONBUFFSIZE+1];
    int m_iHistoryPos;
    // pozycja na kt�ej znajduje si�kursor
    int m_iCursorPos;
    // dodaje lini�do listy linii w konsoli
    void AddLine(char*);
    // dodaje chara do bufora edycji
    void AddToBuff(char c);
    // parsuje zawarto�konsoli
    void Execute();
    // dodaje lini�z formatowaniem
    void AddLineF(char* str,...);
};

extern HConsole * gHConsole;

#endif // HCONSOLE_H

