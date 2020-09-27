 /*
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library mi_biblioteca.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_STRING_LEN 1000

static int utn_checkString(char* string,int len);
static int myGets(char *string, int len);


/**
 * \brief utn_getInt: Asks the user for an int value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int max: max value admitted
 * \param int min: min value admitted
 * \return (-1) Error / (0) Ok
 */

int utn_getInt(char* msj, char* errorMsj, int* pValue,int retries,int max,int min)
{
	int retorno = -1;
	int bufferInt;
	int resultadoScanf;

	if(msj != NULL && errorMsj != NULL && pValue != NULL &&	retries >= 0 && max >= min)
	{
		do
		{
			printf("%s",msj);
			__fpurge(stdin);
			resultadoScanf = scanf("%d" , &bufferInt);
			if(resultadoScanf == 1 && bufferInt >= min && bufferInt <= max)
			{
				*pValue = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos\n",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return retorno;
}

/**
 * \brief utn_getFloat: Asks the user for a float value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \return (-1) Error / (0) Ok
 */

int utn_getFloat(char* msj, char* errorMsj, float* pValue,int retries)
{
	int retorno = -1;
	float bufferFloat;
	int resultadoScanf;

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0)
	{
		do
		{
			printf("%s",msj);
			__fpurge(stdin);
			resultadoScanf = scanf("%f" , &bufferFloat);
			if(resultadoScanf == 1 && pValue >0)
			{
				retorno = 0;
				*pValue = bufferFloat;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return retorno;
}

/**
 * \brief utn_getString Asks the user for an string value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int len: lenght allowed for the value entered.
 * \return (-1) Error / (0) Ok
 */

int utn_getString(char* msj, char* errorMsj, char* pValue,int retries, int len)
{
	char bufferString[BUFFER_STRING_LEN];
	int retorno = -1;

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && len > 0)
	{
		do
		{
			printf("%s",msj);
			if( myGets(bufferString,BUFFER_STRING_LEN) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= len &&
				utn_checkString(bufferString,len) == 0 )
			{
				strncpy(pValue,bufferString,len);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos\n",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return retorno;
}

/**
 * \brief checkString: Checks the string for invalid characters
 * Allows upper and lower case letters and spaces
 * \param char* string: Pointer to string to check
 * \param int len: max lenght allowed of the string
 * \return (-1) Error / (0) Ok
 */

static int utn_checkString(char* string,int len)
{
	int retorno = 0; // TODOOK

	for(int i=0; i<=len && string[i] != '\0';i++)
	{
		if(	(string[i] < 'A' || string[i] > 'Z') &&
			(string[i] < 'a' || string[i] > 'z') &&
			 string[i] != ' ')
		{
			retorno = -1;
			break;
		}
	}
	return retorno;
}

/**
 * \brief myGets: Reads from stdin until a '\n' (finalization character)
 *  or until it has copied a string of a length of lenght - 1 characters .
 * \param char *string: Pointer to memory space where string will be copied
 * \param int len: String lenght
 * \return (-1) Error / (0) Ok
 */

static int myGets(char *string, int len)
{
	__fpurge(stdin);
	fgets (string, len, stdin);
	string[strlen (string) - 1] = '\0';
	return 0;
}

/**
 * \brief utn_getChar : Ask the user to choose between two letters
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param char valueOne: Option one
 * \param char valueTwo: Option two
 * \param int retries: amount of retries permitted
 * \return (-1) Error / (0) Ok
 */

int utn_getChar(char* msj,char* errorMsj,char* pValue,char valueOne,char valueTwo,int retries)
{
	int retorno = -1;
	char bufferChar;
	int resultadoScan;

	if(msj != NULL && errorMsj != NULL &&  pValue != NULL && retries > 0)
	{
		do{
			printf("%s", msj);
			__fpurge(stdin);
			resultadoScan = scanf("%c",&bufferChar);
			if(resultadoScan == 1 && (bufferChar == valueOne || bufferChar == valueTwo))
			{
				*pValue = bufferChar;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s Te quedan %d reintentos.\n", errorMsj,retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return retorno;
}

