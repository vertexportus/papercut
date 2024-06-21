/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__SDL_SURFACE_H
#define PAPERCUT__SDL_SURFACE_H		1

#include "SDL.h"

#include "Core/typedefs.h"
#include "Core/singleton.h"
#include "Graphic/Interfaces/isurface.h"

//
//  ## cSurface_sdl ##
//       SDL version of the surface class
class cSurface_sdl : public ISurface
{
protected:
	SDL_Surface *m_pSurf; //< SDL surface pointer

public:
	// default constructor
	cSurface_sdl ( const dword surfID ) : ISurface(surfID),m_pSurf(0) {}
	// construct surface from raw data
	cSurface_sdl ( const dword surfID, const byte *rawData, const dword size );
	// construct surface specified with parameters. ATTENTION: a screen surface must already been created.
	cSurface_sdl ( const dword width, const dword height );
	// default destructor - free's the sdl surface
	virtual ~cSurface_sdl ( void ) { if(m_pSurf) SDL_FreeSurface(m_pSurf); }

	// blits from the draw area of the src surface
	virtual void blitFromSurface ( const ISurface &src );
	// blits from the draw area of the src surface into a specified destination area within the surface
	virtual void blitFromSurface ( const ISurface &src, const cRect &dstRect );
	// blits from a specified draw area of the src surface into a specified destination area within this surface
	virtual void blitFromSurface ( const ISurface &src, const cRect &dstRect, const cRect &srcRect );

	// fills the surface with the plain base color
	virtual void clear ( void );
	// fills the surface with the specified plain color
	virtual void clear ( const cColor &color );

	// fills part of the surface with color
	virtual void fillRect ( const cRect &rect, const cColor &color );

protected:

};

//
//  ## cScreenSurface_sdl ##
//       special surface: the Screen
class cScreenSurface_sdl : public cSurface_sdl, public Singleton<cScreenSurface_sdl>
{
public:
	// default constructor (for a screen that is)
	cScreenSurface_sdl ( const dword width, const dword height, const byte bpp, const cColor &bg );

	// flips screen surface - after all it is double buffered
	void flip ( void ) { SDL_Flip(m_pSurf); }
	// get screen's pixel format
	static SDL_PixelFormat* getScreenFormat ( void )
	{ if (self && self->m_pSurf) return self->m_pSurf->format; else return 0; }
};

#endif // PAPERCUT__SDL_SURFACE_H
