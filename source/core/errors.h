///////////////////////////////////////////
// CSG / GeoMod Tutorial. Write by Dexio //
//    Copyright (C) 2002 by BiG Soft     //
///////////////////////////////////////////

#ifndef HERRORS
#define HERRORS

extern void AddErrorTrace(char *sText,...);
extern bool AddErrorMsg(char *sFile,int iLine,const char *sBuf);
extern void DisplayError();

#define error(a) { if (AddErrorMsg(__FILE__,__LINE__,a)) throw a; }
#define check(a) { if (!(a)) { error(STR("Assertion failed: \"%s\"",#a)); }}
#define guard(a) { static const char *__FUNC_NAME__=#a; try {
//#define guard(a) { static const char *__FUNC_NAME__=__FUNCTION__; try {
#define unguard } catch(...) { AddErrorTrace("%s",__FUNC_NAME__); throw; }}
#define debug printf

#endif
