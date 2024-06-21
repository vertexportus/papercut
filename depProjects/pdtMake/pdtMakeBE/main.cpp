/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "makerclasses.h"
#include "PDT/pdt.h"

// C helper functions
CHAR* dllName ( CHAR *name, CHAR *file );
int assemblePDT ( const CHAR *file, tPDTMakeInfo *info );

// ## MAIN ##
//
int wmain ( int argc, CHAR **argv )
{
	int control = 0, type;
	PluginControl	pluginControl;
	ArgsProcessor	argsProcessor;
	XmlProcessor	xmlProcessor;
	TiXmlElement	*element;
	tPDTMakeInfo	pdtInfo;

	// inits pdtInfo
	pdtInfo.numSections = 0;

	// process arguments
	do {
		if ( control = argsProcessor.process ( argc, (const CHAR**)argv ) )
			break;
		// sets temporary path defined in arguments
		pdtInfo.wcTemp = (CHAR*)argsProcessor.getArg_temp();

		// loads DLLs
		if ( control = pluginControl.load() )
			break;
		// opens XML file
		if ( control = xmlProcessor.load ( argsProcessor.getArg_in() ) )
			break;
		// processes XML and delegates calls
		while ( type = xmlProcessor.nextDataSection(&element) )
		{
			pdtInfo.xmlElement = element;
			if ( control = pluginControl.call ( type, pdtInfo ) )
				break;
		}
		// breaks out if previous loop finished with an error
		if ( control ) break;
		// assembles the PDT
		if ( control = assemblePDT(argsProcessor.getArg_out(),&pdtInfo) )
			break;
	} while(0);

	// releases
	control = pluginControl.release();
	xmlProcessor.unload();
	// end this shit
	PCE_END_MAIN ( control );
}

CHAR* dllName ( CHAR *name, CHAR *file )
{
	CHAR *temp;
	dword len = (dword)_strlen ( name );
	// constructs the name
	_strcpy ( file, name );
#ifdef _DEBUG
	file[len++] = 'd';
#endif
	temp = file+len;
	_strncpy ( temp, T(".dll"), 5 );
	// returns the filename
	return file;
}

int assemblePDT ( const CHAR *file, tPDTMakeInfo *info )
{
	int		control;
	listFiles::iterator	it;
	byte	buffer[1024];
	FILE	*pFile, *pDataFile;
	dword	i, bytes, offsetCalc;

	// sets the offset to calc all offsets
	offsetCalc = sizeof(dword)*2 + sizeof(tPDTSection)*info->numSections;

	// opens file
	FOPEN ( pFile, file, "wb" );
	if ( !pFile )
		return -443;

	// writes version to file
	__asm
	{
		mov ax, PDT_VERSION_MAJOR;
		shl eax, 16;
		mov ax, PDT_VERSION_MINOR;
		mov [i], eax;
	}
	fwrite ( &i, sizeof(dword), 1, pFile );
	// write number of sections
	fwrite ( &(info->numSections), sizeof(dword), 1, pFile );

	// writes header
	for ( i = 0; i < info->numSections; i++ )
	{
		info->sections[i].offset = offsetCalc;
		offsetCalc += info->sectionSize[i];
	}
	fwrite ( (tPDTSection*)info->sections, sizeof(tPDTSection), info->numSections, pFile );

	// writes all other files
	for ( it = info->lsFiles.begin(); it != info->lsFiles.end(); it++ )
	{
		// open file
		FOPEN ( pDataFile, *it, "rb" );
		if ( !pDataFile )
		{
			control = -2443;
			break;
		}
		// writes data
		while ( !feof(pDataFile) )
		{
			bytes = (dword)fread ( buffer, sizeof(byte), 1024, pDataFile );
			fwrite ( buffer, sizeof(byte), bytes, pFile );
		}
		// closes file
		fclose ( pDataFile );
		pDataFile = 0;
		// deletes name
		delete[] *it;
	}
	// all went well
	fclose ( pFile );
	return 0;
}