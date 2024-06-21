/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__IEVENTMANAGER_H
#define PAPERCUT__IEVENTMANAGER_H			1

#include "Core/typedefs.h"
#include "Input/inputtypes.h"

//
//  ## IEventManager interface ##
//   defines the default interface for an input/system event manager
class IEventManager
{
protected:
	tInputInfo	*m_pInfo;  //< pointer to the event info structure

public:
	// initialization method
	void init ( const tInputInfo &info ) { m_pInfo = (tInputInfo*)&info; }

	// method that processes all queued events
	virtual void processEvents ( void ) = 0;
	// method for raising an event
	virtual void raiseEvent ( const tEvent &e ) = 0;

	// access input information
	tInputInfo& info ( void ) const { return *m_pInfo; }
};

#endif // PAPERCUT__IEVENTMANAGER_H
