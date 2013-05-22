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
#include "hparser.h" // class's header file

#define safecread() if (fread(&c,1,1,m_FP)!=1) {return 0;}// else {hlog("c:%s\n",c); }

// class constructor
HParser::HParser ( unsigned int buffersize ) {
    // insert your code here
    m_FP=NULL;
    m_iLastRead=0;
    m_iLastReadCount=0;
    m_BufferSize=buffersize;
    if ( m_BufferSize<=0 ) m_BufferSize=1;
    m_Buffer=new char[m_BufferSize+1];
    ClearBuffer();
    m_bStripComment=true;
}

// class destructor
HParser::~HParser() {
    // insert your code here
    if ( m_FP ) {
        fclose ( m_FP );
        m_FP=NULL;
    }
    delete[] m_Buffer;

}

unsigned long FileGetSize ( FILE *stream ) {
    unsigned long curpos, length;
    curpos = ftell ( stream );
    fseek ( stream, 0L, SEEK_END );
    length = ftell ( stream );
    fseek ( stream, curpos, SEEK_SET );
    return length;
}

// rozpoczyna parsowanie pliku
int HParser::StartParse ( string filename ) {
    /* TODO (#1#): Implement HParser::StartParse() */
    if ( m_FP ) {
        fclose ( m_FP );
        m_FP=NULL;
    }
    m_iLastRead=0;
//  m_iLastReadCount=0;
    ClearBuffer();

    m_sFilename=filename;
    m_FP=fopen ( filename.c_str(),"r" );
    if ( !m_FP ) return 0;
    rewind ( m_FP );
    if ( FileGetSize ( m_FP ) >0 ) return 1;
    else {
        fclose ( m_FP );
        m_FP=NULL;
        return 0;
    }

}

// czyci bufor
void HParser::ClearBuffer() {
    /* DONE (#1#): Implement HParser::ClearBuffer() */
//  debug("Clearing buffer...\n");
    assert ( m_Buffer );
    memset ( m_Buffer,0,m_BufferSize+1 );
}

// parsuje plik w poszukiwaniu token� (czego pomiedzy "biaymi" znakami)
int HParser::GetToken ( unsigned int limit ) {
    /* TODO (#1#): Implement HParser::GetToken() */
    if ( !m_FP ) return -2;
    char c[2];
    c[0]=0;
    c[1]=0;
    unsigned int readlimit=limit;
    if ( readlimit==0||readlimit>m_BufferSize ) readlimit=m_BufferSize;
    int read=0;
    ClearBuffer();
    Strip();
    StripWhite();
    while ( read<readlimit ) {
        safecread();
        if ( c[0]==' '||c[0]=='\t'||c[0]=='\n'||c[0]=='\r' ) {
            FileRewind ( 1 );
            read++;
            break;
        }
        m_Buffer[read]=c[0];
        read++;
    }
    m_iLastReadCount=read;
    return read;

}

// zmiena rozmiar buforu
void HParser::ResizeBuffer ( unsigned int nsize ) {
    /* TODO (#1#): Implement HParser::ResizeBuffer() */
    if ( nsize==m_BufferSize ) return;
//  debug("Resizing buffer...\n");
    delete[] m_Buffer;
    m_Buffer=NULL;
    m_BufferSize=nsize;
    m_Buffer=new char[m_BufferSize+1];
    assert ( m_Buffer );
}

// czyta a natrafi na znak ko�a linii lub przekroczy bufor
int HParser::GetLine() {
    /* TODO (#1#): Implement HParser::GetLine() */
    if ( !m_FP ) return -2;
    char c[2];
    c[0]=0;
    c[1]=0;
    /*  unsigned int readlimit=limit;
        if(readlimit==0||readlimit>m_BufferSize)readlimit=m_BufferSize;*/
    int read=0;
    ClearBuffer();
//  Strip();
    while ( read<m_BufferSize ) {
        safecread();
        if ( c[0]=='\n'||c[0]=='/' ) {
            safecread();
            if ( c[0]=='/' ) {//komentarz
                while ( true ) {
                    safecread();
                    if ( c[0]=='\n' ) {
                        safecread();
//  FileRewind(1);
                        c[0]=0;
                        break;
                    }
                }

                FileRewind ( 2 );
                read++;
                break;
            }//komentarz

//  c[0]=0;
            FileRewind ( 1 );
            read++;
            break;
        }

        m_Buffer[read]=c[0];
        read++;
    }
    m_iLastReadCount=read;
    return read;
}

