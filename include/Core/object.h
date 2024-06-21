/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__OBJECT_H
#define	PAPERCUT__OBJECT_H		1

#include "Core/stdstl.h"

#include "Core/typedefs.h"
#include "Core/classdefs.h"
#include "Core/pointer.h"
#include "Core/debug.h"
#include "Core/rtti.h"

// object typedefs
typedef std::map<dword,cObject*>		objMap;
typedef std::list<cObject*>			objList;

// ## cObject ##
//    base class for all engine objects
class cObject : public IRefCount
{
	// declares the RTTI information
	DECLARE_RTTI();

private:
	// static list of objects that are still in use
	static objMap	m_liveMap;
	// static list of objects for deletion
	static objList	m_deadList;
	// static value that ensures no two objects have the same id
	static dword	m_iNextID;
	// reference counting - when it reaches 0 it means the object is no longer in use
	dword			m_iRefCount;
	// keeps track of registered status within the kernel
	bool			m_isRegistered;

protected:
	// object's id code
	dword	m_id;

public:
	// constructor
	cObject ( void );
	// destructor
	virtual ~cObject ( void );

	// inline method for id discovery
	dword id ( void ) const { return m_id; }
	// registration method
	void kernelRegister ( void );
	// unregister method
	void kernelUnregister ( void );

	// ref control methods
	//    increments reference counter
	virtual void addRef ( void );
	//    decrements reference counter
	virtual void release ( void );

	// GC Control
	//    forces garbage collector
	static void collectGarbage ( void );
	//    collects all objects, incluing still-in-use ones. Usefull to check for non-dereferenced objects
	static void collectGarbageAll ( void );
};

// ## cTickableObject ##
//     base class for all objects that receive tick-based updates
class cTickableObject : public cObject
{
	// declares the RTTI information
	DECLARE_RTTI();

protected:
	// stores the mask of the ticks that this object responds too
	dword	m_tickMask;

public:
	// initialized the object
	//    @param tickMask: receives the mask of the related ticks
	virtual void init ( const dword tickMask );

	// filters the tick - if this object does not respond to the calling tick, it returns false; else returns true;
	virtual dword tickCheck ( const dword tick ) const { return (tick & m_tickMask); }
	// updates the object - pure virtual method: MUST OVERLOAD
	//    @param tick: the current tick to update
	//    @param ms:   the current update time in milisseconds
	virtual void tick ( const dword tick, const dword ms ) = 0;
};

// ## cDrawableObject ##
//     base class for all objects that are drawable. By definition, all drawable objects are also updatable with ticks
class cDrawableObject : public cTickableObject
{
	// declares the RTTI information
	DECLARE_RTTI();

public:
	// updates the frame prior to drawing
	virtual void updateFrame ( const dword ms ) = 0;
	// draws the object
	virtual void draw ( void ) = 0;
};

#endif // PAPERCUT__OBJECT_H
