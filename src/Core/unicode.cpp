/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/unicode.h"
#include "Core/typedefs.h"

#include <cstdlib>

CHAR* __TextFormat ( const char *inBuffer, CHAR *outBuffer )
{
	dword len;

	len = (dword)strlen ( inBuffer ) + 1;
	mbstowcs ( outBuffer, inBuffer, len );

	return outBuffer;
}
char* __GaranteeAscii ( const CHAR *inBuffer, char *outBuffer )
{
	dword len;

	len = (dword)wcslen ( inBuffer ) + 1;
	wcstombs ( outBuffer, inBuffer, len );

	return outBuffer;
}
