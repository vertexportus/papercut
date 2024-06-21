/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__STDSTL_H
#define PAPERCUT__STDSTL_H		1

#define STDSTL 1

// this header exists to include all the necessary STL headers
// to avoid inclusion post-new overloading
#if STDSTL == 1
	// checks to see if memory.h is already included, and raises a linker message
	#ifdef PAPERCUT_MEMORY
		#pragma message( "WARNING: new operator redefined when STL is included" )
	#endif
	#include <list>
	#include <map>
// includes replacements
#else
#endif

#endif // PAPERCUT__STDSTL_H
