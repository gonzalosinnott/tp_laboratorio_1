/*
 ============================================================================
 Name        : TP2.c
 Author      : Gonzalo Sinnott
 Version     :
 Copyright   : 
 Description :Una empresa requiere un sistema para administrar su nómina de empleados.
 Se sabe que dicha nómina bajo ninguna circunstancia superara los 1000 empleados.

 El sistema deberá tener el siguiente menú de opciones:
 1. ALTAS: Se debe permitir ingresar un empleado calculando automáticamente el número
 de Id. El resto de los campos se le pedirá al usuario.
 2. MODIFICAR: Se ingresará el Número de Id, permitiendo modificar: o Nombre o Apellido
 o Salario o Sector
 3. BAJA: Se ingresará el Número de Id y se eliminará el empleado del sistema.
 4. INFORMAR:
 A. Listado de los empleados ordenados alfabéticamente por Apellido y Sector.
 B. Total y promedio de los salarios, y cuántos empleados superan el salario promedio.
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include "mi_biblioteca.h"
#include "ArrayEmployees.h"

#define TRUE 1
#define FALSE 0

int main(void){

	int choosenOption;
	int emptyIndex;
	int firstLoad = FALSE;

	sEmployee arrayEmployees[QTY_EMPLOYEES];

	initEmployees(arrayEmployees, QTY_EMPLOYEES);

	do
	{
		getEmployeeMenu(&choosenOption);
		switch(choosenOption)
		{
			case 1:
				//ALTA
				if(checkFirstEmptyIndex(arrayEmployees, QTY_EMPLOYEES, &emptyIndex)==0)
				{
					loadEmployeeData(arrayEmployees, QTY_EMPLOYEES, emptyIndex);
					firstLoad = TRUE;
				}
				else
				{
					printf("\nNO SE PUEDEN CARGAR MAS REGISTROS.\n");
				}
				break;
			case 2:
				//MODIFICAR
				if(firstLoad == TRUE)
				{
					   modifyEmployee(arrayEmployees, QTY_EMPLOYEES);
				}
				else
				{
					printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
				}
				break;
			case 3:
				//BAJA
				if(firstLoad == TRUE)
				{
					removeEmployee(arrayEmployees, QTY_EMPLOYEES, &firstLoad);
				}
				else
				{
					printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
				}
				break;
			case 4:
				//INFORME
				if(firstLoad == TRUE)
				{
					sortEmployees(arrayEmployees, QTY_EMPLOYEES);
				}
				else
				{
					printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
				}
				break;
		}
	}while(choosenOption!=5);
	printf("PROGRAMA TERMINADO");
	return EXIT_SUCCESS;
}
