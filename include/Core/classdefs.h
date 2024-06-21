/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__CLASSDEFS_H
#define PAPERCUT__CLASSDEFS_H		1

//
//  ##  classes
//

// singleton template
template <class S> class Singleton;

// order related
class IOrderReceiver;

// smart pointers
class base_ptr;
class base_fptr;
class IRefCount;
template <class T> class pointer;
template <class T> class functor;

// object classes
class RTTI;
class cObject;
class cTickableObject;
class cDrawableObject;

// kernel related classes
class Engine;
class cKernel;
class ITask;

// graphic interfaces
class ISurface;
class IGraphic;
class IScreen;
// inherited from the interfaces
class cSurface_sdl;
class cScreenSurface_sdl;
class cGraphic_sdl;
// graphic related
class cGraphic;
class cColor;
class cVector2;

// input related
class cInput;
// input interfaces
class IEventReceiver;
class IEventManager;
// inherited from the interfaces
class cEventManager_sdl;

// Content managers
class ContentManager;
class cManagerSurface;

#endif // PAPERCUT__CLASSDEFS_H
