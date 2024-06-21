/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__RTTI_H
#define PAPERCUT__RTTI_H	1

/*

This is a really neat piece of code.

Simply, it allows objects to keep track of it's own name, id and it's derivates.
Also, implements methods for checking if some object if of a certain type.

To implement, simply DECLARE_RTTI() on the beguining of the class, and IMPLEMENT_RTTI on the declaration space
if the class is the base class (not derivated of other type with RTTI), use IMPLEMENT_RTTI_BASE. Its arguments are:

 * _tid: the TYPE ID of the object (usually declared on the format TYPE_YOURTYPE on Core\types.h
 * _class: the class name

 if the class is already inherited from another with RTTI, use IMPLEMENT_RTTI. Its arguments are:

 * _tid: the TYPE ID of the object
 * _class: the class name
 * _parent: the name of the parent class

 for checking if an object if of some type, use pObject->getType().isType ( TYPE_YOURTYPE );
 if you want to be sure the class is EXACLTY of that type(and not derivated), use pObject->getType().isExactlyType(TYPE_YOURTYPE);

 This RTTI implementation does not support multiple inheritance, as the engine was built on top of single inheritance
 still, one day the need for multiple may arrise and then I shall update this code.

*/

#include "Core/typedefs.h"
#include "Core/compat.h"

#define DECLARE_RTTI()							protected: static const RTTI _TYPE; \
												public: virtual const RTTI& getType() const { return _TYPE; }

#define IMPLEMENT_RTTI_BASE(_tid,_class)		const RTTI _class::_TYPE ( _tid, T(#_class), 0 )
#define IMPLEMENT_RTTI(_tid,_class,_parent)		const RTTI _class::_TYPE ( _tid, T(#_class), &_parent::_TYPE )

// ## RTTI class ##
class RTTI
{
private:
	// the TYPE ID
	const dword		m_type;
	// the class name string (char array format)
	const CHAR		*m_className;
	// pointer to the base RTTI object
	const RTTI		*m_baseType;

public:
	// constructor
	RTTI ( const dword type, const CHAR *className, const RTTI *parent );

	// method for checking object type
	bool isType ( const dword type ) const;
	// method for checking actual object type
	bool isExactlyType ( const dword type ) const;

	// get object type name
	const CHAR* getName ( void ) const { return m_className; }
};

#endif // PAPERCUT__RTTI_H
