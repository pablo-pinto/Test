#define RETCODE_SUCCESS                "00"
#define RETCODE_COMMUNICATION_ERROR    "99"
#define RETCODE_COMMUNICATION_TIMEOUT  "94"
#define RETCODE_ERROR_EN_SISTEMA       "92"
#define RETCODE_ESTADO_SAF             "90"
//
// Header General
//
	
typedef struct
{
	char local[4];
	char caja[4];
	char fecha[8];
	char hora[6];
	char correlativo[6];
	char pago[2];
	char boleta[10];
	char servicio[3];
	char familia[3];
	char largo_header_servicio[3];
	char codigo_retorno[2];    
	char filler[5];
} HEADER_GENERAL;
