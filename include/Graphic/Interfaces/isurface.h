/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__ISURFACE_H
#define PAPERCUT__ISURFACE_H		1

#include "Core/typedefs.h"
#include "Graphic/graphtypes.h"

//
//  ## ISurface interface ##
//		This defines the default interface of a 2D surface.
class ISurface
{
protected:
	dword		m_id;					//< current id
	cRect		m_drawRect;				//< the actual area of the surface to be drawn
	dword		m_width, m_height;		//< size of the surface
	cColor		m_baseColor;			//< the base color of this surface
	byte		m_bpp;					//< bits per pixel

public:
	// default constructor - creates current id
	ISurface ( const dword id ) : m_id(id) {}
	// parameterized constructor
	ISurface ( const dword width, const dword height ) : m_id(0),m_width(width),m_height(height) {}
	// default destructor
	virtual ~ISurface ( void ) {}

	// blits from the draw area of the src surface
	virtual void blitFromSurface ( const ISurface &src ) = 0;
	// blits from the draw area of the src surface into a specified destination area within the surface
	virtual void blitFromSurface ( const ISurface &src, const cRect &dstRect ) = 0;
	// blits from a specified draw area of the src surface into a specified destination area within this surface
	virtual void blitFromSurface ( const ISurface &src, const cRect &dstRect, const cRect &srcRect ) = 0;

	// fills the surface with the plain base color
	virtual void clear ( void ) = 0;
	// fills the surface with the specified plain color
	virtual void clear ( const cColor &color ) = 0;

	// fills part of the surface with color
	virtual void fillRect ( const cRect &rect, const cColor &color ) = 0;

	// sets base color
	void setDrawColor ( const cColor &color ) { m_baseColor = color; }
	// gets base color
	cColor getDrawColor ( void ) const { return m_baseColor; }
	// sets the actual area of draw
	void setDrawRect ( const cRect &rect ) { this->m_drawRect = rect; }
	// gets the draw area rect
	cRect getDrawRect ( void ) const { return m_drawRect; }
	// gets the size of the surface as a 2tuple
	cVector2 getSize ( void ) const { return cVector2 ( m_width, m_height ); }
	// gets the bits per pixel
	byte getBpp ( void ) const { return m_bpp; }
};

#endif // PAPERCUT__ISURFACE_H
