/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/memory.h"

#include "Core/compat.h"

#ifdef _DEBUG

// log function for memory-related code use only
/*
void memlog ( const CHAR *str, ... )
{
	va_list pl;

	// variable argument list
	va_start ( pl, str );
	printf ( str, pl );
	va_end ( pl );
}*/

// memory list-head
alloc_entry *_memlist = 0;

// memory control functions
void addMemBlock ( const void *addr, const dword size, const CHAR *file, const dword line, const bool isArray )
{
	// create the data blocks
	alloc_entry *entry = (alloc_entry*)malloc ( sizeof(alloc_entry) );
	alloc_info *info = (alloc_info*)malloc ( sizeof(alloc_info) );

	// populate the data blocks
	entry->data = info;
	info->address = const_cast<void*>(addr);
	info->file = const_cast<CHAR*>(file);
	info->line = line;
	info->size = size;
	info->isArray = isArray;

	// place into the queue
	if ( !_memlist )
	{
		_memlist = entry;
		entry->next = 0;
	} else {
		entry->next = _memlist;
		_memlist = entry;
	}
}
void delMemBlock ( void *addr )
{
	// get list head
	alloc_entry *last = 0, *entry = _memlist;
	// sanity checks
	PCE_ASSERT ( addr );
	if ( !entry ) return;

	// if the addr is the head of the list, do it right
	if ( entry->data->address == addr )
	{
		// sets new head
		_memlist = entry->next;
		// deletes node
		free ( entry->data );
		free ( entry );
		return; //< avoids any hassle
	}

	// search for node
	do
	{
		// walks in the list
		last = entry;
		entry = entry->next;
		// sanity check
		if ( !entry ) return;
	} while ( entry->data->address != addr );

	// delete node from list
	last->next = entry->next;
	free ( entry->data );
	free ( entry );
}
void logMemoryLeaks ( void )
{
	dword totalWasted = 0;
	void *del;
	alloc_info *info;
	alloc_entry *entry = _memlist;

	// check for memory leak
	if ( entry ) memlog ( T("\nMEMORY LEAK!!!\n") );
	else return;

	// elaborate on the leak
	while ( entry )
	{
		// simplify info access
		info = entry->data;
		// add to wasted
		totalWasted += info->size;
		// log
		memlog ( T("File: '%s' Line: %d Address: 0x%p Unfreed: %d bytes %s\n"),
			info->file, info->line, info->address, info->size,
			(info->isArray ? "(Array)" : "") );
		// remove the node
		del = entry->data->address;
		entry = entry->next;
		delMemBlock ( del );
	}
	// log total wasted memory
	memlog ( T("\nTotal leaked memory: %d bytes"), totalWasted );
}

#endif // _DEBUG
