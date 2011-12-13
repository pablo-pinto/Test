#include <string.h>
#include "TrxQueue.h"


CTrxQueue::CTrxQueue()
{
	m_head  = 0;
	m_tail  = 0;
	m_items = 0;
}

CTrxQueue::~CTrxQueue()
{
}

void CTrxQueue::Initialize()
{
	m_head  = 0;
	m_tail  = 0;
	m_items = 0;
}

bool CTrxQueue::IsEmpty()
{	
	return ( m_items == 0 );
}

int CTrxQueue::Push( char *buffer, int size )
{
	if ( m_items == MAX_QUEUE)
		return -1;

	memcpy( m_trx[m_head].buffer, buffer, size );
	m_trx[m_head].size = size;

	m_head = ( m_head + 1 ) % MAX_QUEUE;
	m_items++;
	return m_head;
}

int CTrxQueue::Pop()
{	
	if ( m_items == 0 )
		return -1;

	m_tail = ( m_tail + 1 ) % MAX_QUEUE;
	m_items--;
	return m_tail;
}

void CTrxQueue::Peek( char **buffer, int *size )
{
	*size   = m_trx[m_tail].size;
	*buffer = m_trx[m_tail].buffer;
}