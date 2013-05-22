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

#include "hconsole.h" // class's header file

#include "../Haze_private.h"
#ifdef __MINGW32_VERSION
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING" (MinGW v.%1.2f Powered) ("CPUSTRING") "__DATE__"\n",__MINGW32_VERSION
#else
#define HINFO PRODUCT_NAME" "VER_STRING" "BUILDSTRING"("CPUSTRING") "__DATE__"\n"
#endif

template<> HConsole* Singleton<HConsole>::ms_Singleton = 0;

HConsole * gHConsole=NULL;

// class constructor
HConsole::HConsole() {
    // insert your code here
    m_fHeight=0;
    m_iBackground=0;
    m_bOpen=false;
    m_iCursorPos=0;
    m_iNumLines=0;
    m_iBuferLenght=0;
    m_iHistoryPos=0;
    memset(m_szBuffer,0,CONBUFFSIZE+1);
    memset(m_Lines,0,CONLINES*(CONBUFFSIZE+1));
    if (gHConsole==NULL) {
        gHConsole=this;
    }
}

// class destructor
HConsole::~HConsole() {
    if (gHConsole==this) {
        gHConsole=NULL;
    }
}

// inicjuje konsol�
int HConsole::Init() {
    /* TODO (#1#): Implement HConsole::Init() */
    char buff[CONBUFFSIZE]={0};


    m_iBackground=HTextureManager::GetSingleton().Load("console");
//  memcpy(m_Lines[0],HINFO,strlen(HINFO));
//  m_iNumLines++;
    sprintf(buff,HINFO);
    AddLine("\35\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\37");
    sprintf(buff,HINFO);
    AddLine(buff);
    sprintf(buff,HINFO);
    AddLine("\35\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\37");
    AddLine(0);
    return 1;
}

// uwalnia zasoby
int HConsole::DeInit() {
    /* TODO (#1#): Implement HConsole::DeInit() */
    HTextureManager::GetSingleton().UnLoad(m_iBackground);
    return 1;
}

// robi updejt konsoli
void HConsole::Update() {
    /* TODO (#1#): Implement HConsole::Update() */
    float delta=HTimer::GetSingleton().GetDelta()*2/3;
    if (m_bOpen&&m_fHeight<600/2) {
        m_fHeight+=delta;
    }
    if (!m_bOpen&&m_fHeight>0) {
        m_fHeight-=delta;
    }
    if (m_fHeight>600/2) m_fHeight=600/2;
    if (m_fHeight<0) m_fHeight=0;
}

// renderuje konsol�
void HConsole::Draw() {
    /* TODO (#1#): Implement HConsole::Draw() */
    if (m_fHeight==0) return;
    glPushAttrib( GL_COLOR_BUFFER_BIT|GL_ENABLE_BIT|GL_TEXTURE_BIT);
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0, 800, 600, 0 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.8);
    HEngineCore::GetSingleton().m_pFont->firstset=1;
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    HTextureManager::GetSingleton().Bind(m_iBackground);// HTextureManager::GetSingleton().Load("loading_slider"));
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin( GL_TRIANGLE_FAN );


    glMultiTexCoord2f(GL_TEXTURE0_ARB, 0,0 );
    glVertex2i( 0,-300+m_fHeight);


    glMultiTexCoord2f(GL_TEXTURE0_ARB, 8,0 );
    glVertex2i( 800,-300+m_fHeight);

    glMultiTexCoord2f(GL_TEXTURE0_ARB, 8,3 );
    glVertex2i( 800,(int)m_fHeight);

    glMultiTexCoord2f(GL_TEXTURE0_ARB, 0,3 );
    glVertex2i( 0,(int)m_fHeight);

    glEnd();
    float pos;
    int i;
    int i2;
    char buff[CONBUFFSIZE+1];
    int numcharsonscreen=(int)(800/(12*0.9f)-1);
    float numlinesonscreen;
