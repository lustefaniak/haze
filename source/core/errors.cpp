///////////////////////////////////////////
// CSG / GeoMod Tutorial. Write by Dexio //
//    Copyright (C) 2002 by BiG Soft     //
///////////////////////////////////////////

#include "../Haze.h"
#pragma hdrstop

// Tekst
char sErrorMsg[4096];

// Gdzie
char *sErrorFile;
int iErrorLine;

// Flagi
bool bCriticalError = false;
bool bErrorMsgCleared = false;

// Dodaje tekst do komunikatu o b�zie. Zazwyczaj jest to
// nazwa procedury w kt�ej bd wystpi.
void AddErrorTrace ( char *sText,... )
{
    static char sBuf[256];
    va_list vArgs;

    // Jeeli bufor na komunikat b�u nie by jeszcze
    // czyszczony zr� to teraz.
    if ( !bErrorMsgCleared )
    {
        bErrorMsgCleared = true;
        memset ( sErrorMsg,0,sizeof ( sErrorMsg ) );
    }

    // Z�tekst z argument� wywoania funkcji.
    va_start ( vArgs,sText );
    vsprintf ( sBuf,sText,vArgs );
    va_end ( vArgs );

    // Dodaj tekst do bufora
    strcat ( sErrorMsg,sBuf );
    strcat ( sErrorMsg," <- " );
}

// Dodaje komunikat o b�zie do bufora. Zwraca true jeeli
// by to pierwszy taki komunikat.
bool AddErrorMsg ( char *sFile,int iLine,const char *sBuf )
{
    bool bFirstError;

    // Wyczy�bufor
    if ( !bErrorMsgCleared )
    {
        bErrorMsgCleared = true;
        memset ( sErrorMsg,0,sizeof ( sErrorMsg ) );
    }

    // Jeeli by to pierwszy bd zapisz miejsce jego wystpienia
    if ( !bCriticalError )
    {
        sErrorFile = sFile;
        iErrorLine = iLine;
    }

    // Dodaj tekst do bufora
    if ( !bCriticalError )
    {
        bFirstError = true;
        bCriticalError = true;
        strcat ( sErrorMsg,sBuf );
        strcat ( sErrorMsg,"\n\n" );
    }
    else
    {
        bFirstError = false;
        strcat ( sErrorMsg," (" );
        strcat ( sErrorMsg,sBuf );
        strcat ( sErrorMsg,") " );
    }

    // Zwr� czy by to pierwszy bd
    return bFirstError;
}

// Wywietla b�y w okienku dialogowym.
void DisplayError()
{
    int iLen;
    char sBuf[4096];

// HACK :)
    AddErrorTrace ( "WinMain" );

// Obetnij ostatni strzak�
    iLen = strlen ( sErrorMsg );
    if ( ( iLen>=4 ) && ( sErrorMsg[iLen-3]=='<' ) )
    {
        sErrorMsg[iLen-4] = 0;
    }

// Skada komunikat i wywietla go na ekranie
    sprintf ( sBuf,"%s%sFile: %s\nLine: %i",sErrorMsg,"\n\n",sErrorFile,iErrorLine );
    printf ( sBuf );
//MessageBox(0,sBuf,"Haze Critical Error",MB_ICONHAND | MB_TASKMODAL | MB_TOPMOST);
}
