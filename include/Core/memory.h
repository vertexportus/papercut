/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__MEMORY_H
#define PAPERCUT__MEMORY_H		1

// checks to see if stdstl.h is already included, and raises a linker message
#ifdef STDSTL_ALREADY_INCLUDED
	#pragma message( "WARNING: STL already included when redefining new operator" )
#endif

#pragma warning(disable:4291) //< disables 'no matching delete operator' warning

#include "Core/typedefs.h"
#include "Core/compat.h"

// this section is DEBUG only - mantains a list of all alloc'ed objects to make sure all is released
#ifdef _DEBUG
#include "Core/debug.h"
#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#define FILENAME_SIZE	512

// log functions
//    DO NOT EEEEVER use on the engine code
//    For logging purposed within the engine, use the Log singleton class
#define memlog		printf

// memory control data structures
typedef struct _T_alloc_info
{
	void	*address;
	dword	size;
	dword	line;
	CHAR	*file;
	bool	isArray;
} alloc_info;
typedef struct _T_alloc_entry
{
	alloc_info		*data;
	_T_alloc_entry	*next;
} alloc_entry;

// memory control functions
void addMemBlock ( const void *addr, const dword size, const CHAR *file, const dword line, const bool isArray = false );
void delMemBlock ( void *addr );
void logMemoryLeaks ( void );

// operator overloads
inline void* operator new ( size_t size, const CHAR *file, const dword line )
{
	void* ptr = malloc ( size );
	addMemBlock ( ptr, (dword)size, file, line );
	return ptr;
}
inline void* operator new[] ( size_t size, const CHAR *file, const dword line )
{
	void* ptr = malloc ( size );
	addMemBlock ( ptr, (dword)size, file, line, true );
	return ptr;
}
inline void operator delete ( void *p )
{
	PCE_ASSERT ( p );
	delMemBlock ( p );
	free ( p );
}
inline void operator delete[] ( void *p )
{
	PCE_ASSERT ( p );
	delMemBlock ( p );
	free ( p );
}
#endif // _DEBUG

// Strange defs for debug_new
//   this section replaces the normal new operator to support adicional information on the alloc'ed object - DEBUG only
#ifdef _DEBUG
	#define debug_new	new(T(__FILE__),__LINE__)
#else
	#define debug_new	new
#endif // _DEBUG
#define new		debug_new

// makes sure the STL is NOT included after this
#define PAPERCUT_MEMORY		 1

#endif // PAPERCUT__MEMORY_H
