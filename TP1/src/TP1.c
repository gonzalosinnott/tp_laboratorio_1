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
	//Declaracion de variables
	float resultado;
	float numeroUno;
	float numeroDos;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;

	//Ingreso y validacion de datos
	if(utn_getFloat(&numeroUno,"\nIngrese un numero:", "\nError,", 3)==0)
	{
		if(utn_getFloat(&numeroDos,"\nIngrese un numero:", "\nError,", 3)==0)
		{
		//Funciones
			if(suma(numeroUno,numeroDos,&resultado) == 0)
			{
				resultadoSuma = resultado;
			}
			if(resta(numeroUno,numeroDos,&resultado) == 0)
			{
				resultadoResta = resultado;
			}
			if(multiplicacion(numeroUno,numeroDos,&resultado) == 0)
			{
				resultadoMultiplicacion = resultado;
			}

			printf("\nEl resultado de %.2f + %.2f es: %.2f",numeroUno, numeroDos, resultadoSuma);
			printf("\nEl resultado de %.2f - %.2f es: %.2f",numeroUno, numeroDos, resultadoResta);
			printf("\nEl resultado de %.2f * %.2f es: %.2f",numeroUno, numeroDos, resultadoMultiplicacion);

			if(division(numeroUno,numeroDos,&resultado) == 0)
			{
				printf("\nEl resultado de %.2f / %.2f es: %.2f", numeroUno, numeroDos, resultado);
			}
			else
			{
				printf("\nNo se puede dividir por 0.");
			}
			return EXIT_SUCCESS;
		}
	}
}
