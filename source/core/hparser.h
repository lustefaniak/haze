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

#ifndef HPARSER_H
#define HPARSER_H

/*
 * parser plik� i nie tylko
 */
class HParser {
public:
    // class constructor
    HParser(unsigned int buffersize=2048);
    // class destructor
    ~HParser();
    // rozpoczyna parsowanie pliku
    int StartParse(string filename);
    // czyci bufor
    void ClearBuffer();
    // parsuje plik w poszukiwaniu token� (co pomiedzy biaymi znakami)
    int GetToken(unsigned int limit=0);
    // zmiena rozmiar buforu
    void ResizeBuffer(unsigned int nsize);
    // czyta a natrafi na znak ko�a linii lub przekroczy bufor
    int GetLine();
    // odczytuje jeden znak
    char GetChar();
    // przesuwa wskanik poza komentarze (tylko // #)
    int StripComment();
    // przesuwa wskanik pliku do nast�nego nie_biaego_znaku
    int StripWhite();
    // przewija plik do tyu o ilo�danych z ostatniego czytania do bufora
    int RewindLast();
    // zwraca wskanik do bufora
    const char* GetBuffer();
    // wywouje strip white i strip comment jak jest true w opcjach
    int Strip();
    // odczytuje tekst z " "
    int GetString();
protected:
    FILE* m_FP;
//      bool m_bStripWhite;
    bool m_bStripComment;
    int m_iLastRead;
    int m_iLastReadCount;
    unsigned int m_BufferSize;
    char *m_Buffer;
    string m_sFilename;
    // cofa wskanik do pliku o ile
    int FileRewind(int size);
};

#endif // HPARSER_H

