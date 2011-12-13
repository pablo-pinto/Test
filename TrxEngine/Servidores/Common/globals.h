#define DEVICE_READ_STX				0
#define DEVICE_READ_LENGTH		    1
#define DEVICE_READ_DATA		    2

#define STATUS_CONNECTED     0
#define STATUS_DISCONNECTED  1
#define STATUS_CONNECTING    2

#define STATUS_READ_HEADER   0
#define STATUS_READ_DATA       1


#define STATUS_SERVER_IDLE       0
#define STATUS_SERVER_BUSY       1


#define CMD_OK                            0
#define CMD_EMPTY                     1
#define CMD_SYNTAX_ERROR       2
#define CMD_UNKNOWN               3
#define CMD_ERROR                     4
#define CMD_UPDATE_OK             5
#define CMD_SERVER_STARTED  6

//
// Constantes para mensajes de log
//

#define TRACE_LEVEL_ERROR		0
#define	TRACE_LEVEL_INFO		1
#define TRACE_LEVEL_DEBUG		2

//
// Largo maximo de la data de las transacciones
//

#define TRX_BUFFER_SIZE 8192