/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/kernel.h"

#include "Core/stdstl.h"

#include "Core/object.h"
#include "Core/types.h"
#include "Core/memory.h"
#include "Core/engine.h"

#include "Input/input.h"
#include "Input/Interfaces/ieventmanager.h"

//
//  ## kernel class ##
//

// kernel constructor - does nothing because initialization MUST be done within the init() method
cKernel::cKernel ( void ) {}
// clears the object lists
cKernel::~cKernel ( void )
{
	m_tickList.clear();
	m_drawList.clear();
	cObject::collectGarbageAll();
}

// registers the tickable and drawable objects onto the apropriate lists
void cKernel::registerObj ( cObject *obj )
{
	if ( obj->getType().isType(TYPE_TICKABLE) )
		m_tickList.push_back ( (cTickableObject*)obj );
	if ( obj->getType().isType(TYPE_DRAWABLE) )
		m_drawList.push_back ( (cDrawableObject*)obj );
}
// removes the objects from the lists
void cKernel::unregisterObj ( cObject *obj )
{
	if ( obj->getType().isType(TYPE_TICKABLE) )
		m_tickList.remove ( (cTickableObject*)obj );
	if ( obj->getType().isType(TYPE_DRAWABLE) )
		m_drawList.remove ( (cDrawableObject*)obj );
}

// initialized the kernel with the tick information
void cKernel::init ( Engine *pE, tTickInfo &info ) { m_pEngine = pE; m_pInfo = &info; }
// steps through another game update
void cKernel::step ( dword ms )
{
	dword i;

	// process keyboard events
	m_pEngine->input()->processEvents();

	// PreStep
	m_pEngine->preStep();

	// initialized the tick mask to the first tick
	dword tickMask = 1;
	// goes through all the ticks checking if any needs updating
	for ( i = 0; i < m_pInfo->numTicks; i++ )
	{
		// checks if tick needs updating
		if ( (ms-m_pInfo->lastTick[i]) >= m_pInfo->msPerTick[i] )
		{
			// updates the tick on all objects...
			for ( tickList::iterator tit = m_tickList.begin(); tit != m_tickList.end(); tit++ )
			{
				// ...but only if it affects the object
				if ( (*tit)->tickCheck(tickMask) )
					(*tit)->tick ( tickMask, ms );
			}
		}
	}

	// goes through all objects and updates the frames
	drawList::iterator dit;
	for ( dit = m_drawList.begin(); dit != m_drawList.end(); dit++ )
		(*dit)->updateFrame ( ms );
	// draws all
	for ( dit = m_drawList.begin(); dit != m_drawList.end(); dit++ )
		(*dit)->draw();

	// postStep
	m_pEngine->postStep();

	// flips screen
	m_pEngine->graphic()->screenFlip();

	// deletes dead objects
	cObject::collectGarbage();
}
