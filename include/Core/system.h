/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__SYSTEM_H
#define PAPERCUT__SYSTEM_H		1

#include "sdl.h"

#include "Core/typedefs.h"

//
//  ## System static class ##
//
class System
{
private:
public:
	static dword getTime ( void ) { return SDL_GetTicks(); }
};

#endif // PAPERCUT__SYSTEM_H
