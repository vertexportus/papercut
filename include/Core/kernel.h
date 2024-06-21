/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__KERNEL_H
#define PAPERCUT__KERNEL_H		1

#include "Core/stdstl.h"

#include "Core/typedefs.h"
#include "Core/classdefs.h"
#include "Core/engine_structs.h"

//		internal typedefs
typedef std::list<cTickableObject*>  tickList;
typedef std::list<cDrawableObject*>  drawList;
typedef std::map<dword,ITask*>		taskMap;

//
//  kernel class def
//

// ## cKernel class ##  this class is the core of the system.
//    it is responsible for tick and draw updates of all objects.
class cKernel
{
private:
	Engine			*m_pEngine;		//< pointer to the engine
	tTickInfo		*m_pInfo;		//< pointer to the tick information structure
	tickList		m_tickList;		//< list of objects to update tick
	drawList		m_drawList;		//< list of objects to draw

public:
	// kernel construtor - suposely does nothing - all initialization of object must be done calling the init method
	cKernel ( void );
	// kernel destructor
	virtual ~cKernel ( void );

	// registers the tickable and drawable objects
	void registerObj ( cObject *obj );
	// removes the object from the tick and draw lists
	void unregisterObj ( cObject *obj );

	// initializes the kernel
	virtual void init ( Engine *pE, tTickInfo &info );
	// called on every frame - updates and draws objects
	void step ( dword ms );
};

#endif // PAPERCUT__KERNEL_H
