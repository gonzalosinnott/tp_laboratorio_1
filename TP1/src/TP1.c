/*
 ============================================================================
 Name        : TP1.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   : 
 Description : Hacer una calculadora.
 Para ello el programa iniciará y contará con un menú de opciones:
 1. Ingresar 1er operando (A=x)
 2. Ingresar 2do operando (B=y)

 3. Calcular todas las operaciones
 a) Calcular la suma (A+B)
 b) Calcular la resta (A-B)
 c) Calcular la division (A/B)
 d) Calcular la multiplicacion (A*B)
 e) Calcular el factorial (A!)

 4. Informar resultados
 a) “El resultado de A+B es: r”
 b) “El resultado de A-B es: r”
 c) “El resultado de A/B es: r” o “No es posible dividir por cero”
 d) “El resultado de A*B es: r”
 e) “El factorial de A es: r1 y El factorial de B es: r2”

 5. Salir

 • Todas las funciones matemáticas del menú se deberán realizar en una biblioteca
  aparte, que contenga las funciones para realizar las cinco operaciones.
 • En el menú deberán aparecer los valores actuales cargados en los operandos A y B
 • Deberán contemplarse los casos de error (división por cero, etc)
 • Documentar todas las funciones
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include "calculadora.h"
#include "utn.h"

#define TRUE 1
#define FALSE 0

int main(void)
{
	int opcionIngresada;
	float numeroUno;
	float numeroDos;
	int	ingresoNumeroUno = FALSE;
	int	ingresoNumeroDos = FALSE;
	int calculoOperaciones = FALSE;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoFactorialUno;
	int resultadoFactorialDos;
	int errorDivision = TRUE;
	int errorFactorialUno = TRUE;
	int errorFactorialDos = TRUE;
	char respuestaOtraOperacion;

	do
	{
		calculadora_getMainMenu(&opcionIngresada);
		switch(opcionIngresada)
		{
			case 1:
				if(calculadora_getNumber(&numeroUno) ==0)
				{
					ingresoNumeroUno = TRUE;
				}
				break;
			case 2:
				if(ingresoNumeroUno == TRUE)
				{
					if(calculadora_getNumber(&numeroDos) ==0)
					{
						ingresoNumeroDos = TRUE;
					}
				}
				else
				{
					printf("\nError, ingrese el primer numero.\n");
				}
				break;
			case 3:
				if(ingresoNumeroUno == TRUE && ingresoNumeroDos == TRUE)
				{
					getOperaciones(numeroUno, numeroDos, &resultadoSuma, &resultadoResta, &resultadoMultiplicacion, &resultadoDivision, &resultadoFactorialUno, &resultadoFactorialDos, &errorDivision, &errorFactorialUno, &errorFactorialDos);
					calculoOperaciones = TRUE;
				}
				else
				{
					printf("\nError, no se ingresaron ambos numeros.\n");
				}
				break;
			case 4:
				if(calculoOperaciones == TRUE)
				{
					printResultados(numeroUno, numeroDos, resultadoSuma, resultadoResta, resultadoMultiplicacion, resultadoDivision, resultadoFactorialUno, resultadoFactorialDos, errorDivision, errorFactorialUno, errorFactorialDos);
					do
					{
						printf("\n¿Desea realizar otra operacion? (y/n)\n");
						__fpurge(stdin);
						scanf("%c",&respuestaOtraOperacion);
					}while(respuestaOtraOperacion !='y' && respuestaOtraOperacion !='n');
					if(respuestaOtraOperacion=='n')
					{
						printf("\nPrograma terminado.");
						return EXIT_SUCCESS;
					}
					else
					{
						ingresoNumeroUno = FALSE;
						ingresoNumeroDos = FALSE;
						calculoOperaciones = FALSE;
						errorDivision = TRUE;
						errorFactorialUno = TRUE;
						errorFactorialDos = TRUE;
					}
				}
				else
				{
					printf("\nError, no se ingresaron numeros o no se hizo el calculo de operaciones.\n");
				}
				break;
			case 5:
				printf("\nPrograma terminado.");
				break;
		}
	}while(opcionIngresada != 5);
	return EXIT_SUCCESS;
}


