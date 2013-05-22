#include "piki.h"

#define CONSOLE_MAX_LINES 100
#define CONSOLE_MAX_LINE_LENGHT 256
#define CONSOLE_MAX_BUFFER 256
#define CONSOLE_MAX_COMMANDS 25
#define CONSOLE_MAX_HISTORY 25
#define CONSOLE_MAX_VARS 25

#define CONSOLE_TYPE_INT 0
#define CONSOLE_TYPE_FLOAT 1
#define CONSOLE_TYPE_STRING 2

#define CONSOLE_MOVELEFT        (256+0)
#define CONSOLE_MOVERIGHT       (256+1)
#define CONSOLE_MOVEUP          (256+2)
#define CONSOLE_MOVEDOWN        (256+3)
#define CONSOLE_DELETE          (256+4)
#define CONSOLE_MOVEHOME        (256+5)
#define CONSOLE_MOVEEND         (256+6)
#define CONSOLE_PGUP            (256+7)
#define CONSOLE_PGDOWN          (256+8)
#define CONSOLE_TOTAL_KEYS      (256+9)

typedef struct CON_Command_s{
char name[64];
void (*f)(char *cmd);
}CON_Command_t;

typedef struct CON_Variable_s{
char type;
char name[64];
int maxlenght;
char *variables;
float *variablef;
int *variablei;
}CON_Variable_t;

FILE* CON_Log;
bool CON_UseLog=false;
CTexture *CON_Background1=NULL;
CTexture *CON_Background2=NULL;
CTexture *CON_Logo=NULL;

float CON_Height=0;
int CON_CursorPos=0;
int CON_BufferLenght=0;
int CON_nLines=0;
char CON_Lines[CONSOLE_MAX_LINES][CONSOLE_MAX_LINE_LENGHT];
char CON_Buffer[CONSOLE_MAX_BUFFER]={0};
float xshift = 0;
float yshift = 0;
int CON_MaxHeight=300;

bool CON_keys[CONSOLE_TOTAL_KEYS];

bool CON_Open=false;

static CON_Command_s* CON_Commands[CONSOLE_MAX_COMMANDS]={0};
static unsigned int CON_Commands_count=0;

static CON_Variable_s* CON_Variables[CONSOLE_MAX_VARS]={0};
static unsigned int CON_Variables_count=0;

#include "console_commands.cpp"

void CON_BufferAdd(unsigned char);

char * CON_CompleteCommand(char *partial){
	int				len;
	int i;
	
	len = (int)strlen(partial);
	
	if (!len)
		return NULL;
		
// check for exact match
for (i=0; i<CON_Commands_count;i++){
		if (!strcmp (partial,CON_Commands[i]->name))
			return CON_Commands[i]->name;
}

for (i=0; i<CON_Commands_count;i++){
		if (!strncmp (partial,CON_Commands[i]->name, len))
			return CON_Commands[i]->name;
}

return NULL;

/*	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
		if (!strcmp (partial,cmd->name))
			return cmd->name;
	for (a=cmd_alias ; a ; a=a->next)
		if (!strcmp (partial, a->name))
			return a->name;

// check for partial match
	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
		if (!strncmp (partial,cmd->name, len))
			return cmd->name;
	for (a=cmd_alias ; a ; a=a->next)
		if (!strncmp (partial, a->name, len))
			return a->name;

	return NULL;*/


}

char * CON_CompleteVariable(char *partial){
	int				len;
	int i;
	
	len = (int)strlen(partial);
	
	if (!len)
		return NULL;
		
// check for exact match
for (i=0; i<CON_Variables_count;i++){
		if (!strcmp (partial,CON_Variables[i]->name))
			return CON_Variables[i]->name;
}

for (i=0; i<CON_Variables_count;i++){
		if (!strncmp (partial,CON_Variables[i]->name, len))
			return CON_Variables[i]->name;
}

return NULL;

/*	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
		if (!strcmp (partial,cmd->name))
			return cmd->name;
	for (a=cmd_alias ; a ; a=a->next)
		if (!strcmp (partial, a->name))
			return a->name;

// check for partial match
	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
		if (!strncmp (partial,cmd->name, len))
			return cmd->name;
	for (a=cmd_alias ; a ; a=a->next)
		if (!strncmp (partial, a->name, len))
			return a->name;

	return NULL;*/


}

