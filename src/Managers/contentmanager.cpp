/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Managers/contentmanager.h"

//  ## ContentManager singleton ##
// Responsible for all content-related management
FILE* ContentManager::m_pFile = 0;

ContentManager::~ContentManager()
{
	if ( m_pFile )
		fclose ( m_pFile );
	if ( m_pSurfaceManager )
		delete m_pSurfaceManager;
}

// initializes content management
void ContentManager::init ( const string &pdt )
{
	dword	head[2];

	// sets PDT
	this->setPDT ( pdt );
	// creates sub-managers
	m_pSurfaceManager = new cManagerSurface();

	// get section info
	fread ( head, sizeof(dword), 2, m_pFile );
	m_pSections = new tPDTSection[*(head+1)];
	fread ( m_pSections, sizeof(tPDTSection), head[1], m_pFile );
	// inits managers
	for ( dword i = 0; i < head[1]; i++ )
	{
		if ( m_pSections[i].type == PDTMAKE_IMAGE )
			m_pSurfaceManager->init ( m_pFile, m_pSections[i] );
	}
}

// sets new pdt file
inline void ContentManager::setPDT ( const string &pdt )
{
	if ( m_pFile )
		fclose ( m_pFile );
	m_pFile = 0;
	FOPEN ( m_pFile, pdt.c_str(), "rb" );
}

// loads a content set from the PDT
void ContentManager::loadSet ( const dword setID )
{
	self->m_pSurfaceManager->loadSet ( setID );
}


	/*class ContentManager : public Singleton
{
private:
	FILE				*m_pFile;
	string				*m_pStrPdt;
	cSurfacaManager		*m_pSurfaceManager;

public:
	ContentManager ( void ) : Singleton() {}
	virtual ~ContentManager ( void ) {}

	// initializes content management
	void init ( const string &pdt );

	// sets the PDT (Papercut Data file )
	static void setPDT ( const string &pdt );
	// loads a content set from the PDT
	static void loadSet ( const dword setID );

	// returns the surface manager
	static cSurfaceManager* getSurfaceManager ( void ) { return self->m_pSurfaceManager; }
};*/