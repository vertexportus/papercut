/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__IEVENTRECEIVER_H
#define PAPERCUT__IEVENTRECEIVER_H			1

#include "Core/typedefs.h"
#include "Input/inputtypes.h"

//
// ## IEventReceiver interface ##
//  This must be implemented in a input/system event handler class
class IEventReceiver
{
public:
	// gets the event handler pointer
	IEventReceiver* eventReceiver ( void ) const { return (IEventReceiver*)this; }
	// processes an event
	virtual void eventProcess ( const tEvent &e ) = 0;
};

#endif // PAPERCUT__IEVENTRECEIVER_H
