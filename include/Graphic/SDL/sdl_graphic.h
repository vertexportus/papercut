/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__SDL_GRAPHIC_H
#define PAPERCUT__SDL_GRAPHIC_H			1

#include "Core/typedefs.h"
#include "Graphic/Interfaces/igraphic.h"
#include "Graphic/SDL/sdl_surface.h"

//
//   ## cGraphic_sdl class ##
//	  SDL graphic system
class cGraphic_sdl : public IGraphic
{
private:
	cScreenSurface_sdl	*m_pScreen;		//< screen surface
	tVideoInfo			*m_pInfo;		//< video info structure

public:
	// default constructor
	cGraphic_sdl ( void ) : m_pScreen(0),m_pInfo(0) {}
	// default destructor
	virtual ~cGraphic_sdl ( void );

	// create surface related to the underlying graphics library - based on fileid
	virtual ISurface* createSurface ( const dword surfID, const byte *rawData, const dword size );
	// create surface related to the underlying graphics library
	virtual ISurface* createSurface ( const dword width, const dword height );

	// initialize graphics
	virtual void init ( tVideoInfo &info );

	// gets screen surface
	virtual ISurface* screen ( void ) { return m_pScreen; }
	// flips screen
	virtual void screenFlip ( void ) { m_pScreen->flip(); }
};

#endif // PAPERCUT__SDL_GRAPHIC_H
