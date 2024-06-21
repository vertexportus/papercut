/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/object.h"

#include "Core/debug.h"
#include "Core/types.h"
#include "Core/kernel.h"
#include "Core/engine.h"
#include "Core/memory.h"

//
//     ## cObject class ##
//

// static members
dword	cObject::m_iNextID = 0;
objMap	cObject::m_liveMap;
objList cObject::m_deadList;
// implements RTTI - check rtti.h for detailed explanation
IMPLEMENT_RTTI_BASE ( TYPE_OBJECT, cObject );

// constructor - sets the object id and reference counter
cObject::cObject ( void ) : m_iRefCount(0), m_isRegistered(false)
{
	// set id
	m_id = ++m_iNextID;
}
// destructor - removes teh object from the kernel lists
cObject::~cObject ( void )
{
	this->kernelUnregister();
}
// registers the object to the kernel
//    the purpose of this is to register the tickable and drawable objects
inline void cObject::kernelRegister ( void )
{
	Engine::kernel()->registerObj ( this );
	m_isRegistered = true;
}
// unregisters the object from the kernel
inline void cObject::kernelUnregister ( void )
{
	if ( m_isRegistered )
	{
		Engine::kernel()->unregisterObj ( this );
		m_isRegistered = false;
	}
}
// reference counter increment - inlined for better performance
inline void cObject::addRef ( void ) { m_iRefCount++; }
// reference counter decrement - inlined for better performance
//    if counter reaches 0, flags object for deletion
void cObject::release ( void )
{
	// assures reference counter is not already at 0 value
	//    it IS a unsigned value, not very good to decrement it past 0 would it?
	PCE_ASSERT ( m_iRefCount );
	// flags for destruction - YOU'RE DEAD, STUPID!
	if ( --m_iRefCount == 0 )
	{
		m_liveMap.erase ( m_id );
		m_deadList.push_back ( this );
	}
}

// collects dead objects
void cObject::collectGarbage ( void )
{
	objList::iterator it;

	// deletes all dead objects
	for ( it = m_deadList.begin(); it != m_deadList.end(); it++ )
		delete (*it);
	m_deadList.clear();
}
// collects ALL objects
void cObject::collectGarbageAll ( void )
{
	// TODO: add information
	collectGarbage();
	for ( objMap::iterator it = m_liveMap.begin(); it != m_liveMap.end(); it++ )
		delete it->second;
	m_liveMap.clear();
}


//
//		## cTickableObject class ##
//

// RTTI implementation - read rtti.h for more information
IMPLEMENT_RTTI ( TYPE_TICKABLE, cTickableObject, cObject );

// initializes object - also registers the object
void cTickableObject::init ( const dword tickMask ) { this->kernelRegister(); m_tickMask = (dword)tickMask; }

//
//		## cDrawableObject class ##
//

// implements cDrawableObject's RTTI
IMPLEMENT_RTTI ( TYPE_DRAWABLE, cDrawableObject, cTickableObject );
