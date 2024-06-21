/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__STRING_H
#define PAPERCUT__STRING_H			1

#include <cstring>
#include "Core/unicode.h"
#include "Core/typedefs.h"

//  ## string class ##
// encapsulates string funcionality with unicode support
class string
{
private:
	CHAR		*m_pStr;    //< pointer to the actual string
	dword		m_buffSize; //< stores the actual buffer size, not the string size (ie. unrelated to any \0)

public:
	// default constructor
	string ( void ) : m_pStr(0),m_buffSize(0) {}
	// accepts pointer to proper char
	string ( CHAR *s );
	string ( const string &s );
	~string ( void );

	// inline methods
	CHAR* c_str ( void ) const { return m_pStr; }
	dword size ( void ) { return (dword)_strlen(m_pStr); }
	dword byteSize ( void ) { return ( this->size()*sizeof(CHAR) ); }
};

#endif // PAPERCUT__STRING_H