//        float linewidth=/(12*0.9);
    pos=m_fHeight-15;
    for (i=m_iNumLines;i>=0;i--) {
        numlinesonscreen=(strlen(m_Lines[i])*(12*0.9))/800;
        if (numlinesonscreen>1) {
            for (i2=ROUND(numlinesonscreen);i2>=0;i2--) {
                if (i2<ROUND(numlinesonscreen)) {
                    HEngineCore::GetSingleton().m_pFont->DrawText(800-12,(int)pos,12,"^2^");
                }
                memset(buff,0,CONBUFFSIZE+1);
                memcpy(buff,&m_Lines[i][numcharsonscreen*i2],numcharsonscreen);
                HEngineCore::GetSingleton().m_pFont->DrawText(/*i2==0?*/2/*:7*/,(int)pos,12,buff);
                pos-=12;
            }
            if (pos<-12) break;
            continue;
        }


        HEngineCore::GetSingleton().m_pFont->DrawText(2,(int)pos,12,m_Lines[i]);
        pos-=12;
        if (pos<-12) break;
    }

    numcharsonscreen=(int)(800/(14*0.9f)-5);
    HEngineCore::GetSingleton().m_pFont->DrawText(0,(int)m_fHeight-15,14,"^\4]");
    if (m_iCursorPos>=numcharsonscreen) {
        HEngineCore::GetSingleton().m_pFont->DrawText(22,(int)m_fHeight-15,14,m_szBuffer+(m_iCursorPos-numcharsonscreen));
        HEngineCore::GetSingleton().m_pFont->DrawText(11,(int)m_fHeight-15,16,"~");
        HEngineCore::GetSingleton().m_pFont->DrawText((int)(22+14*(numcharsonscreen)*0.9f),(int)m_fHeight-15,16,"_");
    } else {
        HEngineCore::GetSingleton().m_pFont->DrawText(12,(int)m_fHeight-15,14,m_szBuffer);
        HEngineCore::GetSingleton().m_pFont->DrawText((int)(12+14*m_iCursorPos*0.9f),(int)m_fHeight-15,16,"_");
    }


    glLineWidth(2);
    glColor4f(1,0,0,0.8);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
    glVertex2f(0,m_fHeight);
    glVertex2f( 800,m_fHeight);
    glEnd();
    glLineWidth(0);
    HEngineCore::GetSingleton().m_pFont->DrawText((int)(800-36*0.9f),(int)m_fHeight-8,8,"^2Haze");

    HEngineCore::GetSingleton().m_pFont->firstset=0;
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();


}

// odbiera zdarzenia
int HConsole::HandleKey( int key) {
    /* TODO (#1#): Implement HConsole::HandleKey() */
    if (key=='`'||key=='~') {
        m_bOpen=!m_bOpen;
        return 1;
    }


    if (key==SDLK_BACKSPACE) {
        if ( m_iCursorPos ) { // can we suppress safely?

            // suppress last character if cursor is at the last position
            if ( m_iCursorPos == m_iBuferLenght ) {
                m_iCursorPos--;
                m_iBuferLenght--;
                m_szBuffer[m_iCursorPos] = '\0';
            }
            // suppress previous character of current position
            else {
                for ( int j=m_iCursorPos-1; j<m_iBuferLenght-1; j++ ) {
                    m_szBuffer[j] = m_szBuffer[j+1]; // move chars to left
                }
                m_szBuffer[m_iBuferLenght-1] = '\0';
                m_iBuferLenght--;
                m_iCursorPos--;
            }
        }
    }
    if (key==SDLK_RETURN) {
        AddLine(m_szBuffer);
        m_iCursorPos=0;
        m_iBuferLenght=0;
        memset(m_szBuffer,0,CONBUFFSIZE+1);
        return 1;
    }
    if (key==SDLK_DELETE) {
        if ( m_iCursorPos<m_iBuferLenght ) {
            for (int j=m_iCursorPos; j<m_iBuferLenght-1; j++ ) {
                m_szBuffer[j] = m_szBuffer[j+1]; // move chars to left
            }
            m_szBuffer[m_iBuferLenght-1] = '\0';
            m_iBuferLenght--;
        }
        return 1;
    }
    if (key==SDLK_LEFT) {
        if ( m_iCursorPos ) m_iCursorPos--;
        return 1;
    }
    if (key==SDLK_RIGHT) {
        if ( m_iCursorPos<m_iBuferLenght ) m_iCursorPos++;
        return 1;
    }
    if (key==SDLK_HOME) {
        m_iCursorPos = 0;
        return 1;
    }
    if (key==SDLK_END) {
        m_iCursorPos = m_iBuferLenght;
        return 1;
    }

    AddToBuff(key);

    /*  if(key=='r'||key=='R') HTextureManager::GetSingleton().DumpReport();
        if(key=='l'||key=='L') {
        float start=HTimer::GetSingleton().GetCurrentTime();
        HEngineCore::GetSingleton().SetLoadingScreenTitle("I just like this loading screen!");
        HEngineCore::GetSingleton().LoadingScreenUpdate(0);
        while(HTimer::GetSingleton().GetCurrentTime()-start<1000){
        HEngineCore::GetSingleton().LoadingScreenUpdate((HTimer::GetSingleton().GetCurrentTime()-start)/1000);
        }
        HEngineCore::GetSingleton().LoadingScreenUpdate(1);
        }*/
//  printf("Console received \"%s\" key\n",SDL_GetKeyName((SDLKey)key));
}

