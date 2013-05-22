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
#include "hcvar.h" // class's header file

// class constructor
HCVar::HCVar(string name, tCCallback callback, int flags=0): HCCommand(name,callback) {
    // insert your code here
}

// class destructor
HCVar::~HCVar() {
    // insert your code here
}

// parsuje zmienn z konsoli
int HCVar::Execute(string args) {
    /* TODO (#1#): Implement HCVar::Execute() */
}


// returns the value of m_iFlags
int HCVar::GetFlags() {
    return m_iFlags;
}


// sets the value of m_iFlags
void HCVar::SetFlags(int x) {
    m_iFlags = x;
}

