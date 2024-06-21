/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__UNICODE_H
#define PAPERCUT__UNICODE_H			1

#include <cstring>

// defines CHAR and U macros
#ifdef UNICODE
	#define CHAR wchar_t //< define WIDE CHAR
	#define __T(t)  L##t
	#define T(t) __T(t)
#else
	#define CHAR char  //< define BYTE CHAR
	#define __T(t)  t
	#define T(t) __T(t)
#endif

// from here on, defines for each necessary C function that uses char as argument
#ifdef UNICODE

CHAR* __TextFormat ( const char *inBuffer, CHAR *outBuffer );
char* __GaranteeAscii ( const CHAR *inBuffer, char *outBuffer );

// use these macros to create conversion buffers only
#define UnicodeBuffer(name,size)	CHAR name[size]
#define AsciiBuffer(name,size)		char name[size]
// conversions macros
#define TextFormat(orig,buff)		__TextFormat ( orig, buff )
#define GaranteeAscii(orig,buff)	__GaranteeAscii ( orig, buff )

#define printf			wprintf
#define _scanf			wscanf
#define _scanf_s		wscanf_s
#define _fopen			_wfopen
#define _fopen_s		_wfopen_s
#define _vsprintf_s		vswprintf_s
#define _strlen			wcslen
#define _strcpy			wcscpy
#define _strcpy_s		wcscpy_s
#define _strncpy		wcsncpy
#define _strncpy_s		wcsncpy_s
#define _strcmp			wcscmp

#else

#define UnicodeBuffer(name,size)	
#define AsciiBuffer(name,size)		
#define TextFormat(orig,buff)		orig
#define GaranteeAscii(orig,buff)	orig

#endif // UNICODE

#endif // PAPERCUT__UNICODE_H