/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__GRAPHTYPES_H
#define PAPERCUT__GRAPHTYPES_H		1

// class that defines a point or a 2D vector
class cVector2
{
public:
	int x, y;

	cVector2 ( void ) {}
	cVector2 ( dword _x, dword _y ) {}
};
// class that defines a Rectangle
class cRect : public cVector2
{
public:
	int w, h;
};

// class that defines RGBA color scheme
class cColor
{
public:
	cColor ( void ) {}
	cColor ( byte _r, byte _g, byte _b, byte _a = 0xFF ) : r(_r),g(_g),b(_b),a(_a) {}

	byte r,g,b,a;
};

// video system constants
namespace VideoSystem
{
	enum sysVideo
	{
		SDL = 0,
		maxVideoSystems
	};
};
using namespace VideoSystem;

// VideoMode structure
typedef struct _T_VideoMode
{
	dword		width, height;
	dword		flags;
	byte		bpp;
	cColor		bgColor;	//< screen background color
} tVideoMode;
// VideoInfo structure
typedef struct _T_VideoInfo
{
	sysVideo	system;		//< video system
	tVideoMode	mode;		//< video mode
} tVideoInfo;

#endif // PAPERCUT__GRAPHTYPES_H
