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

#include "Haze.h"
#include "Haze_private.h"
#include "core/henginecore.h"
#include "core/errors.h"
#include "core/hparser.h"
#include "world/hworldfromqmap.h"

bool ConfigGenerateLightmaps=true;

#ifdef WIN32
int ParamSpecified ( const char* string, const char *extension ) {
    const char *start;
    char *where, *terminator;

    where = strchr ( extension, ' ' );
    if ( where || *extension == '\0' )
        return 0;


    start = string;
    for ( ;; ) {
        where = ( char * ) strstr ( start, extension );
        if ( !where )
            break;
        terminator = where + strlen ( extension );
        if ( where == start || * ( where - 1 ) == ' ' ) {
            if ( *terminator == ' ' || *terminator == '\0' ) {
                return 1;
            }
        }
        start = terminator;
    }
    return 0;
}



int WINAPI WinMain ( HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nFunsterStil )
#else
int main ( int iArgs, char szArgs[] )
#endif
{
    HEngineCore *E=NULL;
    try {
        if ( freopen ( "stdout.log","wt",stdout ) ==0 ) hlog ( "could not open stdout" );
        if ( freopen ( "stderr.log","wt",stderr ) ==0 ) hlog ( "could not open stderr" );

#if defined(WIN32)
        SDL_SetModuleHandle ( hThisInstance );
//TODO: ta opcja dla linuxa!
        if ( ParamSpecified ( lpszArgument,"-nolighting" ) ||ParamSpecified ( lpszArgument,"-nolightmaps" ) ) ConfigGenerateLightmaps=false;
#endif

#ifdef __MINGW32_VERSION
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING" (MinGW v.%1.2f Powered) ("CPUSTRING") "__DATE__"\n",__MINGW32_VERSION
#else
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING"("CPUSTRING") "__DATE__"\n"
#endif
        hlog ( HINFO );

        E=new HEngineCore();
        assert ( E );
        E->Init();
        E->Run();
        E->DeInit();
        delete E;

        return 0;
    } catch ( ... ) {
        if ( E ) {
            E->Exit();
            E->DeInit();
            delete E;
        }
        SDL_Quit();
        DisplayError();
        return -1;
    }
}
