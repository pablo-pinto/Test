typedef struct
{
	char estacion[20];
	char tipo[1];
	char subtipo[1];
	char codigo[2];				// numerico
	char num_ref[6];			// numerico
	char largo1[3];				// numerico
	char largo2[3];				// numerico
	char mcc[4];				// numerico
} HDR_CONTROLADOR;				// 40