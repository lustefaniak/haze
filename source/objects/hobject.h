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

#ifndef HOBJECT_H
#define HOBJECT_H

class HLevel;

/*
 * taki sobie objekt kt�y reprezentuje jakie co na mapie
 */
class HObject {
public:
    // class constructor
    HObject(HLevel *);
    // class destructor
    virtual ~HObject();
    // renderuje objekt
    virtual void Render() { };
    // robi updejt objektu
    virtual void Update() { };
    vec3_t m_vOrigin;
    HLevel * m_pLevel;
    // dodaje poly do listy tego co ma w sobie
    virtual void AddGeometry(HGPoly * poly);
    List<HGPoly *> m_Polys;
};

#endif // HOBJECT_H

