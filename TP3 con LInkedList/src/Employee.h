/*
============================================================================
Name        : Employee.h
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Header for Library Employee.c
============================================================================
*/
#include "LinkedList.h"
#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NOMBRE_LEN 500


typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    float sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* id,char* nombre,char* horasTrabajadas, char* sueldo);
void employee_delete();

int employee_setIdFromTxtFile(Employee* this,char* id);
int employee_setId(Employee* this, int id);
int employee_getId(Employee* this,int* id);
int employee_generateNewId(LinkedList* pArrayListEmployee);
int employee_findMaxId(LinkedList* pArrayListEmployee);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadasFromTxtFile(Employee* this,char* horasTrabajadas);
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldoFromTxtFile(Employee* this,char* sueldo);
int employee_setSueldo(Employee* this, float sueldo);
int employee_getSueldo(Employee* this,float* sueldo);

int employee_compareId (void* fieldOne, void* fieldTwo);
int employee_compareNombre(void* fieldOne, void* fieldTwo);
int employee_compareHorasTrabajadas (void* fieldOne, void* fieldTwo);
int employee_compareSueldo(void* fieldOne, void* fieldTwo);

#endif // employee_H_INCLUDED
