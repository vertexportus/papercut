/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__FUNCTOR_H
#define PAPERCUT__FUNCTOR_H		1

#include "Core/pointer.h"

#define _TEMPLATE template <class T>

//
//  ## base_fptr ##
//    base class for the functor functionality
class base_fptr
{
public:
	virtual void operator() ( void ) = 0;
};

//
//  ## functor ##
//    pointer to class method wrapper - with 0 parameters
_TEMPLATE2 class functor : public base_fptr
{
protected:
	typedef void (T::*methodType)();	//< type of member function with 0 arguments
	pointer<T>	m_obj;					//< pointer to object
	methodType	m_method;				//< pointer to member

public:
	// constructor: sets the object and the method
	functor ( T *o, methodType *f ) { m_obj = o; m_method = f; }

	// operator that simulates functor as a regular function
	void operator() ( void ) { if ( m_obj->check() ) (m_obj->*m_method)(); }
};

#endif // PAPERCUT__FUNCTOR_H
