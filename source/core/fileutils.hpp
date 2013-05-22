//------------------------------------------------------------------------------
// File : fileutils.hpp
//------------------------------------------------------------------------------
// GLVU : Copyright 1997 - 2002 
//        The University of North Carolina at Chapel Hill
//------------------------------------------------------------------------------
// Permission to use, copy, modify, distribute and sell this software and its 
// documentation for any purpose is hereby granted without fee, provided that 
// the above copyright notice appear in all copies and that both that copyright 
// notice and this permission notice appear in supporting documentation. 
// Binaries may be compiled with this software without any royalties or 
// restrictions. 
//
// The University of North Carolina at Chapel Hill makes no representations 
// about the suitability of this software for any purpose. It is provided 
// "as is" without express or implied warranty.

//-----------------------------------------------------------------------------
// @ fileutils.h
// ---------------------------------------------------------------------------
// Cross-platform utilities to find files, change dirs, etc. 
//-----------------------------------------------------------------------------
//--------------------------------------------------------------------------//
// NOTE: ALL THESE UTILITIES THAT RETURN CHAR * AUTOMATICALLY ALLOCATE THE 
//       SPACE AND YOU MUST CLEAN IT UP WITH DELETE UNLESS OTHERWISE
//       SPECIFIED!
//
//       THESE ROUTINES COMPILE ON MSVC AND SGI IRIX MACHINES. MOST OTHER
//       ARCHITECTURES SHOULD WORK, BUT ARE UNTESTED.
//--------------------------------------------------------------------------//

#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

//-----------------------------------------------------------------------------
//-- Includes ----------------------------------------------------------------
//-----------------------------------------------------------------------------

#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
  #include <direct.h>
  #include <io.h>
#else
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  //#include <sys/dir.h>
  #include <glob.h>
  #include <stdio.h>
#endif


