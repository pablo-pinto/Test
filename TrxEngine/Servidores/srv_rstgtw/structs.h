typedef struct
{
	char local[4];
	char caja[4];
	char fecha[8];
	char hora[6];
	char correlativo[6];				// numero de trace del sistema
	char pago[2];						// secuencia de pago
	char boleta[10];
	char servicio[3];					// VAS
	char familia[3];					// CRE
	char largo_header_servicio[3];
	char codigo_retorno[2];				// Codigo retorno interno
	char version;
    char filler[4];
} HEADER_GENERAL;


typedef struct
{
   char tipo_mensaje[4];
   char codigo_procesamiento[6];
   char identificacion_comercio[15];
   char identificacion_terminal[8];
   char largo_req[3];
   char largo_res[3];
} HEADER_VASA;


typedef struct
{
   char numero_cuenta[20];
   char fecha_expiracion[4];
   char codigo_seguridad[3];
   char monto[12];
   char cuotas[2];
   char modo_ingreso[3];
   char track1[76];
   char track2[37];
   char track_leido;
   char codigo_moneda[3];
   char tasa[5];
   char plan;
   char numero_ticket[4];
   char numero_ticket_original[4];
   char fecha_original[8];
   char hora_original[6];
   char codigo_autorizacion[6];
   char fecha_captura[4];
} REQUERIMIENTO_VASA;

typedef struct
{
   char numero_batch[3];
   char fecha_cierre[4];
   char hora_cierre[6];
   char numero_ticket_original[4];
   char numero_compras[4];
   char monto_compras[12];
   char numero_devoluciones[4];
   char monto_devoluciones[12];
   char numero_anulaciones[4];
   char monto_anulaciones[12];
} CIERRE_VASA;

typedef struct
{
   char codigo_autorizacion[6];
   char codigo_respuesta[2];
   char mensaje[201];
   char tasa_aplicar[5];
   char ticket_original[4];
   char fecha_hora_original[12];
   char numero_referencia[12];
} RESPUESTA_VASA;
