/*
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Biblioteca utn.c - Created on: 3 sept. 2020
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * \brief getEntero : Pide al usuario un numero entero.
 * \param pValor: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param msg: El mensaje que imprime para pedir un valor
 * \param msgError: El mensaje que imprime si el rango no es valido
 * \param intentos: Intentos totales que quiero dejar al usuario ingresar un valor no valido.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getEntero(int* pValor, char* msj, char* msjError, int intentos)
{
	int retorno = -1;
	int num;
	int retornoScanf;

	if(pValor != NULL && msj != NULL && msjError != NULL)
	{
		do
		{
			printf("%s", msj);
			__fpurge(stdin);
			retornoScanf = scanf( "%d" ,&num);
			if(retornoScanf == 1)
			{
				*pValor = num;
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos");
				break;
			}
			printf("%s Te quedan %d reintentos.", msjError,intentos);
		}while(intentos > 0);
	}

	return retorno;
}

/*
 * \brief getEnteroConRango : Pide al usuario un numero entero dentor de un rango determinado.
 * \param pValor: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param min: Valor minimo valido (inclusive)
 * \param max: Valor maximo valido (inclusive)
 * \param msg: El mensaje que imprime para pedir un valor
 * \param msgError: El mensaje que imprime si el rango no es valido
 * \param intentos: Intentos totales que quiero dejar al usuario ingresar un valor no valido.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getEnteroConRango(int* pValor, int min, int max, char* msj, char* msjError, int intentos)
{
	int retorno = -1;
	int num;
	int retornoScanf;

	if(pValor != NULL && msj != NULL && msjError != NULL)
	{
		do
		{
			printf("%s", msj);
			__fpurge(stdin);
			retornoScanf = scanf( "%d" ,&num);
			if(retornoScanf == 1 && num >= min && num <= max)
			{
				*pValor = num;
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos");
				break;
			}
			printf("%s Te quedan %d reintentos.", msjError,intentos);
		}while(intentos > 0);
	}
	return retorno;
}

/*
 * \brief getFloat : Pide al usuario un numero con decimales.
 * \param pValor: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param msg: El mensaje que imprime para pedir un valor
 * \param msgError: El mensaje que imprime si el rango no es valido
 * \param intentos: Intentos totales que quiero dejar al usuario ingresar un valor no valido.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getFloat(float* pValor, char* msj, char* msjError, int intentos)
{
	int retorno = -1;
	float num;
	int retornoScanf;

	if(pValor != NULL && msj != NULL && msjError != NULL)
	{
		do
		{
			printf("%s", msj);
			__fpurge(stdin);
			retornoScanf = scanf( "%f" ,&num);
			if(retornoScanf == 1)
			{
				*pValor = num;
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos");
				break;
			}
			printf("%s te quedan %d reintentos.", msjError,intentos);
		}while(intentos > 0);
	}
	return retorno;
}

/*
 * \brief getFloatConRango : Pide al usuario un numero con decimales dentro de un rango determinado
 * \param pValor: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param min: Valor minimo valido (inclusive)
 * \param max: Valor maximo valido (inclusive)
 * \param msg: El mensaje que imprime para pedir un valor
 * \param msgError: El mensaje que imprime si el rango no es valido
 * \param intentos: Intentos totales que quiero dejar al usuario ingresar un valor no valido.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getFloatConRango(float* pValor, int min, int max, char* msj, char* msjError, int intentos)
{
	int retorno = -1;
	float num;
	int retornoScanf;

	if(pValor != NULL && msj != NULL && msjError != NULL)
	{
		do
		{
			printf("%s", msj);
			__fpurge(stdin);
			retornoScanf = scanf( "%f" ,&num);
			if(retornoScanf == 1 && num >= min && num <= max)
			{
				*pValor = num;
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos");
				break;
			}
			printf("%s Te quedan %d reintentos.", msjError,intentos);
		}while(intentos > 0);
	}
	return retorno;
}

/*
 * \brief getChar : Pide al usuario una letra.
 * \param pValor: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * \param msg: El mensaje que imprime para pedir un valor
 * \param msgError: El mensaje que imprime si el rango no es valido
 * \param intentos: Intentos totales que quiero dejar al usuario ingresar un valor no valido.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getChar(char* pValor,char* msj, char* msjError, int intentos)
{
	int retorno = -1;
	char letra;

	if(pValor != NULL && msj != NULL && msjError != NULL)
	{
		do
		{
			printf("%s", msj);
			__fpurge(stdin);
			scanf( "%c" ,&letra);
			if(isalpha(letra) != 0)
			{
				*pValor = letra;
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos");
				break;
			}
			printf("%s Te quedan %d reintentos.", msjError,intentos);
		}while(intentos > 0);
	}
	return retorno;
}

/*
 * \brief getSuma : suma dos numeros float previamente guardados.
 * \param numeroUno: primer variable de la suma.
 * \param numeroDos: segunda variable de la suma.
 * \param * resultado: Direccion de memoria de la variable donde escribe el valor de la suma.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getSuma (float numeroUno, float numeroDos, float* resultado)
{
	int retorno = -1;
	if(resultado != NULL)
	{
		*resultado = numeroUno + numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief getResta : resta dos numeros float previamente guardados.
 * \param numeroUno: primer variable de la resta.
 * \param numeroDos: segunda variable de la resta.
 * \param * resultado: Direccion de memoria de la variable donde escribe el valor de la resta.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getResta(float numeroUno, float numeroDos, float* resultado)
{
	int retorno = -1;
	if(resultado != NULL)
	{
		*resultado = numeroUno - numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief getMultiplicacion : multiplica dos numeros float previamente guardados.
 * \param numeroUno: primer variable de la multiplicacion.
 * \param numeroDos: segunda variable de la multiplicacion.
 * \param * resultado: Direccion de memoria de la variable donde escribe el valor de la multiplicacion.
 * \return retorno: 0: si esta OK. -1: Si hubo un error
 */

int getMultiplicacion(float numeroUno, float numeroDos, float* resultado)
{
	int retorno = -1;
	if(resultado != NULL)
	{
		*resultado = numeroUno * numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief getDivision : divide dos numeros float previamente guardados.
 * \param numeroUno: variable dividendo.
 * \param numeroDos: variable divisor.
 * \param * resultado: Direccion de memoria de la variable donde escribe el valor de la division.
 * \return retorno: 0: si esta OK. -1: Si hubo un error o se intento dividir por 0.
 */

int getDivision(float numeroUno, float numeroDos, float* resultado)
{
	int retorno = -1;
	if(resultado != NULL && numeroDos != 0)
	{
		*resultado = numeroUno / numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief getFactorial : devuelve el factorial de un numero float previamente guardado.
 * \param numero: variable a calcularle su factorial.
 * \param * resultado: Direccion de memoria de la variable donde escribe el valor del factorial.
 * \return retorno: 0: si esta OK. -1: Si hubo un error o se intento calcular el factorial de un numero negativo
 */

int getFactorial(float numero,float* resultado)
{
	int retorno = -1;

	int contador;
	int factorial = 1;

	if(resultado != NULL )
	{
		if(numero == 0)
		{
			*resultado = 1;
			retorno = 0;
		}
		if(numero > 0)
		{
			for (contador = 1;contador <= numero;contador++)
			{
				factorial = (float)factorial * contador;
			}
			*resultado = factorial;
			retorno = 0;
		}
	}
	return retorno;
}
