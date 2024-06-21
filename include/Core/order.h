/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__ORDER_H
#define PAPERCUT__ORDER_H		1

#include "Core/typedefs.h"

// order IDs
//   note: add new order types as defines
#define ORDER_NULL		0

// order data structures
//   note: create especialized order structures, and add them to union
typedef struct _T_uOrder
{
	// order type - used to know wich union type to access
	dword	type;
	// union of order data
	union _U_order {} order;
} uOrder;

// order queue implementation
typedef struct _T_orderNode
{
	uOrder			order;
	_T_orderNode	*previous;
} tOrderNode;
class OrderQueue
{
private:
	tOrderNode *m_pHead, *m_pTail;

public:
	OrderQueue ( void );
	~OrderQueue ( void );

	void push ( uOrder &order );
	uOrder pop ( void );
	void flush ( void );
};
// end:order queue implementation

// order interface
//    all objects that should receive orders must implement this interface
class IOrderReceiver
{
private:
	// the order queue
	OrderQueue	m_qOrders;

public:
	// Execute the next order - usually based on tick update (calls virtal protected method orderExec(uOrder&) )
	void orderExecNext ( void );
	// queues an order to execute at the next update
	void orderQueue ( uOrder &order );
	// executes and instant order - does not get queued: IT'S EXECUTED ON THE SPOT!
	void orderInstant ( uOrder &order );

protected:
	// filters the incomming order - allows you to discard an order before queueing
	virtual bool orderFilter ( uOrder &order );
	// actually executes the order
	virtual void orderExec ( uOrder &order );
};

#endif // PAPERCUT__ORDER_H
