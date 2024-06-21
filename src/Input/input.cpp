/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Input/input.h"

#include "Input/SDL/sdl_eventmanager.h"

//
//  ## Input singleton ##
// Singleton responsible for all input and event related control

// initialization method
void cInput::init ( tInputInfo &info )
{
    // sets the internal info pointer
    m_pInfo = &info;
    // initializes the apropriate manager
    switch ( info.system )
    {
    case InputSystem::SDL:
        m_pManager = (IEventManager*)new cEventManager_sdl();
    }
	// inits event manager
	m_pManager->init ( info );
}
