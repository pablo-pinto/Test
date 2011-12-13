#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mid.h"

char    jperror[128];

BOOL    genera( char *szpath, char letter );
BOOL    muestra_ppl( char *szpath, char *codigo, char *szoutput );
char    *busca_ppl( char *szpath, char *codigo );

BOOL jp( char *szpath, char *szcode, char *szoutput )
{
	FILE *fp;
	char szfilename[128];

	
	sprintf( szfilename, "%s\\Documentacion de Mensajes\\%c.idx", szpath, tolower(szcode[0]));

		
	if ( ( fp = fopen( szfilename, "r" ) ) == NULL )
	
	{
		if ( !genera( szpath, szcode[0] ))
				return FALSE;	
	}

	if ( !muestra_ppl( szpath, szcode, szoutput ) )
		return FALSE;

	return TRUE;
}

BOOL muestra_ppl( char *szpath, char *codigo, char *szoutput )
{
	FILE    *doc;
	char    ref[32];
	long    inicio, fin;
	char    szfilename[128];

	
	sprintf( szfilename, "%s\\Documentacion de Mensajes\\%c.rhm", szpath, tolower(codigo[0]));


	doc = fopen( szfilename, "rb" );
	
	if ( doc == NULL )
	{
	   MessageBox( NULL,
		   "No se ha encontrado, o no se ha podido abrir el archivo de documentacion,\n"
		   "no se puede mostar detalle del error. Presione Aceptar para continuar.",
		   "VigiaNT",
		   MB_ICONWARNING );
	   return FALSE;
	}


	if ( strncmp( "No ex", busca_ppl( szpath, codigo ), 5 ) == 0 )
	{
		printf( "%s\n", busca_ppl( szpath, codigo ));
		return FALSE;
	}
	else
	strncpy( ref, busca_ppl( szpath, codigo ), 16 );

	inicio = atol( mid( ref , 4 , 6 ) );
	fin    = atol( mid( ref , 10, 6 ) );

	fseek( doc, inicio, SEEK_SET );

	fread( szoutput, ( fin - inicio ), 1, doc );

	szoutput[(size_t)(fin-inicio-1)] = 0;


	fclose(doc);
	return TRUE;
}

char *busca_ppl( char *szpath, char *codigo )
{
	FILE *fp;
	char buffer[256];
	char szfilename[128];

	sprintf( szfilename, "%s\\Documentacion de Mensajes\\%c.idx", szpath, tolower(codigo[0]));	

	fp = fopen( szfilename,"r" );

	for( ; ; )
	{
		if ( fgets( buffer, 256, fp ) == NULL )
			break;


		if ( strncmp( codigo, buffer, 4 ) == 0 )
		{
			fclose(fp);
			return( borracoma(buffer) );
		}

		memset(buffer, 0, sizeof(buffer) );

	}

	sprintf( jperror,"No existe documentacion para mensaje <%s>", codigo );
	return jperror;
}


BOOL genera( char *szpath, char letter )
{
   FILE    *doc, *idx;
   char    buffer[5];
   long    posicion;
   int     veces;
   int     retcode;
   char    szdoc[128];
   char    szidx[128];

   sprintf( szdoc, "%s\\Documentacion de Mensajes\\%c.rhm", szpath, tolower(letter));
   sprintf( szidx, "%s\\Documentacion de Mensajes\\%c.idx", szpath, tolower(letter));

   doc = fopen( szdoc, "r" );
   idx = fopen( szidx, "w" );

   if ( doc == NULL )
   {
	   MessageBox(
		   NULL,
		   "No se ha encontrado, o no se ha podido abrir el archivo de documentacion,\n"
		   "no se puede mostar detalle del error. Presione Aceptar para continuar.",
		   "VigiaNT",
		   MB_ICONWARNING );
	   return FALSE;
   }

   veces = 0;

   for( ; ; )
   {
	   retcode = fread( buffer, 1, 1, doc );
	   if ( retcode != 1 )
		   break;

	   if ( buffer[0] =='' )
	   {
		   if ( veces == 0 )
		   {
			   posicion = ftell(doc);
			   fread( buffer, 1, 1, doc);
			   memset(buffer, 0, sizeof(buffer) );
			   fread(buffer, 4, 1, doc);
			   fprintf(idx, "%s%06ld", buffer, posicion);
		   }
		   else if ( veces > 0 )
		   {
			   posicion = ftell(doc);
			   fread( buffer, 1, 1, doc);
			   memset(buffer, 0, sizeof(buffer) );
			   if ( fread(buffer, 4, 1, doc) != 1)
			   {
				   fprintf(idx, "%06ld;", (posicion-2) );
				   break;
			   }
			   else
				   fprintf(idx, "%06ld;\n%s%06ld", (posicion-2), buffer, posicion);
		   }

		   veces++;

	   }	// FIN IF CTRL-L
   }	// FIN FOR

   fclose(doc);
   fclose(idx); 

   return TRUE;
}