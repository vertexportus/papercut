/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__SDL_EVENTMANAGER_H
#define PAPERCUT__SDL_EVENTMANAGER_H		1

#include "Core/typedefs.h"
#include "Input/Interfaces/ieventmanager.h"

#include "SDL.h"

//
//  ## cEventManager_sdl class ##
// defines an eventmanager based on SDL
class cEventManager_sdl : public IEventManager
{
public:
	// default constructor - does nothing
	cEventManager_sdl ( void ) {}
	// default destructor - does nothing
	virtual ~cEventManager_sdl ( void ) {}

	// processes the queued events
	virtual void processEvents ( void );
	// raises an event
	virtual void raiseEvent ( const tEvent &e );

protected:
	// sdl keyboard process method
	void processKeyboard ( SDLKey &key, tEvent &e );
	// default caller when there is no defined event handler
	void noReceiver ( const tEvent &e );
};

#endif // PAPERCUT__SDL_EVENTMANAGER_H
