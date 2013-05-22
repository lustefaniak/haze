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
#include "hfont.h" // class's header file

// class constructor
HFont::HFont ( string filename ) {
    // insert your code here
    fontname=filename;
    needinit=true;
    firstset=0;
}

// class destructor
HFont::~HFont() {
    if ( glIsList ( fontsavestate ) ) glDeleteLists ( fontsavestate, 1 );
    if ( glIsList ( fontrestorestate ) ) glDeleteLists ( fontrestorestate, 1 );

}

// renderuje trkst na ekranie
void HFont::DrawText ( int xpos, int ypos, int size, const char *str,... ) {
    /* TODO (#1#): Implement HFont::DrawText() */
    if ( needinit ) {
        fontsavestate = glGenLists ( 1 );
        fontrestorestate = glGenLists ( 1 );
        // use one to save state and change mode
        glNewList ( fontsavestate, GL_COMPILE );
        glPushAttrib ( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT );
        glMatrixMode ( GL_PROJECTION );
        glPushMatrix();
        glLoadIdentity();
//            debug("w %d h %d",HRendererWindow::GetSingleton().GetWidth(),HRendererWindow::GetSingleton().GetHeight());
        gluOrtho2D ( 0, HRendererWindow::GetSingleton().GetWidth(), HRendererWindow::GetSingleton().GetHeight(), 0 );
        glMatrixMode ( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();
        glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
        glDisable ( GL_DEPTH_TEST );
        glDisable ( GL_LIGHTING );
        glDisable ( GL_CULL_FACE );
        glEnable ( GL_BLEND );
        //glBlendFunc( GL_ONE, GL_DST_ALPHA );
//           glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//           glBlendFunc( GL_ONE, GL_ONE ); // eleminate black src color
        //glEnable( GL_TEXTURE_2D );
        //glBindTexture( GL_TEXTURE_2D, fonttexture );
        glEndList();


        // use other to restore saved mode
        glNewList ( fontrestorestate, GL_COMPILE );
        glMatrixMode ( GL_PROJECTION );
        glPopMatrix();
        glMatrixMode ( GL_MODELVIEW );
        glPopMatrix();
        glBindTexture ( GL_TEXTURE_2D, 0 );
        glPopAttrib();

        glEndList();

        texture=HTextureManager::GetSingleton().Load ( fontname );
        needinit=false;
    }

    static char buffer[2048];
    int i, L, ascii;
    float cx, cy;
    float transcounter=0;


    // evaluate the string
    memset ( buffer, '\0', 2048 );
    va_list argptr;
    va_start ( argptr, str );

    vsnprintf ( buffer, 2048, str, argptr );
    va_end ( argptr );


    L = strlen ( buffer );

    // set our mode
    glCallList ( fontsavestate );
    glActiveTexture ( GL_TEXTURE3_ARB );
    glDisable ( GL_TEXTURE_2D );
    glActiveTexture ( GL_TEXTURE2_ARB );
    glDisable ( GL_TEXTURE_2D );
    glActiveTexture ( GL_TEXTURE1_ARB );
    glDisable ( GL_TEXTURE_2D );
    glActiveTexture ( GL_TEXTURE0_ARB );
    glEnable ( GL_TEXTURE_2D );
    glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    HTextureManager::GetSingleton().Bind ( texture );
    glTranslatef ( ( float ) xpos, ( float ) ypos, 0 );


    // we draw character per character
    for ( i=0; i<L; i++ ) {

        // FIXME : performance ?
        // lazy conversion
        ascii = ( int ) buffer[i];

        if ( buffer[i] == '^' && i+1<L ) {
            ascii = ( int ) buffer[i+1];
            glColor4f ( ( float ) ( ascii&4 ), ( float ) ( ascii&2 ), ( float ) ( ascii&1 ), 1.0f );
            i++;
            continue;
        } else {

            cx=float ( ascii%16 ) /16.0f;
            cy=float ( ascii/16 ) /16.0f-0.5*firstset;
            if ( ascii=='\n' ) {
                glTranslatef ( - ( float ) size*0.9*transcounter, size, 0 );
                transcounter=0;
                continue;
            } else if ( ascii!=' ' ) {
                glBegin ( GL_TRIANGLE_FAN /*GL_QUADS*/ );


                glMultiTexCoord2f ( GL_TEXTURE0_ARB, cx,cy );
                glVertex2i ( 0,0 );


                glMultiTexCoord2f ( GL_TEXTURE0_ARB, cx+0.0625f,cy );
                glVertex2i ( size,0 );

                glMultiTexCoord2f ( GL_TEXTURE0_ARB, cx+0.0625f,cy+0.0625f );
                glVertex2i ( size,size );

                glMultiTexCoord2f ( GL_TEXTURE0_ARB, cx,cy+0.0625f );
                glVertex2i ( 0,size );

                glEnd();
            }
            transcounter+=1;
            glTranslatef ( ( float ) size*0.9, 0, 0 );

        }

    }

    glCallList ( fontrestorestate );
}