namespace FileUtils {

//-----------------------------------------------------------------------------
//-- Defines, Constants ------------------------------------------------------
//-----------------------------------------------------------------------------

#ifdef _WIN32
// win32 is actually happy with using / as the default dir char
  const char DefaultDirChar = '\\';
#else
  const char DefaultDirChar = '/';
#endif

enum { IS_DIR =0x1, IS_EXE =0x2, IS_READABLE =0x4, IS_WRITEABLE =0x8, 
       IS_FILE =0x10, IS_LINK =0x20, FILE_EXISTS =0x40
};

//-----------------------------------------------------------------------------
//-- Function Declarations, Macros -------------------------------------------
//-----------------------------------------------------------------------------

//--------------------------------------------------------------------------//
// BASENAME - RETURN THE FILE NAME ASSOCIATED WITH A FULL PATH NAME
//
// FullPathName - Pointer to the full path name of the file.
// DirChar - Directory separator character (i.e. '/' or '\').
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
std::string Basename(const char *FullPathName, char DirChar=DefaultDirChar);

//--------------------------------------------------------------------------//
// DIRNAME - RETURN THE DIRECTORY NAME ASSOCIATED WITH A FULL PATH NAME
// FullPathName - Pointer to the full path name of the file.
// DirChar - Directory separator character (i.e. '/' or '\\').
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
std::string Dirname(const char *FullPathName, char DirChar=DefaultDirChar);

//--------------------------------------------------------------------------//
// EXTNAME - RETURN THE FILE EXTENSION ASSOCIATED WITH A FULL PATH NAME
// FullPathName - Pointer to the full path name of the file.
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
std::string Extname(const char *FullPathName);

//--------------------------------------------------------------------------//
// STRIPEXT  - RETURN THE FILE WITHOUT ITS ASSOCIATED EXTENSION.
//             WITH A FULL PATH NAME
// FullPathName - Pointer to the full path name of the file.
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
std::string StripExt(const char *FullPathName);

//--------------------------------------------------------------------------//
// SPLITPATH  - SPLIT A PATH INTO A VECTOR OF STRINGS.
// FullPathName - Pointer to the full path name of the file.
//--------------------------------------------------------------------------//
void SplitPath(const char *FullPathName, 
               std::vector<std::string> &splitpath,
               char dirSep = DefaultDirChar);

//--------------------------------------------------------------------------//
// JOINPATH  - Join a vector of strings together into a path separated by
//             the dirchar
// split - Vector of string path parts
// dirSet - The character for separating directory components
//--------------------------------------------------------------------------//
std::string JoinPath(const std::vector<std::string> &splitPath,
                     char dirSep = DefaultDirChar);

//--------------------------------------------------------------------------//
// CHDIR - Change the current directory to DirName.
// DirName - Pointer to the directory name to change.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int ChDir(const char *DirName);

//--------------------------------------------------------------------------//
// GETDIR - GET THE CURRENT DIRECTORY NAME.
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
std::string GetDir();

//--------------------------------------------------------------------------//
// MKDIR  - CREATE A NEW DIRECTORY.
// RETURN - Pre-allocated string. use delete[] to dispose of it.
//--------------------------------------------------------------------------//
int MkDir(const char *DirName);

//--------------------------------------------------------------------------//
// ISDIR  - CHECK IF THE GIVEN STRING IS ACTUALLY A DIRECTORY.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int IsDir(const char *DirName);

//--------------------------------------------------------------------------//
// ISFILE  - CHECK IF THE GIVEN STRING IS A PLAIN FILE.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int IsFile(const char *FileName);

//--------------------------------------------------------------------------//
// ISLINK  - CHECK IF THE GIVEN STRING IS A LINK
// RETURN - 0 if failure, 1 if success.
//    (note this probably doesn't work on any platform)
//--------------------------------------------------------------------------//
int IsLink(const char *FileName);


//--------------------------------------------------------------------------//
// FILESTATUS  - PERFORM MULTIPLE CHECKS ON FILE ATTRIBUTES.
// RETURN - bit mask of some combination of the flags:
//           IS_DIR, IS_EXE, IS_READABLE, IS_WRITEABLE, IS_FILE, FILE_EXISTS 
//   (if you need to check multiple attributes this is more efficient
//    than individual calls to IsDir() IsReadable() etc
//--------------------------------------------------------------------------//
unsigned int FileStatus( const char *FileName );


//--------------------------------------------------------------------------//
// ISREADABLE  - CHECK IF THE GIVEN STRING IS A READABLE FILE.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int IsReadable(const char *PathName);

//--------------------------------------------------------------------------//
// ISWRITEABLE  - CHECK IF THE GIVEN STRING IS WRITEABLE.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int IsWriteable(const char *PathName);

//--------------------------------------------------------------------------//
// ISEXE  - CHECK IF THE GIVEN STRING IS EXECUTABLE (OR SEARCHABLE FOR A DIR).
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int IsExe(const char *PathName);


//--------------------------------------------------------------------------//
// FILEEXISTS  - SEE IF A FILE EXISTS.
// RETURN - 0 if failure, 1 if success.
//--------------------------------------------------------------------------//
int FileExists(const char *FileName);

//--------------------------------------------------------------------------//
// AddDirChar - Add a slash to the end of a string if it isn't already.
// WARNING: Assumes the string has room for one more char!
//--------------------------------------------------------------------------//
inline void AddDirChar(char *s)
{
  int l = strlen(s);
  if (s[l-1] != DefaultDirChar) {
    s[l] = DefaultDirChar;
    s[l+1] = 0;
  }
}

//--------------------------------------------------------------------------//
// AddDirChar - Add a slash to the end of a string if it isn't already.
//--------------------------------------------------------------------------//
inline void AddDirChar(std::string &s)
{
  int l = s.size();
  if (s[l-1] != DefaultDirChar) {
    s += DefaultDirChar;
  }
}


//--------------------------------------------------------------------------//
// ConvertDirChar - Change dir in path char to given char
//--------------------------------------------------------------------------//
std::string &ConvertDirChar(std::string &path, char dchar = DefaultDirChar);

//--------------------------------------------------------------------------//
// ConvertDirChar - Change dir chars in path char to given char
//--------------------------------------------------------------------------//
std::string ConvertDirChar(const char *path, char dchar = DefaultDirChar);

//--------------------------------------------------------------------------//
// StripDirChar - Remove the terminal dirchars from a path, if any
//--------------------------------------------------------------------------//
std::string &StripDirChar(std::string &path);

//-----------------------------------------------------------------------------
//-- Typedefs, Structs, Classes ----------------------------------------------
//-----------------------------------------------------------------------------

class FileFilter;
class FileFinder;

//-----------------------------------------------------------------------------
// Class FileFinder
// ---------------------------------------------------------------------------
// Allows an iterative search though a single directory.
// This is a shallow search, meaning, it doesn't recurse into subdirs.
// NOTE - Methods return pre-allocated strings!! Use delete[] to dispose of them.
//
// API:
//    NewSearch(<WildCard>, FindDirs)
//    NextFileName = Search();
//
// If FindDirs parameter is true, returns directories also. Directories are
// guaranteed to end in DefaultDirChar.
//-----------------------------------------------------------------------------
typedef bool (*DeepSearchFunc)(const char *name);
typedef bool (*DeepSearchExtFunc)(const std::vector<std::string>& names);
typedef bool (*DeepSearchExt2Func)(const char *filename, void *userData);
class FileFinder
{
  public:
    friend class FileFilter;

