/*
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Biblioteca mi_biblioteca.c - Created on: 3 sept. 2020
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include "calculadora.h"
#include "utn.h"

#define MAINMENU_HEADER "|          CALCULADORA          |"
#define MAINMENU_MSJ "\nIngrese una opcion:\n 1. Ingrese el primer numero\n 2. Ingrese el segundo numero\n 3. Realizar calculos.\n 4. Informar resultados\n 5. Salir\nOpcion:"
#define ERROR_MSJ "ERROR, INGRESE UNA OPCION VALIDA. "


/**
 * \brief menu_getMainMenu: Menu principal del programa
 * \param choosenOption* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int calculadora_getMainMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		printf("\n---------------------------------\n");
		printf(MAINMENU_HEADER);
		printf("\n---------------------------------\n");
		if(utn_getIntNumber(MAINMENU_MSJ,ERROR_MSJ, choosenOption, 3, 5, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 5;
		}
	}
	return output;
}

/**
 * \brief calculadora_getNumber: F(x) para obtener los numeros para realizar los calculos
 * \param number float*: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int calculadora_getNumber(float* number)
{
	int retorno = -1;
	float num;
	int intentos = 3;
	int retornoScanf;

	if(number != NULL)
	{
		do
		{
			printf("Ingrese un numero: \n");
			__fpurge(stdin);
			retornoScanf = scanf( "%f" ,&num);
			if(retornoScanf == 1)
			{
				*number = num;
				printf("Numero ingresado: %.2f\n",num);
				retorno = 0;
				break;
			}
			intentos--;
			if(intentos == 0)
			{
				printf("\nSe agotaron los intentos\n");
				break;
			}
			printf("Error, te quedan %d reintentos.",intentos);
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
 * \brief getFactorial : devuelve el factorial de un numero previamente guardado.
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
		if(numero == (int)numero)
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
	}
	return retorno;
}

/*
 * \brief getOperaciones: funcion para calcular operaciones
 * \param numeroUno: primer variable operacion.
 * \param numeroDos: segunda variable de la operacion.
 * \param resultadoSuma: Direccion de memoria de la variable donde escribe el resultado de la suma.
 * \param resultadoResta: Direccion de memoria de la variable donde escribe el resultado de la resta.
 * \param resultadoMultiplicacion: Direccion de memoria de la variable donde escribe el resultado de la multiplicacion.
 * \param resultadoDivision: Direccion de memoria de la variable donde escribe el resultado de la division.
 * \param resultadoFactorialUno: Direccion de memoria de la variable donde escribe el resultado del factorial del primer numero.
 * \param resultadoFactorialDos: Direccion de memoria de la variable donde escribe el resultado del factorial del segundo numero.
 * \param errorDivision: Direccion de memoria de la variable donde escribe la validacion de que la operacion se puede realizar.
 * \param errorFactorialUno:Direccion de memoria de la variable donde escribe la validacion de que la operacion se puede realizar.
 * \param errorFactorialDos:Direccion de memoria de la variable donde escribe la validacion de que la operacion se puede realizar.
 * \return retorno: 0: si esta OK. -1: Si hubo un error o se intento calcular el factorial de un numero negativo
 */

int getOperaciones(float numeroUno, float numeroDos, float* resultadoSuma, float* resultadoResta, float* resultadoMultiplicacion, float* resultadoDivision, int* resultadoFactorialUno, int* resultadoFactorialDos, int* errorDivision, int* errorFactorialUno, int* errorFactorialDos)
{
	int retorno = -1;
	float resultado;

	if(resultadoSuma !=NULL && resultadoResta !=NULL && resultadoMultiplicacion !=NULL && resultadoDivision !=NULL && resultadoFactorialUno !=NULL && resultadoFactorialDos !=NULL && errorDivision !=NULL && errorFactorialUno !=NULL && errorFactorialDos !=NULL)
	{
		if(getSuma(numeroUno,numeroDos,&resultado) == 0)
		{
			*resultadoSuma = resultado;
		}
		if(getResta(numeroUno,numeroDos,&resultado) == 0)
		{
			*resultadoResta = resultado;
		}
		if(getMultiplicacion(numeroUno,numeroDos,&resultado) == 0)
		{
			*resultadoMultiplicacion = resultado;
		}
		if(getDivision(numeroUno,numeroDos,&resultado) == 0)
		{
			*resultadoDivision = resultado;
			*errorDivision = 0;
		}
		if(getFactorial(numeroUno, &resultado) == 0)
		{
			*resultadoFactorialUno = resultado;
			*errorFactorialUno = 0;
		}
		if(getFactorial(numeroDos, &resultado) == 0)
		{
			*resultadoFactorialDos = resultado;
			*errorFactorialDos = 0;
		}
		retorno = 0;
		printf("\nCalculando...\n");
	}
	return retorno;
}

/*
 * \brief printResultados: funcion para devolver por consola el resultado de las operaciones.
 * \param numeroUno: primer variable operacion.
 * \param numeroDos: segunda variable de la operacion.
 * \param resultadoSuma: resultado de la suma.
 * \param resultadoResta: resultado de la resta.
 * \param resultadoMultiplicacion: resultado de la multiplicacion.
 * \param resultadoDivision: resultado de la division.
 * \param resultadoFactorialUno: resultado del factorial del primer numero.
 * \param resultadoFactorialDos: resultado del factorial del segundo numero.
 * \param errorDivision: validacion de que la operacion se puede realizar.
 * \param errorFactorialUno:validacion de que la operacion se puede realizar.
 * \param errorFactorialDos:validacion de que la operacion se puede realizar.
 * \return retorno: 0: si esta OK. -1: Si hubo un error o se intento calcular el factorial de un numero negativo
 */

int printResultados(float numeroUno, float numeroDos, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion, float resultadoDivision, int resultadoFactorialUno, int resultadoFactorialDos, int errorDivision, int errorFactorialUno, int errorFactorialDos)
{
	int retorno = -1;

	printf("\nEl resultado de %.2f + %.2f es: %.2f",numeroUno,numeroDos,resultadoSuma);
	printf("\nEl resultado de %.2f - %.2f es: %.2f",numeroUno,numeroDos,resultadoResta);
	printf("\nEl resultado de %.2f * %.2f es: %.2f",numeroUno,numeroDos,resultadoMultiplicacion);
	if(errorDivision == 0)
	{
		printf("\nEl resultado de la division es: %.2f", resultadoDivision);
	}
	else
	{
		printf("\nNo se puede dividir por 0.");
	}
	if(errorFactorialUno == 0)
	{
		printf("\nEl factorial de %.2f es: %.d",numeroUno, resultadoFactorialUno);
	}
	else
	{
		printf("\nNo es posible calcular el factorial de %.2f.",numeroUno);
	}
	if(errorFactorialDos == 0)
	{
		printf("\nEl factorial de %.2f es: %.d\n",numeroDos, resultadoFactorialDos);
	}
	else
	{
		printf("\nNo es posible calcular el factorial de %.2f.\n",numeroDos);
	}
	retorno = 0;
	return retorno;
}
