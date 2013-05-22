#ifndef _CONSOLE_H_
#define _CONSOLE_H_

extern bool CON_Open;

void CON_Update();
void CON_Draw();
void CON_WM_CHAR(char argument);
void CON_HandleInput(int,char);
void CON_Init();
void CON_InitLog();
void CON_DeInit();
void CON_Register( char *cmd, void (*function)(char *cmd) );
void CON_RegisterVar( char *name, float * var );
void CON_RegisterVar( char *name, int * var );
void CON_RegisterVar( char *name, char * var, unsigned int size);
void CON_Add(const char* msg,...);
void CON_BufferClear();
void CON_Clear();
#endif

