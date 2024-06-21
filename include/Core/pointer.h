/***********************************************************************

	  PaperCut Engine (c) InsaneCows Entertainment 2006-2007

		Developers: Daniel "Portus" Alves
						( daniel.alves -at- member.igda.org )

***********************************************************************/
#ifndef PAPERCUT__POINTER_H
#define PAPERCUT__POINTER_H		1

#include "Core/typedefs.h"

// define to improve template typing
#define _TEMPLATE template <class T>

// ## IRefCount interface ##
//     all objects that are to use the smart pointer must implement this interface
//     cObject already implements it so extra work needed for derivated classes
class IRefCount
{
public:
	virtual void addRef ( void ) = 0;
	virtual void release ( void ) = 0;
};

// ## base_ptr ##
//   enables easy transition between smart pointer types
//   also enables the possibility of using collection types with smart pointers
class base_ptr
{
protected:
	// the actual pointer
	IRefCount *m_p;

public:
	// allows typecasting to normal pointer
	operator IRefCount* ( void ) const { return (IRefCount*)m_p; }
};

// ## pointer template ##
_TEMPLATE class pointer : public base_ptr
{
public:
	// constructor - might receive a pointer to T type, or not
	pointer ( T *p = 0 ) { m_p = p; if(p) p->addRef(); }
	// copy constructor - to allow smartpointer-to-smartpointer association
	pointer ( base_ptr &p ) { m_p = (T*)p; m_p->addRef(); }
	// copy constructor - to allow smartpointer-to-smartpointer association
	//pointer ( pointer<T> &p ) : m_p( (T*)p ) { m_p->addRef(); }
	// destructor - releases the object
	virtual ~pointer ( void ) { if (m_p) m_p->release(); }

	// assigns the atual pointer (inlined - see implementation below)
	void assign ( IRefCount *p );
	// resets the pointer - remembering to release the previous one if it exists
	void reset ( void ) { if (m_p) m_p->release(); m_p = 0; }
	// checks if pointer is valid, or if another pointer is equivalent to the current one
	bool check ( IRefCount *p = 0 ) const { if (p) return((m_p == p) ? true : false); else return false; }

	// enables typecasting to void*
	operator void* ( void ) const { return (void*)m_p; }
	// enables typecasting to T pointer type
	operator T* ( void ) const { return (T*)m_p; }

	// assign operator from raw pointer
	void operator= ( IRefCount *p ) { this->assign(p); }
	// assign operator from other smart pointer
	void operator= ( base_ptr &p ) { this->assign( (IRefCount*)p ); }
	// assign operator from other smart pointer
	void operator= ( pointer<T> &p ) { this->assign( (IRefCount*)p ); }

	// comparison operator with raw pointer
	bool operator== ( IRefCount *p ) { return this->check(p); }
	// comparison operator with another smart pointer
	bool operator== ( base_ptr &p ) { return this->check( (IRefCount*)p ); }
	// comparison operator with another smart pointer
	bool operator== ( pointer<T> &p ) { return this->check( (IRefCount*)p ); }

	// pointer magic: simulates -> pointer operations
	T* operator -> ( void ) const { return (T*)m_p; }
	// pointer magic: simulates * pointer operations
	T& operator * ( void ) const { return *m_p; }
};
// implementations
_TEMPLATE inline void pointer<T>::assign ( IRefCount *p )
{
	if ( m_p != p )
	{
		if ( m_p ) m_p->release();
		m_p = p;
		if ( m_p ) m_p->addRef();
	}
}

#endif // PAPERCUT__POINTER_H
