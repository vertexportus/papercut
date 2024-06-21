/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "pdt_image_dll.h"

#include <cstdio>

#include "Core/stdstl.h"
#include "Core/compat.h"
#include "Core/unicode.h"
#include "Core/typedefs.h"
#include "PDT/pdt.h"

// entry point
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

// internal data management
typedef std::list<tPDTImage> ImageList;
dword   gCurrentOffset = 0;

// function definitions
dword processImage ( FILE *pFile, TiXmlElement *elImage, ImageList *plsImages );
CHAR *getFileName ( CHAR *finishedName, CHAR *path, CHAR *file );
dword assembleFile ( CHAR *pwcFile, FILE *pDataFile, ImageList *plsImages, dword numImages );

// returns the dll type
dword type ( void ) { return PDTMAKE_IMAGE; }

// method responsible for making image PDT
tPDTReturn make (  tPDTMakeInfo *pdtMake )
{
	int			control = 0;
	tPDTReturn	_ret;
	dword		imageCount = 0; //< number of images
	FILE		*pFile = 0;
	ImageList	lsImages;
	// create temp storage file
	FOPEN ( pFile, getFileName(_ret.pdtFile,pdtMake->wcTemp,T("ttImage.pdtemp.temp")), "wb" );
	// returns an error if file not opened
	if ( !pFile )
	{
		_ret.error = -3; //< unable to open file
		return _ret;
	}

	// get first image tag
	TiXmlElement *elImage = pdtMake->xmlElement->FirstChildElement ( "image" );
	// and start processing
	while ( elImage )
	{
		imageCount++;
		if ( control = processImage(pFile,elImage,&lsImages) )
		{
			_ret.error = control; //< error processing image
			return _ret;	//< return the error
		}
		elImage = elImage->NextSiblingElement("image");
	}
	// reopen file for read
	fflush ( pFile );
	fclose ( pFile );
	FOPEN ( pFile, _ret.pdtFile, "rb" );

	// assembles file
	getFileName ( (CHAR*)&(_ret.pdtFile), pdtMake->wcTemp, T("ttImage.pdtemp") );
	if ( control = assembleFile(_ret.pdtFile, pFile, &lsImages,imageCount) )
	{
		_ret.error = control;
		return _ret;
	}

	// finishes file and buffers - all is well so return it
	fclose ( pFile );
	_ret.error = 0;
	_ret.entries = imageCount;
	_ret.fileSize = gCurrentOffset;
	return _ret;
}

// gets the actual file name buffer - returns *finishedFile
CHAR *getFileName ( CHAR *finishedName, CHAR *path, CHAR *file )
{
	CHAR	*temp;
	size_t	len1, len2;

	// gets size
	len1 = _strlen ( path );
	len2 = _strlen ( file );

	// copies
	temp = finishedName;
	_strncpy ( temp, path, len1 );
	temp += len1;
	_strncpy ( temp, file, len2+1 );

	// return string
	return finishedName;
}
// process image - returns image size
dword processImage ( FILE *pFile, TiXmlElement *elImage, ImageList *plsImages )
{
	byte		buffer[1024];
	dword		bytes;
	FILE		*pImageFile = 0;
	CHAR		ImageName[128];
	tPDTImage	imageInfo;

	// sets initial values
	imageInfo.id = (dword)atoi ( elImage->Attribute("id") );
	imageInfo.offset = gCurrentOffset;
	imageInfo.size = 0;

	// get image name
	TextFormat ( elImage->GetText(), ImageName );
	// open image
	FOPEN ( pImageFile, ImageName, "rb" ); 
	if ( !pImageFile ) return -10; //< error no image opened

	// copy bytes to file
	while ( !feof(pImageFile) )
	{
		bytes = (dword)fread ( buffer, sizeof(byte), 1024, pImageFile );
		fwrite ( buffer, sizeof(byte), bytes, pFile );
		imageInfo.size += bytes;
	}

	// closes file
	fclose ( pImageFile );
	// makes sure global offset is proper
	gCurrentOffset += imageInfo.size;

	// places image into list
	plsImages->push_back ( imageInfo );

	// returns all is well
	return 0;
}

dword assembleFile ( CHAR *pwcFile, FILE *pDataFile, ImageList *plsImages, dword numImages )
{
	byte					buffer[1024];
	ImageList::iterator		it;
	FILE					*pFinal = 0; //< FILE
	dword					i, headerSize = sizeof(tPDTImage)*numImages;
	tPDTImage				*pImagesHeader;

	// open file
	FOPEN ( pFinal, pwcFile, "wb" );
	if ( !pFinal )
		return -133;

	// creates header
	pImagesHeader =  new tPDTImage[numImages];

	// starts to compute the header
	for ( i = 0,it = plsImages->begin(); it != plsImages->end(); i++,it++ )
	{
		it->offset += headerSize;
		pImagesHeader[i] = *it;
	}
	plsImages->clear();

	// writes to new file the header, followed by all image data
	fseek ( pDataFile, 0, SEEK_SET );
	fwrite ( pImagesHeader, sizeof(tPDTImage), numImages, pFinal );
	while ( !feof(pDataFile) )
	{
		i = (dword)fread ( buffer, sizeof(byte), 1024, pDataFile );
		fwrite ( buffer, sizeof(byte), i, pFinal );
	}

	// destroys header
	if ( pImagesHeader )
		delete[] pImagesHeader;
	// closes file
	fclose ( pFinal );
	// all is well
	gCurrentOffset += sizeof(tPDTImage)*numImages;
	return 0;
}