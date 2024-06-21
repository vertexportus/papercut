/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__SINGLETON_H
#define PAPERCUT__SINGLETON_H		1

#include "Core/debug.h"

//
//   ## Singleton template ##
//   Use this template class to deploy singleton functionality to a class
template <class S> class Singleton
{
protected:
	static S *self;

public:
	// default constructor - makes sure this is a singleton
	Singleton ( void ) { PCE_ASSERT(!self); self = (S*)this; }
	// default destructure - removes reference to old self
	virtual ~Singleton ( void ) { self = 0; }

	// method to access the singleton in format Singleton::singleton()
	static S* singleton ( void ) { return (S*)self; }
};
// initialize the static self
template <class S> S* Singleton<S>::self = 0;

#endif // PAPERCUT__SINGLETON_H
