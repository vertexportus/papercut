/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__ENGINE_H
#define PAPERCUT__ENGINE_H

/*
this is the Engine singleton class.
Your game will inherit this class for refinement
*/
#include "Core/singleton.h"
#include "Core/classdefs.h"
#include "Core/kernel.h"
#include "Core/memory.h"
#include "Core/system.h"

#include "Graphic/graphic.h"
#include "Input/input.h"
#include "Managers/contentmanager.h"

#include "Core/engine_structs.h"

// ## engine class ##
class Engine : public Singleton<Engine>
{
protected:
	bool			m_quit;			//< quit engine if true
	static cKernel  *m_pKernel;     //< pointer to kernel
	static cGraphic *m_pGraphic;    //< pointer to graphic
	static cInput   *m_pInput;      //< pointer to input subsystem
	tEngineInfo     *m_pInfo;       //< pointer to info struct

public:
	// Engine constructor
	Engine ( void );
	// Engine destructor
	virtual ~Engine ( void );

	// static method to access the kernel pointer
	static cKernel* kernel ( void ) { return m_pKernel; }
	// static method to access the graphic subsystem
	static IGraphic* graphic ( void ) { return m_pGraphic->graphic(); }
	// static method to access the input subsystem
	static IEventManager* input ( void ) { return m_pInput->manager(); }

	// virtual initialization method
	virtual void init ( tEngineInfo &info );
	// force a quit
	virtual void quit ( void ) { m_quit = true; }

	// runs engine
	virtual void run ( void );

	// virtual method - redefine if there is need for pre-step computations
	virtual void preStep ( void ) {}
	// virtual method - redefine if there is need for post-step computations
	virtual void postStep ( void ) {}
};

#endif // PAPERCUT__ENGINE_H
