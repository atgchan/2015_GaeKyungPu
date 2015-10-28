#ifndef __MAIN_H__
#define __MAIN_H__

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>
// C RunTime Header Files
#include "CCStdC.h"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__, __LINE__)
#endif


#endif    // __MAIN_H__
