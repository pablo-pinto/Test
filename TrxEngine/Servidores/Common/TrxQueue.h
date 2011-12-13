#define MAX_QUEUE 500

class CClientSocket;

typedef struct
{
	char buffer[1100];
	int  size;
} QNode;

class CTrxQueue
{

public:
	CClientSocket *m_pSocket;
	QNode m_trx[MAX_QUEUE];
	int   m_head, m_tail;
	int   m_items;

public:
	CTrxQueue();
	~CTrxQueue();


	void Initialize();
	bool IsEmpty();
	int  Push( char *buffer, int size );
	void Peek( char **buffer, int *size );
	int  Pop();
};
