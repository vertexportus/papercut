/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__GRAPHIC_H
#define PAPERCUT__GRAPHIC_H			1

#include "Core/memory.h"
#include "Core/typedefs.h"
#include "Core/singleton.h"
#include "Graphic/graphtypes.h"
#include "Graphic/Interfaces/igraphic.h"

//
//  ## Graphic singleton class ##
//   graphic system - use this for all graphic-oriented needs
class cGraphic
{
protected:
	static IGraphic		*m_pGraphic;
	tVideoInfo			*m_pInfo;

public:
	// default constructor
	cGraphic ( void ) : m_pInfo(0) {}
	// default destructor
	virtual ~cGraphic ( void ) { if(m_pGraphic) delete m_pGraphic; }

	// method for obtaining underlying graphic system
	static IGraphic* graphic ( void ) { return m_pGraphic; }

	// initialization method
	void init ( tVideoInfo &info );
};

#endif // PAPERCUT__GRAPHIC_H
