char *mid( char *szin, int pos, int size )
{
   static char sztmp[255];

   memcpy( sztmp, szin+pos, size );
   sztmp[size] = 0;

   return sztmp;
}

char *right(char *cadena, int offset)
{
cadena=mid(cadena,strlen(cadena)-offset ,offset);
return cadena; 
}

char *left(char *cadena, int offset)
{
cadena=mid(cadena, 0, offset);
return cadena; 
}

int busca_car(char *cadena, char *car)
{
	int i;

	for( i = 0;  i < (int)strlen(cadena); i++ )
	{
		if ( *(cadena+i) == *car )
		break;
	}

	return i;
}

char *borracoma( char *cadena )
{
   int i = busca_car(cadena, ";");
   return mid(cadena, 0, i);
}

int match(char *cadena, char *car, int pos)
{
	int i;

	for ( i = pos; i < (int)strlen(cadena); i++ )
	{
		if ( *(cadena+i) == *car )
		break;
	}
		return i;
}

int match2(char *cadena, char *car, int pos)
{
	int i;
	char temp[256];

	for(i=pos; i < (int)strlen(cadena); i++ )
	{
		if ( *(cadena+i) == *(car) )
			{
			strcpy(temp, mid(cadena, i, strlen(car)) );
			if ( strncmp(temp,car,strlen(car) ) == 0 )
				return i;
			}
		else continue;
	}
		return -1;

}