void CON_Complete(){
char* cmd=NULL;;
if (CON_Buffer[0]=='\\')
cmd=CON_CompleteCommand(CON_Buffer+1);
else if (CON_Buffer[0]=='$'){
cmd=CON_CompleteVariable(CON_Buffer+1);
if(cmd!=NULL){
int len=strlen(cmd);
CON_Buffer[0]='$';
strcpy(CON_Buffer+1,cmd);
CON_Buffer[len+1]=' ';
CON_CursorPos=len+2;
CON_BufferLenght=len+2;
}
return;
}
else cmd=CON_CompleteCommand(CON_Buffer);
if(cmd!=NULL){
int len=strlen(cmd);
CON_Buffer[0]='\\';
strcpy(CON_Buffer+1,cmd);
CON_Buffer[len+1]=' ';
CON_CursorPos=len+2;
CON_BufferLenght=len+2;

}

}

void CON_Register( char *cmd, void (*function)(char *cmd) ) {

    if( CON_Commands_count < CONSOLE_MAX_COMMANDS ) {

        CON_Commands[CON_Commands_count] = (CON_Command_s*) malloc( sizeof(CON_Command_s) );
        memset( CON_Commands[CON_Commands_count], 0, sizeof(CON_Command_s) );

        strncpy( CON_Commands[CON_Commands_count]->name, cmd, 64 );
        CON_Commands[CON_Commands_count]->f = function;

        CON_Commands_count++;
    }

}

void CON_Update(){
if (CON_MaxHeight<16) CON_MaxHeight=16;
if (CON_MaxHeight>M_HEIGHT) CON_MaxHeight=M_HEIGHT;
if ((CON_Height<CON_MaxHeight)&&CON_Open){
CON_Height+=timerGetDT()*500;
}
if ((CON_Height>0)&&!CON_Open){
CON_Height-=timerGetDT()*600;
}

if (CON_Height>CON_MaxHeight) CON_Height=CON_MaxHeight;
xshift += (float)(timerGetDT())*0.02f;
yshift += (float)(timerGetDT())*0.01f;


}

void CON_Draw(){
if (CON_Height!=0){
R_Begin2D();
glColor3f( 1.0f, 1.0f, 1.0f );
glEnable( GL_TEXTURE_2D );
glEnable( GL_BLEND );
glBlendFunc( GL_ONE, GL_ZERO );
BIND(CON_Background1);
glBegin(GL_QUADS);
glTexCoord2d( xshift, 0 ); glVertex2f( 0, 0 );
glTexCoord2d( 2.0f+xshift, 0 ); glVertex2f( M_WIDTH, 0 );
glTexCoord2d( 2.0f+xshift, 1.0f ); glVertex2f( M_WIDTH, CON_Height );
glTexCoord2d( xshift, 1.0f ); glVertex2f( 0, CON_Height );
glEnd();
glBlendFunc( GL_ONE, GL_ONE );
BIND(CON_Background2);
glBegin(GL_QUADS);
glTexCoord2d( xshift*10.0f , yshift ); glVertex2f( 0, 0 );
glTexCoord2d( 2.0f+xshift*10.0f, yshift ); glVertex2f( M_WIDTH, 0 );
glTexCoord2d( 2.0f+xshift*10.0f, 1.0f + yshift ); glVertex2f( M_WIDTH, CON_Height );
glTexCoord2d( xshift*10.0f , 1.0f + yshift ); glVertex2f( 0, CON_Height );
glEnd();

//glBindTexture(GL_TEXTURE_2D, CON_Logo );
BIND(CON_Logo);
glBegin(GL_QUADS);
glTexCoord2d( 0 , 1); glVertex2f( M_WIDTH-138, CON_Height-138 );
glTexCoord2d( 1, 1 ); glVertex2f( M_WIDTH-10,  CON_Height-138 );
glTexCoord2d( 1, 0 ); glVertex2f( M_WIDTH-10,  CON_Height-10 );
glTexCoord2d( 0 , 0); glVertex2f( M_WIDTH-138, CON_Height-10 );
glEnd();




glDisable( GL_BLEND );
glBindTexture(GL_TEXTURE_2D, 0 );
glColor3f( 1.0f, 1.0f, 0.0f );
glBegin( GL_LINES );
glVertex2f( 0, CON_Height );
glVertex2f( M_WIDTH, CON_Height);
glEnd();

if (CON_Height>=16){
Font_drawtext( (int)M_WIDTH-9*19, (int)CON_Height-9, 9, "PikiEngineConsole" );
int maxlines=(int)CON_Height/14+1;
if (maxlines>CON_nLines){
maxlines=CON_nLines;
}
int pos=0;
for(int i=CON_nLines;i>=0&&i>=CON_nLines-maxlines;i--){
Font_drawtext(3,(int)(CON_Height-15)-pos,14,CON_Lines[i]);
pos+=14;
}

Font_drawtext( 3, (int)CON_Height-14, 14, "]%s",CON_Buffer );
Font_drawtext( (int)14*(CON_CursorPos+1)+3, (int)CON_Height-11, 14, "_" );

}
R_End2D();
}
}

