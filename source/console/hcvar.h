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

#ifndef HCVAR_H
#define HCVAR_H

#include "hccommand.h" // inheriting class's header file

#define CV_READONLY (1<<1)

/*
 * klasa do obsugi zmiennych
 */
class HCVar : public HCCommand {
public:
    // class constructor
    HCVar(string name, tCCallback callback, int flags);
    // class destructor
    ~HCVar();
    // parsuje zmienn z konsoli
    int Execute(string args);
    void SetFlags(int x); // sets the value of m_iFlags
    int GetFlags(); // returns the value of m_iFlags
private:
    // flagi jakie ma zmienna
    int m_iFlags;
};

#endif // HCVAR_H

