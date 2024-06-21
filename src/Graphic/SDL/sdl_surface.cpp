/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Graphic/SDL/sdl_surface.h"

#include "SDL_image.h"
#include "Core/debug.h"

//
//  ## cSurface_sdl class ##
//

// construct surface from raw data
cSurface_sdl::cSurface_sdl ( const dword surfID, const byte *rawData, const dword size ) : ISurface(surfID)
{
	SDL_RWops		*mem;	//< this structure will hold the processed data
	SDL_Surface		*raw;	//< raw surface - before converting to display format

	// process the data into SDL format
	mem = SDL_RWFromMem ( (void*)rawData, size );
	// get raw surface - second param is =1 so mem is freed automaticaly
	raw = IMG_Load_RW ( mem, 1 );
	// convert raw into displayFormat into m_pSurf pointer, and releases raw surface
	if ( raw )
	{
		m_pSurf = SDL_DisplayFormat ( raw );
		SDL_FreeSurface ( raw );
		// set information
		m_width = m_pSurf->w;
		m_height = m_pSurf->h;
		m_bpp = (byte)m_pSurf->format->BitsPerPixel;
	} else this->m_pSurf = 0; //< places a 0 onto the pointer so no trouble comes our way
}
// construct surface specified with parameters. ATTENTION: a screen surface must already been created.
cSurface_sdl::cSurface_sdl ( const dword width, const dword height ) : ISurface(width,height)
{
	SDL_PixelFormat *format = cScreenSurface_sdl::getScreenFormat(); //< gets pixel format of the screen

	// creates surface
	m_pSurf = SDL_CreateRGBSurface ( SDL_HWSURFACE, width, height,
		format->BitsPerPixel, format->Rmask, format->Gmask, format->Bmask, format->Amask );
}


// blits from the draw area of the src surface
void cSurface_sdl::blitFromSurface ( const ISurface &src )
{
	SDL_BlitSurface ( ((cSurface_sdl*)(&src))->m_pSurf, 0, m_pSurf, 0 );
}
// blits from the draw area of the src surface into a specified destination area within the surface
void cSurface_sdl::blitFromSurface ( const ISurface &src, const cRect &dstRect )
{
	SDL_BlitSurface ( ((cSurface_sdl*)(&src))->m_pSurf, 0, m_pSurf, 0 );
}
// blits from a specified draw area of the src surface into a specified destination area within this surface
void cSurface_sdl::blitFromSurface ( const ISurface &src, const cRect &dstRect, const cRect &srcRect ) {}

// fills the surface with the plain base color
void cSurface_sdl::clear ( void )
{
	SDL_Rect rect;

	rect.x = 0; rect.y = 0;
	rect.w = m_width; rect.h = m_height;

	SDL_FillRect ( m_pSurf, &rect,
		SDL_MapRGBA ( m_pSurf->format, m_baseColor.r, m_baseColor.g, m_baseColor.b, m_baseColor.a ) );
}
// fills the surface with the specified plain color
void cSurface_sdl::clear ( const cColor &color )
{
	SDL_Rect rect;

	rect.x = 0; rect.y = 0;
	rect.w = m_width; rect.h = m_height;

	SDL_FillRect ( m_pSurf, &rect,
		SDL_MapRGBA ( m_pSurf->format, color.r, color.g, color.b, color.a ) );
}

// fills part of the surface with color
void cSurface_sdl::fillRect ( const cRect &rect, const cColor &color )
{
	SDL_Rect r;

	r.x = rect.x; r.y = rect.y;
	r.w = rect.w; r.h = rect.h;

	SDL_FillRect ( m_pSurf, &r,
		SDL_MapRGBA ( m_pSurf->format, color.r, color.g, color.b, color.a ) );
}

//
//  ## cScreenSurface_sdl class ##
//

// default screen constructor
cScreenSurface_sdl::cScreenSurface_sdl ( const dword width, const dword height, const byte bpp, const cColor &bg ) : cSurface_sdl(0)
{
	// create SDL surface
	m_pSurf = SDL_SetVideoMode ( width, height, (int)bpp, SDL_HWSURFACE );
	// sets screen info
	m_width = width;
	m_height = height;
	m_bpp = bpp;
	m_baseColor = bg;
	// clears screen
	this->clear();
}