void CON_BufferAdd(unsigned char c){
if( CON_CursorPos < CONSOLE_MAX_BUFFER-1 && isprint(c)) {

        if( CON_BufferLenght == CON_CursorPos ) {
            CON_Buffer[CON_CursorPos] = c;
            CON_CursorPos++;
            CON_BufferLenght++;
        }
        else { // we are inserting

            int i;
            for( i=CON_BufferLenght; i>CON_CursorPos; i-- ) {

                CON_Buffer[i] = CON_Buffer[i-1];
            }
            CON_Buffer[i] = c;
            CON_CursorPos++;
            CON_BufferLenght++;
        }

}

}
int CON_ExecCommand(char* buffer){
    unsigned int i, L;
    char cmd[64];
    char param[256];
    char buff[64];


    sscanf( buffer, "%s %s", buff, param );

    L = strlen( buff );
    for( i=0; i<63 && i<L; i++ ) {
        cmd[i] = tolower( buff[i] );
    }
    cmd[i] = '\0';


    for( i=0; i<CON_Commands_count; i++ ) {

        if( strncmp(CON_Commands[i]->name, cmd, 64) == 0 ) {

            if( strlen(buffer) > strlen(cmd) + 1 ) CON_Commands[i]->f( buffer+strlen(cmd)+1/*param*/ );
            else  CON_Commands[i]->f( 0 );
            
            return 1;
        }
    }

    CON_Add("^\4Unknown command '\\%s'",cmd);
    return 0;
}

int CON_ExecVar(char* buffer){
    unsigned int i, L;
    char cmd[64];
    char param[256];
    char buff[64];
    memset(&param,0,256);

    sscanf( buffer, "%s %s", buff, param );

    L = strlen( buff );
    for( i=0; i<63 && i<L; i++ ) {
        cmd[i] = tolower( buff[i] );
    }
    cmd[i] = '\0';

    int valuei=0;
    float valuef=0.0f;
    
    for( i=0; i<CON_Variables_count; i++ ) {

        if( strncmp(CON_Variables[i]->name, cmd, 64) == 0 ) {
            if (strlen(param)>0){
            
            switch(CON_Variables[i]->type){
            case(CONSOLE_TYPE_INT):
            if (sscanf(param,"%d",&valuei)){
            *(CON_Variables[i]->variablei)=valuei;
            CON_Add("Variable '$%s' set to '%d'",cmd,valuei);
            }
            break;
            case(CONSOLE_TYPE_FLOAT):
            if(sscanf(param,"%f",&valuef)){
            *(CON_Variables[i]->variablef)=valuef;
            CON_Add("Variable '$%s' set to '%f'",cmd,valuef);
            }
            break;
            case(CONSOLE_TYPE_STRING):
            strncpy(CON_Variables[i]->variables,param,CON_Variables[i]->maxlenght);
            //*(CON_Variables[i]->variablei)=valuei;
            CON_Add("Variable '%s' set to '%s'",cmd,param);
            break;
            }
            } else {
            switch(CON_Variables[i]->type){
            case CONSOLE_TYPE_INT: CON_Add("'$%s'='%d'",CON_Variables[i]->name,*CON_Variables[i]->variablei); break;
            case CONSOLE_TYPE_FLOAT: CON_Add("'$%s'='%f'",CON_Variables[i]->name,*CON_Variables[i]->variablef); break;
            case CONSOLE_TYPE_STRING: CON_Add("'$%s'='%s'",CON_Variables[i]->name,*CON_Variables[i]->variables); break;
            }
            }
            
            return 1;
        }
    }

    CON_Add("^\4Unknown variable '$%s'",cmd);
    return 0;
}

void CON_Execute(){
if (CON_Buffer[0]=='\\'){
CON_ExecCommand(CON_Buffer+1);
} else if (CON_Buffer[0]=='$'){
CON_ExecVar(CON_Buffer+1);
} else {
CON_Add("^\6%s",CON_Buffer);
}
CON_BufferClear();
}

