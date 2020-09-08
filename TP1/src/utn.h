/*
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header de la biblioteca utn.c - Created on: 3 sept. 2020
 ============================================================================
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getEntero(int* pNumero, char* msj, char* msjError, int reintentos);
int utn_getEnteroConRango(int* pValor, int min, int max, char* msj, char* msjError, int intentos);
int utn_getFloat(float* pValor, char* msj, char* msjError, int intentos);
int utn_getFloatConRango(float* pValor, int min, int max, char* msj, char* msjError, int intentos);
int utn_getChar(char* pValor,char* msj, char* msjError, int intentos);

int suma (float numeroUno, float numeroDos, float *resultado);
int resta (float numeroUno, float numeroDos, float *resultado);
int multiplicacion (float numeroUno, float numeroDos, float *resultado);
int division (float numeroUno, float numeroDos, float *resultado);
int factorial(float numero,float* resultado);


#endif /* UTN_H_ */