// odczytuje jeden znak
char HParser::GetChar() {
    /* TODO (#1#): Implement HParser::GetChar() */
    if ( !m_FP ) return 0;
    char c[2];
    c[0]=0;
    c[1]=0;
    if ( fread ( &c,1,1,m_FP ) !=1 ) return 0;
    return c[0];

}

// cofa wskanik do pliku o ile
int HParser::FileRewind ( int size ) {
    /* TODO (#1#): Implement HParser::Rewind() */
    if ( !m_FP ) return -2;
    if ( size==0 ) return 0;
    if ( size<0 ) size=-size;
//  debug("Rewinding %d...\n",size);
    return fseek ( m_FP, -size, SEEK_CUR );
}

// przesuwa wskanik poza komentarze (tylko // #)
int HParser::StripComment() {
    /* TODO (#1#): Implement HParser::StripComment() */
    if ( !m_FP ) return -2;
    if ( !m_bStripComment ) return 0;
//  debug("Stripping comments...\n");
    int count=0;
    char c[2];
    c[0]=0;
    c[1]=0;
    StripWhite();
    safecread();
    if ( c[0]=='/' ) {
        safecread();
        if ( c[0]=='/' ) {
//debug("-// Comment Begin---\n");
            while ( c[0]!='\n'&&c[0]!='\r' ) {
                safecread();
                count++;
//if (c[0]>=32) debug("%s",&c[0]);
            }
//debug("\n-// Comment End---\n");
            FileRewind ( 1 );
            return count+StripComment();
        }
        FileRewind ( 1 );
    }
    if ( c[0]=='#' ) {
        safecread();
//debug("-# Comment Begin---\n");
        while ( c[0]!='\n'&&c[0]!='\r' ) {
            safecread();
            count++;
//if (c[0]>=32) debug("%s",&c[0]);
        }
//debug("\n-# Comment End---\n");
        FileRewind ( 1 );
        return count+StripComment();
    }

    FileRewind ( 1 );
    return count;

}

// przesuwa wskanik pliku do nast�nego nie_biaego_znaku
int HParser::StripWhite() {
    /* TODO (#1#): Implement HParser::StripWhite() */
    if ( !m_FP ) return -2;
//debug("Striping white_chars...\n");
    int count=0;
    char c[2];
    c[0]=0;
    c[1]=0;
    safecread();
    while ( c[0]==' '||c[0]=='\t'||c[0]=='\n'||c[0]=='\r' ) {
        safecread();
        /*if (c[0]=='\r') debug("-Whitespace-[\\r]-\n");
        else if (c[0]=='\n') debug("-Whitespace-[\\n]-\n");
        else debug("-Whitespace-[%s]-\n",c);*/
        count++;
//return count+StripWhite();
    }

    FileRewind ( 1 );
    return count;

}

// przewija plik do tyu o ilo�danych z ostatniego czytania do bufora
int HParser::RewindLast() {
    /* TODO (#1#): Implement HParser::RewindLast() */
    if ( !m_FP ) return -2;

    if ( m_iLastReadCount!=0 ) {
        FileRewind ( m_iLastReadCount );
        m_iLastReadCount=0;
    }

}

// zwraca wskanik do bufora
const char* HParser::GetBuffer() {
    /* DONE (#1#): Implement HParser::GetBuffer() */
    return m_Buffer;
}

// wywouje strip white i strip comment jak jest true w opcjach
int HParser::Strip() {
    /* TODO (#1#): Implement HParser::Strip() */
    StripWhite();
    if ( m_bStripComment ) StripComment();
}

// odczytuje tekst z " "
int HParser::GetString() {
    /* TODO (#1#): Implement HParser::GetString() */
    int found;
    char c[2];
    c[0]=0;
    c[1]=0;
    found=0;
    ClearBuffer();
    StripComment();
    StripWhite();
    safecread();
    if ( c[0]!='"' ) {
        FileRewind ( 1 );
        return 0;
    }
    while ( found<m_BufferSize ) {
        safecread();
        if ( c[0]=='"' ) {
//fseek( fp, -1, SEEK_CUR );
            break;
        }
        m_Buffer[found]=c[0];
        found++;
    }
#ifdef _DEBUG
    debug ( "-String-[%s]-\n",buff );
#endif
    m_iLastReadCount=found+2;
    return found;
}