void CON_Add(const char* str,...){

    char buffer[1024];
    int i;

    va_list argptr;
    va_start( argptr, str );
    vsprintf( buffer, str, argptr );
    va_end( argptr );


    if( CON_nLines < CONSOLE_MAX_LINES ) {

        strncpy( CON_Lines[CON_nLines], buffer, CONSOLE_MAX_LINE_LENGHT );
        CON_nLines++;
    }
    else {


        // move down all previous lines
        for( i=0; i<CONSOLE_MAX_LINES-1 && i<CON_nLines-1; i++ ) {

            strncpy( CON_Lines[i], CON_Lines[i+1], CONSOLE_MAX_LINE_LENGHT );
        }

        strncpy( CON_Lines[CON_nLines-1], buffer, CONSOLE_MAX_LINE_LENGHT );
    }
    if (CON_UseLog){
    CON_Log=fopen("console.log","a");
    if (CON_Log) {
    fprintf(CON_Log,"%s\n",buffer);
    fclose(CON_Log);
    }
    }
        





}

void CON_WM_CHAR(char argument){
            
if (argument=='`') {
CON_Open=!CON_Open;
return;
}

            if (CON_Open)      
            switch( argument ) {
            // enter key
            case '\r':
            case '\n':
                CON_Execute();
                /*if( !Command_treat(CON_Buffer) ) Console_flush();
                else Console_clearline();*/
                /*Console_savecommand( CON_Buffer );
                if( !CON_Bufferpos ) {

                    Console_flush();
                }
                else if( CON_Buffer[0] != '\\' ) {

                    //Console_flush();
                    Console_add( "^6not a command !" );
                    //Command_help( NULL );
                    Console_clearbuffer();
                }
                else if( !Command_treat(CON_Buffer+1) ) {

                    Console_add( "^6unknown command !" );
                    Console_clearbuffer();
                }
                else {

                    // command was treated successfuly
                    Console_clearbuffer();
                }*/
                break;


            // auto completion key !
            case '\t':
                CON_Complete();
                break;


            // backsuppress key
            case '\b':
                if( CON_CursorPos ) { // can we suppress safely?

                    // suppress last character if cursor is at the last position
                    if( CON_CursorPos == CON_BufferLenght ) {
                        CON_CursorPos--;
                        CON_BufferLenght--;
                        CON_Buffer[CON_CursorPos] = '\0';
                    }
                    // suppress previous character of current position
                    else {
                        for( int j=CON_CursorPos-1; j<CON_BufferLenght-1; j++ ) {
                            CON_Buffer[j] = CON_Buffer[j+1]; // move chars to left
                        }
                        CON_Buffer[CON_BufferLenght-1] = '\0';
                        CON_BufferLenght--;
                        CON_CursorPos--;
                    }
                }
                break;
                default: CON_BufferAdd(argument);
                }

}

void CON_HandleInput(int action ,char key){
if (CON_Open&&action==I_KD){

switch(key){
            case VK_DELETE:
                // can we suppress next character?
                if( CON_CursorPos<CON_BufferLenght ) {
                    for(int j=CON_CursorPos; j<CON_BufferLenght-1; j++ ) {
                        CON_Buffer[j] = CON_Buffer[j+1]; // move chars to left
                    }
                    CON_Buffer[CON_BufferLenght-1] = '\0';
                    CON_BufferLenght--;
                }
                break;


            // move left key
            case VK_LEFT:
                if( CON_CursorPos ) CON_CursorPos--;
                break;


            // move right key
            case VK_RIGHT:
                if( CON_CursorPos<CON_BufferLenght ) CON_CursorPos++;
                break;


            // previous command key
/*            case CONSOLE_MOVEUP:
                if( console->curr_cmd ) {
                    console->curr_cmd--;
                    strncpy( CON_Buffer, console->command[console->curr_cmd], CONSOLE_CMDLINELGTH );
                    CON_CursorPos = strlen( CON_Buffer );
                    CON_BufferLenght = CON_CursorPos;
                }
                break;*/


            // next command key
/*            case CONSOLE_MOVEDOWN:
                if( console->curr_cmd<console->last_cmd-1 ) {
                    console->curr_cmd++;
                    strncpy( CON_Buffer, console->command[console->curr_cmd], CONSOLE_CMDLINELGTH );
                    CON_CursorPos = strlen( CON_Buffer );
                    CON_BufferLenght = CON_CursorPos;
                }
                break;
*/

            // home key
            case VK_HOME:
                CON_CursorPos = 0;
                break;


            // end key
            case VK_END:
                CON_CursorPos = CON_BufferLenght;
                break;


            // page up key
            case VK_PRIOR:
                //if( console->first_visible_msg<console->last_msg-15 ) console->first_visible_msg++;
                break;


            // page down key
            case VK_NEXT:
                //if( console->first_visible_msg>0 ) console->first_visible_msg--;
                break;
}


}
}

