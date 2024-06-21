/***********************************************************************

	  PDT Make (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PDTMAKE__MAKERCLASSES_H
#define PDTMAKE__MAKERCLASSES_H			1

#include "tinyxml.h"

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "Core/stdstl.h"
#include "Core/typedefs.h"
#include "Core/compat.h"
#include "Core/memory.h"
#include "Core/singleton.h"
#include "PDT/makerdefs.h"

// make DLL functions typedefs
typedef int (*dllType)(void);
typedef tPDTReturn (*dllMake)(tPDTMakeInfo*);

// dllInfo Struct
typedef struct _T_DLLInfo
{
	HINSTANCE		instance;
	dllMake			make;

	_T_DLLInfo ( void ) : instance(0),make(0) {}
} tDLLInfo;

// local types
typedef std::map<dword,tDLLInfo*> 	dllInfoMap;

// ## PluginControl singleton ##
//   this class controls the dynamic loading and calling of plugin libraries
class PluginControl : public Singleton<PluginControl>
{
private:
	dllInfoMap		m_mapDll;		//< keeps a map of all dynamic DLL references

public:
	// default construtor
	PluginControl ( void ) {}
	// default destructor
	virtual ~PluginControl ( void ) {}

	// loads all DLLs
	int load ( void );
	// makes the call
	int call ( const dword type, tPDTMakeInfo &makeInfo );
	// releases all DLLs
	int release ( void );
};

// ## ArgsProcessing singleton ##
//   this class processes and mantains argument information
class ArgsProcessor : public Singleton<ArgsProcessor>
{
private:
	const CHAR		*m_pIn;
	const CHAR		*m_pOut;
	const CHAR		*m_pTemp;

public:
	// default constructor
	ArgsProcessor ( void ) : m_pIn(0),m_pOut(0),m_pTemp(0) {}
	// default destructor
	virtual ~ArgsProcessor ( void ) {}

	// process incomming arguments
	int process ( const int argc, const CHAR **argv );
	/// get methods
	const CHAR* getArg_in ( void ) const { return m_pIn; }
	const CHAR* getArg_out ( void ) const { return m_pOut; }
	const CHAR* getArg_temp ( void ) const { return m_pTemp; }

private:
	// processes individual arguments
	int processArg ( const CHAR *arg, const CHAR *value );
};

// ## XmlProcessor singleton ##
//   this class processes and mantains XML information
class XmlProcessor : public Singleton<XmlProcessor>
{
private:
	TiXmlDocument	*m_pDoc;
	TiXmlElement	*m_pLastElement;

public:
	// default constructor
	XmlProcessor ( void ) : m_pDoc(0),m_pLastElement(0) {}
	// default destructor
	virtual ~XmlProcessor ( void ) {}

	// loads XML file
	int load ( const CHAR *xmlFile );
	// unloads XML file
	void unload ( void ) { if ( m_pDoc ) delete m_pDoc; }
	// data section processing - returns data type
	dword nextDataSection ( TiXmlElement **retEl );
};

#endif // PDTMAKE__MAKERCLASSES_H