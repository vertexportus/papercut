/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__PDTMAKERDEFS_H
#define PAPERCUT__PDTMAKERDEFS_H		1

#include "tinyxml.h"
#include "Core/stdstl.h"
#include "Core/typedefs.h"
#include "Core/unicode.h"
// typedefs
typedef std::list<CHAR*>	listFiles;

// section
typedef struct _T_PDTSection
{
	dword	type;		//< typeID
	dword	entries;	//< number of entries on that particular section
	dword	offset;		//<	offset of the section
} tPDTSection;

// PDT info structure
typedef struct _T_PDTMakeInfo
{
	TiXmlElement	*xmlElement;
	CHAR			*wcTemp;
	listFiles		lsFiles;
	tPDTSection		sections[32];
	dword			sectionSize[32];
	dword			numSections;
} tPDTMakeInfo;

// PDT error return
typedef struct _T_PDTReturn
{
	dword	error;
	CHAR	pdtFile[256];
	dword	fileSize;
	dword	entries;
} tPDTReturn;

#endif // PAPERCUT__PDTMAKERDEFS_H