void CON_BufferClear(){
memset(&CON_Buffer,0,CONSOLE_MAX_BUFFER);
CON_CursorPos=0;
CON_BufferLenght=0;
}

void CON_Clear(){
for (int i=0;i<CONSOLE_MAX_LINES;i++){
memset(&CON_Lines[i],0,CONSOLE_MAX_LINE_LENGHT);
}
CON_nLines=0;
}

void CON_InitLog(){
CON_Log=fopen("console.log","w");
if (CON_Log){
fprintf(CON_Log,"PikiEngine console output:\n");
fclose(CON_Log);
CON_UseLog=true;
} else {
CON_UseLog=false;
CON_Add("^\4Error opening logfile 'console.log'");
}
}

void CON_Init(){
CON_Background1=TMGR_Load("console/console1.tga");
CON_Background2=TMGR_Load("console/console2.tga");
CON_Logo=TMGR_Load("console/logo.tga");
/*CON_Log=fopen("pikiengine.log","w");
if (CON_Log){
fprintf(CON_Log,"PikiEngine logfile:\n");
fclose(CON_Log);
CON_UseLog=true;
} else {
CON_UseLog=false;
CON_Add("^\4Error opening logfile 'pikiengine.log'");
}
*/
CON_MaxHeight=M_HEIGHT/2;

CON_Add("Type \\help for help");
CON_Add("");

CON_RegisterVar("con_maxheight",&CON_MaxHeight);

CON_Register("quit",COMMAND_Quit);
CON_Register("exit",COMMAND_Exit);
CON_Register("clear",COMMAND_Clear);
CON_Register("help",COMMAND_Help);
}

void CON_DeInit(){
for (int i=0; i<CON_Commands_count;i++){
if (CON_Commands[i]!=NULL){
free(CON_Commands[i]);
CON_Commands[i]=NULL;
}
}
for (int i=0; i<CON_Variables_count;i++){
if (CON_Variables[i]!=NULL){
free(CON_Variables[i]);
CON_Variables[i]=NULL;
}
}
}

void CON_RegisterVar( char *name, float * var ){
    if( CON_Variables_count < CONSOLE_MAX_VARS ) {

        CON_Variables[CON_Variables_count] = (CON_Variable_s*) malloc( sizeof(CON_Variable_s) );
        memset( CON_Variables[CON_Variables_count], 0, sizeof(CON_Variable_s) );

        strncpy( CON_Variables[CON_Variables_count]->name, name, 64 );
        CON_Variables[CON_Variables_count]->variablef = var;
        CON_Variables[CON_Variables_count]->type=CONSOLE_TYPE_FLOAT;
        CON_Variables_count++;
    }

}
void CON_RegisterVar( char *name, int * var ){
    if( CON_Variables_count < CONSOLE_MAX_VARS ) {

        CON_Variables[CON_Variables_count] = (CON_Variable_s*) malloc( sizeof(CON_Variable_s) );
        memset( CON_Variables[CON_Variables_count], 0, sizeof(CON_Variable_s) );

        strncpy( CON_Variables[CON_Variables_count]->name, name, 64 );
        CON_Variables[CON_Variables_count]->variablei = var;
        CON_Variables[CON_Variables_count]->type=CONSOLE_TYPE_INT;
        CON_Variables_count++;
    }
}
void CON_RegisterVar( char *name, char * var ,unsigned int size){
    if( CON_Variables_count < CONSOLE_MAX_VARS ) {

        CON_Variables[CON_Variables_count] = (CON_Variable_s*) malloc( sizeof(CON_Variable_s) );
        memset( CON_Variables[CON_Variables_count], 0, sizeof(CON_Variable_s) );

        strncpy( CON_Variables[CON_Variables_count]->name, name, 64 );
        CON_Variables[CON_Variables_count]->variables = var;
        CON_Variables[CON_Variables_count]->maxlenght=size;
        CON_Variables[CON_Variables_count]->type=CONSOLE_TYPE_STRING;
        CON_Variables_count++;
    }
}

