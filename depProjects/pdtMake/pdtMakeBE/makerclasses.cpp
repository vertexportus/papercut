/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "makerclasses.h"

#include "Core/unicode.h"

// ## PluginControl singleton ##
//   this class controls the dynamic loading and calling of plugin libraries

// loads all DLLs
int PluginControl::load ( void )
{
	tDLLInfo	*info;
	HINSTANCE	inst;
	dllMake		makeCall;
	dllType		typeCall;
	// loads apropriate dll
	inst = LoadLibrary ( T("pdtImaged.dll") );
	if ( inst )
		makeCall = (dllMake)GetProcAddress ( inst, "make" );
	else
	{
		// error
		return -1;
	}
	// gets type()
	typeCall = (dllType)GetProcAddress ( inst, "type" );
	// creates info
	info = new tDLLInfo();
	info->instance = inst;
	info->make = makeCall;
	// places into map
	m_mapDll[typeCall()] = info;
	// all healthy
	return 0;
}

// makes the call
int PluginControl::call ( const dword type, tPDTMakeInfo &makeInfo )
{
	dllInfoMap::iterator	it;
	tPDTReturn				ret;

	// finds the apropriate DLL and calls make on it
	it = m_mapDll.find ( type );
	if ( it != m_mapDll.end() )
	{
		ret = (it->second->make)( (tPDTMakeInfo*)&makeInfo );
		// test errors : TODO WARN ABOUT ERROR
		if ( ret.error )
			return ret.error;
		// configures maker types
		dword len = (dword)_strlen(ret.pdtFile)+1;
		CHAR *f = new CHAR[len];
		_strncpy ( f, ret.pdtFile, len );
		makeInfo.lsFiles.push_back ( f );
		dword n = makeInfo.numSections++;
		makeInfo.sections[n].type = type;
		makeInfo.sections[n].entries = ret.entries;
		makeInfo.sections[n].offset = 0;
		makeInfo.sectionSize[n] = ret.fileSize;
	}
	// all well and good
	return 0;
}

// releases all DLLs
int PluginControl::release ( void )
{
	dllInfoMap::iterator	it;

	for ( it = m_mapDll.begin(); it != m_mapDll.end(); it++ )
	{
		// TODO FREE LIBRARY
		delete it->second;
	}
	// clear map
	m_mapDll.clear();
	return 0;
}

// ## ArgsProcessing singleton ##
//   this class processes and mantains argument information

// process incomming arguments
int ArgsProcessor::process ( const int argc, const CHAR **argv )
{
	int control;

	// no arguments
	if ( argc < 2 )
		return -1;

	// check arguments
	for ( int i = 1; i < argc; i++ )
	{
		if ( (argv[i])[0] == '-' )
		{
			// process individual parameter (and its value)
			if ( control = this->processArg(argv[i],argv[i+1]) )
				return control;
		}
	}
	// all well, good and healthy
	return 0;
}

// processes individual arguments
int ArgsProcessor::processArg ( const CHAR *arg, const CHAR *value )
{
	// --in
	if ( !_strcmp(arg,T("--in")) )
	{
		m_pIn = value;
		return 0;
	}
	// --out
	if ( !_strcmp(arg,T("--out")) )
	{
		m_pOut = value;
		return 0;
	}
	// --temp
	if ( !_strcmp(arg,T("--temp")) )
	{
		m_pTemp = value;
		return 0;
	}

	// no supported command
	return -1;
}

// ## XmlProcessor singleton ##
//   this class processes and mantains XML information

// loads XML file
int XmlProcessor::load ( const CHAR *xmlFile )
{
	AsciiBuffer ( __szBuff, 128 );
	m_pDoc = new TiXmlDocument ( GaranteeAscii((CHAR*)xmlFile,__szBuff) );
	if (m_pDoc)
	{
		m_pDoc->LoadFile();
		return 0;
	} else return -1;
}

// data section processing - returns data type
dword XmlProcessor::nextDataSection ( TiXmlElement **retEl )
{
	// gets element
	if ( !m_pLastElement )
	{
		m_pLastElement = m_pDoc->FirstChildElement ( "PDT" );
		m_pLastElement = m_pLastElement->FirstChildElement ( "data" );
	}
	else
	{
		m_pLastElement = m_pLastElement->NextSiblingElement ( "data" );
	}
	// sets return parameter value
	if ( !(*retEl = m_pLastElement) )
		return 0;
	// gets type and returns it
	return (dword)atoi ( m_pLastElement->Attribute("type") );
}