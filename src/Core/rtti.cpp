/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/rtti.h"

#include "Core/compat.h"

// read rtti.h for information of RTTI's workings

// constructor
RTTI::RTTI ( const dword type, const CHAR *className, const RTTI* parent ) : m_type(type),m_baseType(parent),m_className(className)
{}

// checks the object type
bool RTTI::isType ( const dword type ) const
{
	const RTTI *search = this;

	// searches all parent RTTI until the type is found...
	do
	{
		if ( search->m_type == type )
			return true;
	} while ( search = search->m_baseType );
	// ...or returns false if it is not.
	return false;
}
// checks the obhject exact type
bool RTTI::isExactlyType ( const dword type ) const
{
	// simply returns true if it is of the asked type
	if ( this->m_type == type )
		return true;
	else return false;
}
