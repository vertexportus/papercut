/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/engine.h"

#include "Core/kernel.h"
#include "Core/memory.h"
#include "Core/string.h"

// declares the static pointer to the engine's kernel
cKernel*        Engine::m_pKernel = 0;
cGraphic*       Engine::m_pGraphic = 0;
cInput*         Engine::m_pInput = 0;

// default constructor
Engine::Engine ( void ) : m_quit(false) {}
// default destructor
Engine::~Engine ( void )
{
    if ( m_pKernel ) delete m_pKernel;
    if ( m_pGraphic ) delete m_pGraphic;
    if ( m_pInput ) delete m_pInput;
	if ( ContentManager::singleton() ) delete ContentManager::singleton();
}

// run engine
void Engine::run ( void )
{
	// game loop
	while ( !m_quit )
	{
		m_pKernel->step ( System::getTime() );
	}
}

// initialization method - inits the kernel
void Engine::init ( tEngineInfo &info )
{
    // sets info
	m_pInfo = &info;
	// creates subsystems
	m_pKernel = new cKernel();
	m_pGraphic = new cGraphic();
	m_pInput = new cInput();
	// inits subsystems
	m_pKernel->init ( this, info.tick );
	m_pGraphic->init ( info.video );
	m_pInput->init ( info.input );
	// loads pdt
	ContentManager *p = new ContentManager();
	p->init ( string(info.pdt) );
}
