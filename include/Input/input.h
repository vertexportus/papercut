/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__INPUT_H
#define PAPERCUT__INPUT_H       1

#include "Core/typedefs.h"
#include "Core/singleton.h"
#include "Input/inputtypes.h"

//
//  ## cInput class ##
// responsible for all input and event related control
class cInput
{
private:
    IEventManager  *m_pManager;
    tInputInfo     *m_pInfo;

public:
    // default destructor - does nothing
    virtual ~cInput ( void ) {}

    // initialization method
    void init ( tInputInfo &info );

    // static manager access method
    IEventManager* manager ( void ) { return this->m_pManager; }
};

#endif // PAPERCUT__INPUT_H
