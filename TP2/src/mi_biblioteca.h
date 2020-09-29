/**
 ============================================================================
 Name        : mi_biblioteca.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for library mi_biblioteca.c
 ============================================================================
 */

#ifndef MI_BIBLIOTECA_H_
#define MI_BIBLIOTECA_H_

int utn_getIntNumber(char* msj, char* errorMsj, int* pValue,int retries,int max,int min);
int utn_getFloatNumber(char* msj, char* errorMsj, float* pValue,int retries, int max, int min);
int utn_getString(char* msj, char* errorMsj, char* pValue,int retries, int len);
int utn_getChar(char* msj,char* errorMsj,char* pValue,char valueOne,char valueTwo,int retries);

#endif /* MI_BIBLIOTECA_H_ */
