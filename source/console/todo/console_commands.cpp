
void COMMAND_Quit(char*){
PostQuitMessage(0);
}

void CLM_Exit();

void COMMAND_Exit(char*){
CON_Open=false;
CLM_Exit();
}

void COMMAND_Clear(char*){
CON_Clear();
}

void COMMAND_Help( char *param ) {

    unsigned int i;

    CON_Add( "Valid commands are :" );

    for( i=0; i<CON_Commands_count; i++ ) {

        CON_Add( "\\%s",CON_Commands[i]->name );
    }

}
