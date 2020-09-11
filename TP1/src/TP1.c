/*
 ============================================================================
 Name        : TP1.c
 Author      : Gonzalo Sinnott
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
	int opcionOperacion;
	float numeroUno;
	float numeroDos;
	int	ingresoNumeroUno = 0;
	int	ingresoNumeroDos = 0;
	int calculoOperaciones = 0;
	float resultadoOperacion1;
	float resultadoOperacion2;
	int errorOperacion1 = 1;
	int errorOperacion2 = 1;
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
						if( getEnteroConRango(&opcionOperacion, 1, 5, "\nIngrese una opcion:\n 1. Sumar\n 2. Restar\n 3. Multiplicar\n 4. Dividir\n 5. Factorial\n\nOpcion:", "\nError, no es una opcion valida.", 3)==0)
						{
							getOperaciones(opcionOperacion, numeroUno, numeroDos, &resultadoOperacion1, &resultadoOperacion2, &errorOperacion1, &errorOperacion2);
							printf("\nCalculando...\n");
							calculoOperaciones = 1;
						}
					}
					else
					{
						printf("\nError, no se ingresaron ambos numeros.\n");
					}
					break;
				case 4:
					if(calculoOperaciones == 1)
					{
						printResultados(opcionOperacion, numeroUno, numeroDos, resultadoOperacion1, resultadoOperacion2, errorOperacion1, errorOperacion2);
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


