/*
 ============================================================================
 Name        : mi_biblioteca.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header de la biblioteca mi_biblioteca.c - Created on: 3 sept. 2020
 ============================================================================
 */

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

int calculadora_getMainMenu(int* choosenOption);
int calculadora_getNumber(float* number);

int getSuma (float numeroUno, float numeroDos, float *resultado);
int getResta (float numeroUno, float numeroDos, float *resultado);
int getMultiplicacion (float numeroUno, float numeroDos, float *resultado);
int getDivision (float numeroUno, float numeroDos, float *resultado);
int getFactorial(float numero,float* resultado);

int getOperaciones(float numeroUno, float numeroDos, float* resultadoSuma, float* resultadoResta, float* resultadoMultiplicacion, float* resultadoDivision, int* resultadoFactorialUno, int* resultadoFactorialDos, int* errorDivision, int* errorFactorialUno, int* errorFactorialDos);
int printResultados(float numeroUno, float numeroDos, float resultadoSuma, float resultadoResta, float resultadoMultiplicacion, float resultadoDivision, int resultadoFactorialUno, int resultadoFactorialDos, int errorDivision, int errorFactorialUno, int errorFactorialDos);

#endif /* CALCULADORA_H_ */