    inline FileFinder();
    inline ~FileFinder();

    void NewSearch(const char *searchStr, bool findDirs=false);
    std::string Search();
    
    bool DeepSearch(const char *searchStr, bool findDirs, DeepSearchFunc func);
    bool DeepSearch(const char *searchPath, const char *wildcard, bool findDirs, DeepSearchFunc func);

    bool DeepSearch(const char *searchStr, DeepSearchExtFunc func);
    bool DeepSearch(const char *searchPath, const char *wildcard, DeepSearchExtFunc func);
    
    bool DeepSearch(const char *searchStr, bool findDirs, DeepSearchExt2Func func, void *userData);
    bool DeepSearch(const char *searchPath, const char *wildcard, bool findDirs, DeepSearchExt2Func func, void *userData);
  protected:
    bool FFindDirs;
    bool SearchActive();
    void SearchClose();
  private:

    #ifdef _WIN32
      std::string GetFromFindInfo();

      _finddata_t FFindInfo;
      long FFindHandle;
      std::string FWildCard;
      std::string FPath;
      bool FCallFindFirst;
    #else
      glob_t FFindInfo;
      int FFindPos;
    #endif
};

//-----------------------------------------------------------------------------
//-- Typedefs, Structs, Classes ----------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class FileFilter
// ---------------------------------------------------------------------------
// Allows iterative "filtering" of files. 
// The user specifies a source directory and wildcard spec (and whether or
// not to perform the search recursively), and a destination directory.
// The filenames are then passed back to the user through the callback func.
// the user then will somehow "filter" the file in some way and write it out
// to the supplied destination directory.
//
// For example, this can be used to copy directory trees if the "filter" routine
// just copies the original file to the destination directory.
//
// API:
//    FilterFiles(srcDir, wildcard, destDir, recurse, func)
//      srcDir   - location of files to filter
//      wildcard - wilcard to search on (i.e., "*.txt").
//      destDir  - location to place "filtered files". This serves as the root
//                 of the subtree that will be created for recursive searches
//                 the subtree itself will be created for you.
//      recurse  - Whether or not to perform a recursive search for files.
//      func     - FilterFunc callback that gets called for every file that
//                 FilterFiles finds. 
//        oldName  - complete file name of the source file to be filtered.
//        newDir   - relative path name of where the "filtered" file should go.
//                   For example, if the files will keep the same name, you
//                   should write the file to: newDir + oldName.
//                   Dir is guaranteed to end in DefaultDirChar.
//
//-----------------------------------------------------------------------------
typedef void (*FilterFunc)(const char *oldName, const char *newDir);

class FileFilter
{
public:
  void FilterFiles(char *srcDir, char *wildcard, char *destDir, bool recurse, FilterFunc func);
private:
  static bool DoFilter(const char *filename, void *userData);

  std::string FSrcDir;
  std::string FWildcard;
  std::string FDestDir;
  FilterFunc FFilterFunc;
};

//-----------------------------------------------------------------------------
//-- External Variables ------------------------------------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-- Function Definitions ----------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// @ FileFinder::FileFinder()
// ---------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
inline 
FileFinder::FileFinder()
#ifdef _WIN32
: FFindHandle(-1l), FCallFindFirst(false)
#else
: FFindPos(-1)
#endif
{}

//-----------------------------------------------------------------------------
// @ FileFinder::~FileFinder()
// ---------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
inline 
FileFinder::~FileFinder()
{
  SearchClose();
}

} // end namespace FileUtils

#endif
