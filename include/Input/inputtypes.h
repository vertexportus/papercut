/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__INPUTTYPES_H
#define PAPERCUT__INPUTTYPES_H			1

#include "Core/classdefs.h"

// defines the available input systems
namespace InputSystem
{
	enum sysInput
	{
		SDL = 0,
		maxInputSystems
	};
}
using namespace InputSystem;

// info structure
typedef struct _T_InputInfo
{
	sysInput			system;		//< input system to use
	IEventReceiver		*pSys;		//< system event handler
	IEventReceiver		*pKb;		//< keyboard event handler
	IEventReceiver		*pMouse;	//< mouse event handler
} tInputInfo;

// input logic types
namespace EventType
{
	enum eventType
	{
		Unknown = 0,
		keyUp, keyDown,
		quit
	};
}
using namespace EventType;

namespace EventMsg
{
	enum eventMsg
	{
		Unknown = 0,
		keyUp, keyDown, keyLeft, keyRight,
		keyEscape,

		keyControlL
	};
}
using namespace EventMsg;

// event structure
typedef struct _T_Event
{
	eventType	type;
	eventMsg	msg;
} tEvent;

#endif // PAPERCUT__INPUTTYPES_H
