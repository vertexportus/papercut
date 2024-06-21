/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/log.h"

#include <cstdarg>
#include "Core/compat.h"

//  ## Log ##
//    static class for logging

void Log::write(const string &str, ...)
{
	va_list args;
	CHAR	buff[1024];

	// gets the apropriate 
#ifdef _MSC_VER
	__asm
	{
		mov eax, ebp;
		add eax, 0Ch;
		mov args, eax;
	}
#else
	va_start ( args, str );
#endif

	// setup final string and write
	//va_start ( args, str );
	VSPRINTF ( buff, 1024, str.c_str(), args );
	printf ( buff );
}
