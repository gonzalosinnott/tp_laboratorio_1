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
  (donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado)
 • Deberán contemplarse los casos de error (división por cero, etc)
 • Documentar todas las funciones
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include "utn.h"

int main(void)
{
	int opcionIngresada;
	int respuesta;
	float numeroUno;
	float numeroDos;
	float resultado;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	long long resultadoFactorialUno;
	long long resultadoFactorialDos;
	int	ingresoNumeroUno = 0;
	int	ingresoNumeroDos = 0;
	int resultadoOperaciones = 0;
	int divisionPorCero = 1;
	int factorialNegativoUno = 1;
	int factorialNegativoDos = 1;
	char respuestaOtraOperacion;

	do
	{
		respuesta = getEnteroConRango(&opcionIngresada, 1, 5, "\nIngrese una opcion:\n 1. Ingrese el primer numero\n 2. Ingrese el segundo numero\n 3. Calcular todas las operaciones\n 4. Informar resultados\n 5. Salir\n\nOpcion:", "\nError,", 3);
		if (respuesta == 0)
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
						if(getSuma(numeroUno,numeroDos,&resultado) == 0)
						{
							resultadoSuma = resultado;
						}
						if(getResta(numeroUno,numeroDos,&resultado) == 0)
						{
							resultadoResta = resultado;
						}
						if(getMultiplicacion(numeroUno,numeroDos,&resultado) == 0)
						{
							resultadoMultiplicacion = resultado;
						}
						if(getDivision(numeroUno,numeroDos,&resultado) == 0)
						{
							resultadoDivision = resultado;
							divisionPorCero = 0;
						}
						if(getFactorial(numeroUno, &resultado) == 0)
						{
							resultadoFactorialUno = resultado;
							factorialNegativoUno = 0;
						}
						if(getFactorial(numeroDos, &resultado) == 0)
						{
							resultadoFactorialDos = resultado;
							factorialNegativoDos = 0;
						}
						printf("\nCalculando...\n");
						resultadoOperaciones = 1;
					}
					else
					{
						printf("\nError, no se ingresaron ambos numeros.\n");
					}
					break;
				case 4:
					if(resultadoOperaciones == 1)
					{
						printf("\nEl resultado de %.2f + %.2f es: %.2f",numeroUno,numeroDos,resultadoSuma);
						printf("\nEl resultado de %.2f - %.2f es: %.2f",numeroUno,numeroDos,resultadoResta);
						printf("\nEl resultado de %.2f * %.2f es: %.2f",numeroUno,numeroDos,resultadoMultiplicacion);
						if(divisionPorCero == 0)
						{
							printf("\nEl resultado de la division es: %.2f", resultadoDivision);
						}
						else
						{
							printf("\nNo se puede dividir por 0.");
						}
						if(factorialNegativoUno == 0)
						{
							printf("\nEl factorial de %.2f es: %lld",numeroUno, resultadoFactorialUno);
						}
						else
						{
							printf("\nNo es posible calcular el factorial de %.2f porque es un numero negativo.",numeroUno);
						}
						if(factorialNegativoDos == 0)
						{
							printf("\nEl factorial de %.2f es: %lld\n",numeroDos, resultadoFactorialDos);
						}
						else
						{
							printf("\nNo es posible calcular el factorial de %.2f porque es un numero negativo.\n",numeroDos);
						}

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
	}while(opcionIngresada != 5);
	return EXIT_SUCCESS;
}

