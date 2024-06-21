/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Graphic/SDL/sdl_graphic.h"

#include "Core/debug.h"
#include "Core/memory.h"
//
//   ## cGraphic_sdl class ##
//	  SDL graphic system

// default destructor
cGraphic_sdl::~cGraphic_sdl ( void )
{
	// deletes screen
	if (m_pScreen)
		delete m_pScreen;
	// quits SDL
	SDL_Quit();
}

// initialize graphics
void cGraphic_sdl::init ( tVideoInfo &info )
{
	tVideoMode *mode = &(info.mode);

	// inits SDL
	SDL_Init ( SDL_INIT_EVERYTHING );

	// sets info pointer
	m_pInfo = &info;
	// creates screen
	m_pScreen = new cScreenSurface_sdl ( mode->width, mode->height, mode->bpp, mode->bgColor );
}

// create surface related to the underlying graphics library - based on fileid
ISurface* cGraphic_sdl::createSurface ( const dword surfID, const byte *rawData, const dword size )
{
	return new cSurface_sdl ( surfID, rawData, size ); //< returns the newly created surface
}

// create surface related to the underlying graphics library
ISurface* cGraphic_sdl::createSurface ( const dword width, const dword height ) { return 0; }
