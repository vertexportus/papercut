/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PDT__STRUCTS_H
#define PDT__STRUCTS_H			1

#include "PDT/makerdefs.h"
#include "PDT/makertypes.h"

// version
#define PDT_VERSION_MAJOR				0
#define PDT_VERSION_MINOR				1

// image list
typedef struct _T_PDTImage
{
	dword	id;		//< id of the image
	dword	size;	//> size of the image
	dword	offset;	//< partial offset of this image
} tPDTImage;

#endif // PDT__STRUCTS_H