/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__COMPAT_H
#define PAPERCUT__COMPAT_H		1

#include <cstdio>

// define unicode support
#include "Core/unicode.h"

// for Visual studio compiles
#if _MSC_VER >= 1400
	#include <conio.h>
	#define PCE_END_MAIN(r)  logMemoryLeaks(); printf(T("\n\nProgram finished. Press ENTER to exit.")); _getch(); return r
    #define FOPEN(fp,fname,m)  _fopen_s ( &fp, fname, T(m) )
    #define VSPRINTF(buff,size,orig,args) _vsprintf_s ( buff, size, orig, args ) 
#else
	#define PCE_END_MAIN(r) logMemoryLeaks(); return r
	#define FOPEN(fp,fname,m) fp = _fopen ( fname, T(m) )
	#define VSPRINTF(buff,size,orig,args) _vsprintf ( buff, orig, args )
#endif

#endif // PAPERCUT__COMPAT_H
