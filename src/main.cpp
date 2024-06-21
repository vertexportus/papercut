/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "SDL.h"

#include "Core/debug.h"

#include "Core/typedefs.h"
#include "Core/pointer.h"
#include "Core/object.h"
#include "Core/engine.h"
#include "Core/memory.h"
#include "Core/compat.h"

#include "Input/Interfaces/ieventreceiver.h"

#include "Graphic/graphtypes.h"
#include "Graphic/Interfaces/isurface.h"
#include "Managers/contentmanager.h"

class tempSys : public IEventReceiver
{
public:
	virtual void eventProcess ( const tEvent &e )
	{
		if ( e.type == EventType::quit )
			Engine::singleton()->quit();
	}
};


class Navezinha : public cDrawableObject
{
	DECLARE_RTTI();
private:
	ISurface	*m_pSurf;

public:
	Navezinha ( void ) {}
	virtual ~Navezinha ( void ) {}

	virtual void init ( void )
	{
		cTickableObject::init ( 0x0001 );
		m_pSurf = ContentManager::getSurfaceManager()->getSurface ( 1 );
	}

	virtual void tick ( const dword tick, const dword ms ) {}
	virtual void updateFrame ( const dword ms ) {}
	virtual void draw ( void )
	{
		Engine::graphic()->screen()->blitFromSurface ( *m_pSurf );
	}
};
IMPLEMENT_RTTI ( 444, Navezinha, cDrawableObject );

int main ( int argc, char **argv )
{
	tempSys s;
	tEngineInfo info;
	Engine *e = new Engine();
	Navezinha n;

	// defines bg color (while)
	cColor colorWhite ( 255,255,255 );

	info.tick.numTicks = 0;
	info.video.system = VideoSystem::SDL;
	info.video.mode.width = 800;
	info.video.mode.height = 600;
	info.video.mode.bpp = 32;
	info.video.mode.bgColor = colorWhite;
	info.input.system = InputSystem::SDL;
	info.input.pSys = s.eventReceiver();
	info.input.pKb = 0;
	info.input.pMouse = 0;
	info.pdt = T("sample.pdt");

	e->init(info);
	// test imgloader
	ContentManager::loadSet(0);
	n.init();
	// RUN FORREST, RUN!
	e->run();

	delete e;
	PCE_END_MAIN ( 0 );
}