// dodaje lini�do listy linii w konsoli
void HConsole::AddLine(char* text) {
    /* TODO (#1#): Implement HConsole::AddLine() */
    if (text==0)return;
    int i=0;
    for (i=0;i<strlen(text);i++) {
        if (text[i]=='\n') text[i]=0;
    }

    if ( m_iNumLines < CONLINES ) {

        /*    strncpy( &m_szBuffer[m_iNumLines], text, CONBUFFSIZE+1 );
            m_iNumLines++;*/
        strcpy(m_Lines[m_iNumLines],text);
        m_iNumLines++;
    } else {
        int i;

        // move down all previous lines
        for ( i=0; i<CONLINES-1 /*&& i<m_iNumLines*/; i++ ) {

            memset(&m_szBuffer[i],0,CONBUFFSIZE+1);
            strcpy( &m_szBuffer[i], &m_szBuffer[i+1]);
        }
        memset(&m_szBuffer[m_iNumLines],0,CONBUFFSIZE+1);
        strcpy( &m_szBuffer[m_iNumLines], text );
    }



    /*  if(m_iNumLines<=CONLINES){
        strcpy(m_Lines[m_iNumLines],text);
        m_iNumLines++;
        } else {


        }*/
}

// dodaje chara do bufora edycji
void HConsole::AddToBuff(char c) {
    /* TODO (#1#): Implement HConsole::AddToBuff() */
    if ( m_iCursorPos < CONBUFFSIZE-1 && isprint(c)) {

        if ( m_iBuferLenght == m_iCursorPos ) {
            m_szBuffer[m_iCursorPos] = c;
            m_iCursorPos++;
            m_iBuferLenght++;
        } else { // we are inserting

            int i;
            for ( i=m_iBuferLenght; i>m_iCursorPos; i-- ) {

                m_szBuffer[i] = m_szBuffer[i-1];
            }
            m_szBuffer[i] = c;
            m_iCursorPos++;
            m_iBuferLenght++;
        }

    }

}

// parsuje zawarto�konsoli
void HConsole::Execute() {
    /* TODO (#1#): Implement HConsole::Execute() */
}

// dodaje lini�z formatowaniem
void HConsole::AddLineF(char* str,...) {
    /* TODO (#1#): Implement HConsole::AddLine() */
    char buffer[2048]={0};
    int i;

    va_list argptr;
    va_start( argptr, str );
    vsprintf( buffer, str, argptr );
    va_end( argptr );
    AddLine(buffer);
}

