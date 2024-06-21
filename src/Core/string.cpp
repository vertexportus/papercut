/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/memory.h"
#include "Core/string.h"

//  ## string class ##
// encapsulates string funcionality with unicode support
string::string ( CHAR *s )
{
	// copies the string
	m_buffSize = (dword)_strlen ( s );
	m_pStr = new CHAR[m_buffSize+1];
	memcpy ( m_pStr, s, sizeof(CHAR)*(m_buffSize+1) );
}
string::~string ( void )
{
	// deletes the string buffer if it exists
	if ( m_pStr )
		delete[] m_pStr;
}

/*
class string
{
private:
	CHAR		*m_pStr;   //< pointer to the actual string
	char		*m_pANSI;  //< pointer to the converted-to-ANSI string

public:
	// default constructor - also accepts pointer to proper char
	string ( CHAR *s = 0 );
#ifdef UNICODE
	// constructor for the other char type
	string ( char *s );
#endif
	string ( const string &s );
	~string ( void );

	CHAR* c_str ( void ) const { return m_pStr; }
	dword size ( void ) { return (dword)_strlen(m_pStr); }
	dword byteSize ( void ) { return ( this->size()*sizeof(CHAR) ); }

	// converts a string to unicode
	CHAR* convertToUnicode ( char *pocStr = 0 );
	// converts a string to ANSI
	char* convertToANSI ( CHAR *pStr = 0 );
};
*/