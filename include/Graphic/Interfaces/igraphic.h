/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__IGRAPHIC_H
#define PAPERCUT__IGRAPHIC_H		1

#include "Core/typedefs.h"
#include "Core/classdefs.h"
#include "Core/memory.h"

#include "Graphic/Interfaces/isurface.h"

//
//  ## IGraphic template ##
//		This defines the default interface of the graphics system
class IGraphic
{
public:
	// default constructor - here so that the polimorphed destructor is properly called
	virtual ~IGraphic ( void ) {}

	// create surface related to the underlying graphics library - based on fileid
	virtual ISurface* createSurface ( const dword surfID, const byte *rawData, const dword size ) = 0;
	// create surface related to the underlying graphics library
	virtual ISurface* createSurface ( const dword width, const dword height ) = 0;
	// free surface
	virtual void freeSurface ( const ISurface **ppSurface ) { delete *ppSurface; *ppSurface = 0; }

	// initialize graphics
	virtual void init ( tVideoInfo &info ) = 0;

	// gets screen surface
	virtual ISurface* screen ( void ) = 0;
	// flips screen
	virtual void screenFlip ( void ) = 0;
};

#endif // PAPERCUT__IGRAPHIC_H
