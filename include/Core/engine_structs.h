/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__ENGINE_STRUCTS_H
#define PAPERCUT__ENGINE_STRUCTS_H		1

#include "Core/typedefs.h"
#include "Core/unicode.h"

#include "Graphic/graphtypes.h"
#include "Input/inputtypes.h"

// defines the maxinum number of ticks available to use
#define MAX_TICKS	32

// this structure defines the tick information
typedef struct _T_TickInfo
{
	dword numTicks;				//< number of used ticks - growing mask
	dword msPerTick[MAX_TICKS]; //< tick update time in milisseconds
	dword lastTick[MAX_TICKS];  //< time of last update of each tick in milisseconds
} tTickInfo;

// this structure defines the engine information
typedef struct _T_EngineInfo
{
	tTickInfo		tick;	//< tick information - passed to kernel internally
	tVideoInfo      video;  //< video information - passed to Graphic internally
	tInputInfo      input;  //< input information - passed to Input internally
	CHAR			*pdt;   //< pdt file
} tEngineInfo;

#endif // PAPERCUT__ENGINE_STRUCTS_H
