/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__CONTENTMANAGER_H
#define PAPERCUT__CONTENTMANAGER_H			1

#include "Core/compat.h"
#include "Core/typedefs.h"
#include "Core/singleton.h"
#include "Core/string.h"
#include "PDT/pdt.h"

#include "Managers/manager_surface.h"

//  ## ContentManager singleton ##
// Responsible for all content-related management
class ContentManager : public Singleton<ContentManager>
{
private:
	static FILE			*m_pFile;
	string				*m_pStrPdt;
	tPDTSection			*m_pSections;
	cManagerSurface		*m_pSurfaceManager;

public:
	ContentManager ( void ) : Singleton(),m_pStrPdt(0),m_pSections(0),m_pSurfaceManager(0) {}
	virtual ~ContentManager ( void );

	// initializes content management
	void init ( const string &pdt );

	// sets the PDT (Papercut Data file )
	static void setPDT ( const string &pdt );
	// loads a content set from the PDT
	static void loadSet ( const dword setID );

	// returns the surface manager
	static cManagerSurface* getSurfaceManager ( void ) { return self->m_pSurfaceManager; }
};

#endif // PAPERCUT__CONTENTMANAGER_H