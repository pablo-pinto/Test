//
// Definicion de codigos de transacciones
//

#define SERVER_SHUTDOWN					0
#define SERVER_ACCEPT					7

#define TRX_REQ_FROM_DEVICE				10
#define SERVER_VERSION					11
#define SERVER_TRACE_ON					12 
#define SERVER_TRACE_OFF				13

#define TRX_REQ_SERVER					14
#define TRX_RES_SERVER					15
#define TRX_TRACE_MSG_SERVER			16
#define TRX_LOG_MSG_SERVER				17

#define TRX_RELEASE_SERVER				18

//
// Definicion de codigos de retorno
//

#define RETURN_CODE_SUCCESS				0
#define RETURN_CODE_SRV_UNKNOWN			20
#define RETURN_CODE_SRV_DISABLED		21
#define RETURN_CODE_SRV_BUSY			22
#define RETURN_CODE_SRV_NOT_RUNNING		23
