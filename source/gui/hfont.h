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

#ifndef HFONT_H
#define HFONT_H

/*
 * suzy do pisania na ekranie
 */
class HFont {
public:
    // class constructor
    HFont(string filename);
    // class destructor
    ~HFont();
    // renderuje trkst na ekranie
    void DrawText(int x, int y, int size, const char *str,...);
    int firstset;
protected:
    unsigned int fontsavestate;
    unsigned int fontrestorestate;
    int texture;
    bool needinit;
    string fontname;


};

#endif // HFONT_H

