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

int getEntero(int* pNumero, char* msj, char* msjError, int reintentos);
int getEnteroConRango(int* pValor, int min, int max, char* msj, char* msjError, int intentos);
int getFloat(float* pValor, char* msj, char* msjError, int intentos);
int getFloatConRango(float* pValor, int min, int max, char* msj, char* msjError, int intentos);
int getChar(char* pValor,char* msj, char* msjError, int intentos);

int getSuma (float numeroUno, float numeroDos, float *resultado);
int getResta (float numeroUno, float numeroDos, float *resultado);
int getMultiplicacion (float numeroUno, float numeroDos, float *resultado);
int getDivision (float numeroUno, float numeroDos, float *resultado);
int getFactorial(float numero,float* resultado);


#endif /* UTN_H_ */
