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

#ifndef HCCOMMAND_H
#define HCCOMMAND_H

//class HCCommand;

#include "hcparams.h"

/*
 * przechowuje funkcje wywoywane z konsoli
 */
class HCCommand {
public:
    // class constructor
    typedef void (*tCCallback)(HCCommand *, HCParams *);
    HCCommand(string name,tCCallback callback);
    // class destructor
    ~HCCommand();
    // wykonuje fragment kodu z konsoli
    virtual int Execute(string args);
    string GetName(); // returns the value of m_sName
private:
    // przechowuje nazw�funkcji
    string m_sName;
};

#endif // HCCOMMAND_H

