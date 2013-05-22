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

#include "hlog.h" // class's header file

// class constructor
HLog::HLog(string filename) {
    // insert your code here
}

// class destructor
HLog::~HLog() {
    // insert your code here
}


void hlog(char * str,...) {

    char buffer[2048*2]={0};
    int i;

    va_list argptr;
    va_start( argptr, str );
    vsprintf( buffer, str, argptr );
    va_end( argptr );
    printf(buffer);
    if (gHConsole) {
        gHConsole->AddLine(buffer);
    }

}
