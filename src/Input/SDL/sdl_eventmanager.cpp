/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Input/SDL/sdl_eventmanager.h"

#include "sdl.h"
#include "Core/log.h"
#include "Input/Interfaces/ieventreceiver.h"

//
//  ## cEventManager_sdl class ## 
//

// processes the queued events
void cEventManager_sdl::processEvents ( void )
{
	SDL_Event	sdl_e;  //< SDL event type
	tEvent		e;		//< PCE event type

	// dequeue all events from SDL poll
	while ( SDL_PollEvent(&sdl_e) )
	{
		// process the apropriate events
		switch ( sdl_e.type )
		{
		case SDL_QUIT:
			e.type = EventType::quit;
			// checks if there is a registered system event receiver and dispaches
			if ( m_pInfo->pSys ) m_pInfo->pSys->eventProcess ( e );
			// or calls the default no receiver method
			else this->noReceiver ( e );
			break;
		case SDL_KEYDOWN:
			e.type = EventType::keyDown;
			this->processKeyboard ( sdl_e.key.keysym.sym, e );
			break;
		case SDL_KEYUP:
			e.type = EventType::keyUp;
			this->processKeyboard ( sdl_e.key.keysym.sym, e );
			break;
		}
	}
}

// raises an event
void cEventManager_sdl::raiseEvent ( const tEvent &e )
{
	switch ( e.type )
	{
	case EventType::quit:
		// checks if there is a registered system event receiver and dispaches
		if ( m_pInfo->pSys ) m_pInfo->pSys->eventProcess ( e );
		// or calls the default no receiver method
		else this->noReceiver ( e );
		break;
	}
}

// sdl keyboard process method
void cEventManager_sdl::processKeyboard ( SDLKey &key, tEvent &e )
{
	// processes the key event
	switch ( key )
	{
	case SDLK_UP: e.msg = EventMsg::keyUp; break;
	case SDLK_DOWN: e.msg = EventMsg::keyDown; break;
	case SDLK_LEFT: e.msg = EventMsg::keyLeft; break;
	case SDLK_RIGHT: e.msg = EventMsg::keyRight; break;

	case SDLK_ESCAPE: e.msg = EventMsg::keyEscape; break;
	case SDLK_LCTRL: e.msg = EventMsg::keyControlL; break;
	}
	// checks if there is a registered keyboard event receiver and dispaches
	if ( m_pInfo->pKb ) m_pInfo->pKb->eventProcess ( e );
	// or calls the default no receiver method
	else this->noReceiver ( e );
}

// default caller when there is no defined event handler
void cEventManager_sdl::noReceiver ( const tEvent &e )
{
	Log::write ( T("No apropriate receiver for msg type: %d\n"), e.type );
}