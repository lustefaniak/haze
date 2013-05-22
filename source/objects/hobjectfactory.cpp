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
#include "hobjectfactory.h" // class's header file

ObjectCreator *ObjectCreator::first = NULL;

HObjectFactory * gHObjectFactory=NULL;

ObjectCreator::ObjectCreator(string Name, ObjectCreateProc sfunc) {
    name=Name;
    next = first;
    first = this;
    proc = sfunc;
}


// class constructor
HObjectFactory::HObjectFactory() {
    // insert your code here
    if (gHObjectFactory==NULL) {
        gHObjectFactory=this;
    }
}

// class destructor
HObjectFactory::~HObjectFactory() {
    // insert your code here
    if (gHObjectFactory==this) {
        gHObjectFactory=NULL;
    }
}

// alokuje jakis obiekt i dodaje go do wiata
HObject * HObjectFactory::CreateObject(string name, HLevel * level) {
    /* TODO (#1#): Implement HObjectFactory::CreateObject() */
    hlog("Creating object of type \"%s\"\n",name.c_str());
    for (ObjectCreator *walk = ObjectCreator::first; walk; walk = walk->next) {
        if ((walk->name == name) && (walk->proc)) {
            // Register global Function
            hlog("Object found... Calling constructor...\n");
            return walk->proc(level);
        }
    }


    hlog("Can't create object!!!\n");
    return NULL;
}

