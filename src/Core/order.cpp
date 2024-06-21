/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#include "Core/order.h"

#include "Core/memory.h"

// OrderQueue class
OrderQueue::OrderQueue ( void ) : m_pHead(0),m_pTail(0) {}
OrderQueue::~OrderQueue ( void ) { this->flush(); }

// enqueues an order
void OrderQueue::push ( uOrder &order )
{
	tOrderNode *newNode = new tOrderNode;
	newNode->order = order;

	// add order to queue
	if ( !m_pHead )
	{
		m_pHead = newNode;
		m_pTail = newNode;
		newNode->previous = 0;
	} else {
		m_pTail->previous = newNode;
		m_pTail = newNode;
	}
}
// dequeues an order
uOrder OrderQueue::pop ( void )
{
	uOrder order;

	// get and delete next order
	if ( m_pHead )
	{
		tOrderNode *d = m_pHead;
		order = d->order;
		m_pHead = m_pHead->previous;
		delete d;
	} else order.type = ORDER_NULL;
	// return order
	return order;
}
// flushes all the orders from the queue
void OrderQueue::flush ( void )
{
	tOrderNode *prev, *node = m_pHead;

	// sanity return
	if ( !node ) return;

	// flush queue
	do
	{
		prev = node->previous;
		delete node;
	} while ( node = prev );
}

//
// ## IOrderReceiver interface ##
//

// executes the next order in queue - calls virtual method orderExec(uOrder&)
void IOrderReceiver::orderExecNext ( void )
{
    uOrder o = m_qOrders.pop();
	this->orderExec ( o );
}
// enqueues an order
void IOrderReceiver::orderQueue ( uOrder &order )
{
	// queues if no filter
	if ( !(this->orderFilter(order)) )
		m_qOrders.push ( order );
}
// executes instantly a received order - IT IS INSTANT AS IN RIGHT NOW!
void IOrderReceiver::orderInstant ( uOrder &order )
{
	// executes if no filter
	if ( !(this->orderFilter(order)) )
		this->orderExec ( order );
}

// filters orders. by default it filters all - overload if order acceptance needed
bool IOrderReceiver::orderFilter ( uOrder &order ) { return false; }
// executes the order. By default does nothing - overload for refinement
void IOrderReceiver::orderExec ( uOrder &order ) {}
