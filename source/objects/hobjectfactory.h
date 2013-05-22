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

#ifndef HOBJECTFACTORY_H
#define HOBJECTFACTORY_H

class HLevel;
class HObject;

typedef HObject * (*ObjectCreateProc)(HLevel*);

struct ObjectCreator {
    string name;
    ObjectCreator *next;
    static ObjectCreator *first;
    ObjectCreateProc proc;
    ObjectCreator(string name, ObjectCreateProc);
};

#define RegisterObject(name,class) \
   static HObject * c##name(HLevel * level) { hlog("Creating object "#name" ("#class")\n"); return new class(level); }; \
   static ObjectCreator g##name##struct(#name, c##name);\

/*
* zajmuje si�tworzeniem instancji objekt�
*/
class HObjectFactory {
public:
    // class constructor
    HObjectFactory();
    // class destructor
    ~HObjectFactory();
    // alokuje jakis obiekt i dodaje go do wiata
    HObject * CreateObject(string name, HLevel * level);
};

extern HObjectFactory * gHObjectFactory;

#endif // HOBJECTFACTORY_H

