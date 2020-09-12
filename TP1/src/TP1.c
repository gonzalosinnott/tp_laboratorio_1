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
#include "mi_biblioteca.h"

int main(void)
{
	int opcionIngresada;
	float numeroUno;
	float numeroDos;
	int	ingresoNumeroUno = 0;
	int	ingresoNumeroDos = 0;
	int calculoOperaciones = 0;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoFactorialUno;
	int resultadoFactorialDos;
	int errorDivision = 1;
	int errorFactorialUno = 1;
	int errorFactorialDos = 1;
	char respuestaOtraOperacion;

	do
	{
		if(getEnteroConRango(&opcionIngresada, 1, 5, "\nIngrese una opcion:\n 1. Ingrese el primer numero\n 2. Ingrese el segundo numero\n 3. Elegir operacion a calcular.\n 4. Informar resultados\n 5. Salir\n\nOpcion:", "\nError, no es una opcion valida.", 3)==0)
		{
			switch(opcionIngresada)
			{
				case 1:
					if(getFloat(&numeroUno, "\nIngrese el primer numero:", "\nError, ", 3) ==0)
					{
						printf("Numero ingresado: %.2f\n",numeroUno);
						ingresoNumeroUno = 1;
					}
					break;
				case 2:
					if(ingresoNumeroUno == 1)
					{
						if(getFloat(&numeroDos, "\nIngrese el segundo numero:", "\nError, ", 3)== 0)
						{
							printf("Numero ingresado: %.2f\n",numeroDos);
							ingresoNumeroDos = 1;
						}
					}
					else
					{
						printf("\nError, ingrese el primer numero.\n");
					}
					break;
				case 3:
					if(ingresoNumeroUno == 1 && ingresoNumeroDos == 1)
					{
						getOperaciones(numeroUno, numeroDos, &resultadoSuma, &resultadoResta, &resultadoMultiplicacion, &resultadoDivision, &resultadoFactorialUno, &resultadoFactorialDos, &errorDivision, &errorFactorialUno, &errorFactorialDos);
						printf("\nCalculando...\n");
						calculoOperaciones = 1;
					}
					else
					{
						printf("\nError, no se ingresaron ambos numeros.\n");
					}
					break;
				case 4:
					if(calculoOperaciones == 1)
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
							ingresoNumeroUno = 0;
							ingresoNumeroDos = 0;
							calculoOperaciones = 0;
							errorDivision = 1;
							errorFactorialUno = 1;
							errorFactorialDos = 1;
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
		}
		else
		{
			printf("\nPrograma terminado.");
			break;
		}
	}while(opcionIngresada != 5);
	return EXIT_SUCCESS;
}


