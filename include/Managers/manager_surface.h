/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__MANAGER_SURFACES_H
#define PAPERCUT__MANAGER_SURFACES_H			1

#include "Core/stdstl.h"

#include "Core/compat.h"
#include "Core/typedefs.h"
#include "Core/classdefs.h"
#include "Core/string.h"
#include "Graphic/Interfaces/isurface.h"
#include "PDT/pdt.h"

// local typedefs
typedef std::map<dword,ISurface*> surfaceMap;

//
//  ## cManagerSurface class ##
//
class cManagerSurface
{
private:
	FILE			*m_pFile;
	tPDTSection		*m_pSection;
	tPDTImage		*m_pImgHeader;
	surfaceMap		m_mapSurf;   //< list of all existing surfaces

public:
	cManagerSurface ( void );
	~cManagerSurface ( void );

	// init manager
	void init ( FILE *pdtFile, tPDTSection &section );
	// get a singular surface from it's ID
	ISurface* getSurface ( const dword surfID );

	friend class ContentManager;

protected:
	// loads a complete set of surfaces into the map
	void loadSet ( const dword setID );
	// loads a single file into the map
	void loadSurface ( const dword surfID, const string &filename );
	// loads a file from the PDT
	void loadSurface ( tPDTImage &info );
};

#endif // PAPERCUT__MANAGER_SURFACES_H