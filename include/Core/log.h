/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__LOG_H
#define PAPERCUT__LOG_H		1

#include "Core/typedefs.h"
#include "Core/compat.h"
#include "Core/string.h"

//
//  ## Log ##
//    static class for logging
class Log
{
public:

	// logs
	static void write ( const string &str, ... );
};

#endif // PAPERCUT__LOG_H
