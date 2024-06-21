/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Managers/manager_surface.h"

#include "Core/engine.h"
#include "Graphic/graphic.h"
#include "Core/compat.h"
#include "Core/memory.h"
#include "Core/string.h"

//  ## cManagerSurface class ##
//

// default ctor
cManagerSurface::cManagerSurface ( void ) : m_pImgHeader(0) {}
// default dtor
cManagerSurface::~cManagerSurface ( void )
{
	surfaceMap::iterator it;

	for ( it = m_mapSurf.begin(); it != m_mapSurf.end(); it++ )
		delete it->second;

	if ( m_pImgHeader )
		delete[] m_pImgHeader;
}

// init manager
void cManagerSurface::init ( FILE *pdtFile, tPDTSection &section )
{
	m_pFile = pdtFile;
	m_pSection = &section;
	m_pImgHeader = new tPDTImage[m_pSection->entries];
}

// loads a complete set of surfaces into the map
void cManagerSurface::loadSet ( const dword setID )
{
	// gets me where section start
	fseek ( m_pFile, m_pSection->offset, SEEK_SET );
	// loads all headers
	fread ( m_pImgHeader, sizeof(tPDTImage), m_pSection->entries, m_pFile );
	// loads all surfaces
	for ( dword i = 0; i < m_pSection->entries; i++ )
		this->loadSurface ( m_pImgHeader[i] );
}

// gets a singular surface from it's ID
ISurface* cManagerSurface::getSurface ( const dword surfID )
{
	surfaceMap::iterator it;

	// finds the surface
	it = m_mapSurf.find ( surfID );
	if ( it != m_mapSurf.end() )
		return it->second;	//< returns the surface
	else return 0;	//< returns null if there is no surface with such id loaded
}

// loads a single surface and put's it into the map
void cManagerSurface::loadSurface ( const dword surfID, const string &filename )
{
	FILE			*pFile;
	byte			*buffer;
	dword			len;
	ISurface		*surf;

	// opens file
	FOPEN ( pFile, filename.c_str(), "rb" );
	// gets file length
	fseek ( pFile, 0, SEEK_END );
	len = ftell ( pFile );
	fseek ( pFile, 0, SEEK_SET );

	// allocate buffer
	buffer = new byte[len+1];
	// read into buffer
	fread ( buffer, len, 1, pFile );
	// close file
	fclose ( pFile );

	// creates new surface
	surf = Engine::graphic()->createSurface ( surfID, buffer, len );
	// releases buffer
	delete[] buffer;
	
	// adds surface to map
	m_mapSurf[surfID] = surf;
}

// loads a file from the PDT
void cManagerSurface::loadSurface ( tPDTImage &info )
{
	byte		*buffer;
	ISurface	*surf;

	// makes sure offset is proper
	info.offset += m_pSection->offset;
	// allocate buffer
	buffer = new byte[info.size];
	// reads bytes
	fseek ( m_pFile, info.offset, SEEK_SET );
	fread ( buffer, sizeof(byte), info.size, m_pFile );

	// create surface
	surf = Engine::graphic()->createSurface ( info.id, buffer, info.size );
	// releases buffer
	delete[] buffer;

	// adds to map
	m_mapSurf[info.id] = surf;
}