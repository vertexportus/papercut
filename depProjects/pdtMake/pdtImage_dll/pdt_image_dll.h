/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PDTIMAGE_DLL__
#define PDTIMAGE_DLL__			1

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "tinyxml.h"
#include "PDT/makerdefs.h"
#include "PDT/makertypes.h"

#include "Core/typedefs.h"
#include "Core/unicode.h"
#include "Core/singleton.h"

// definition of api macro
#ifdef PDTIMAGE_DLL_EXPORTS
	#define PDTIMAGE_DLL __declspec(dllexport)
#else
	#define PDTIMAGE_DLL __declspec(dllimport)
#endif

extern "C"
{
// method responsible for making image PDT
PDTIMAGE_DLL dword type ( void );
PDTIMAGE_DLL tPDTReturn make ( tPDTMakeInfo *pdtMake );
}

#endif // PDTIMAGE_DLL__