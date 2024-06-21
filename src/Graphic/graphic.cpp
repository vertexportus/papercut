/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Graphic/graphic.h"

#include "Core/memory.h"
#include "Graphic/SDL/sdl_graphic.h"

//
//  ## Graphic singleton class ##
//   graphic system - use this for all graphic-oriented needs

// static graphic pointer
IGraphic* cGraphic::m_pGraphic = 0;



// initialization video
void cGraphic::init ( tVideoInfo &info )
{
	// sets info
	m_pInfo = &info;
	// creates the necessary graphic object
	switch ( info.system )
	{
	case VideoSystem::SDL:
		m_pGraphic = (IGraphic*)new cGraphic_sdl();
	}
	// inits graphic subsystem
	m_pGraphic->init ( info );
}
