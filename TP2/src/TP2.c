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
	int idToSearch;
	int indexToModify;

	Employee arrayEmployees[QTY_EMPLOYEES];

	initEmployees(arrayEmployees, QTY_EMPLOYEES);
	do
	{
		utn_getInt("\nIngrese una opcion:"
				   "\n 1-Alta de empleado."
			       "\n 2-Modificar datos de empleado."
				   "\n 3-Baja de empleado."
			       "\n 4-Informe de personal."
				   "\n 5-Salir"
				   "\nOpcion:", "\nError.", &choosenOption, 3, 5, 1);
		switch(choosenOption)
		{
			case 1:
				//ALTA (FUNCIONA)
				if(checkFirstEmptyIndex(arrayEmployees, QTY_EMPLOYEES, &emptyIndex)==0)
				{
					if(loadEmployeeData(arrayEmployees, QTY_EMPLOYEES, emptyIndex)==0)
					{
						firstLoad = TRUE;
					}
				}
				else
				{
					printf("\nNO SE PUEDEN CARGAR MAS REGISTROS.\n");
				}
				break;
			case 2:
				//MODIFICAR(FUNCIONA)
				if(firstLoad == TRUE)
				{
					if(utn_getInt("Ingrese el ID a modificar:","Error. ",&idToSearch,3,1000,1)==0 &&
					   findEmployeeById(arrayEmployees, QTY_EMPLOYEES, &indexToModify, idToSearch)==0)
					{
					   modifyEmployee(arrayEmployees, QTY_EMPLOYEES, indexToModify, idToSearch);
					}
				}
				else
				{
					printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
				}
				break;
			case 3:
				//BAJA(FUNCIONA)
				if(firstLoad == TRUE)
				{
					if(utn_getInt("Ingrese el ID a eliminar:","Error. ",&idToSearch,3,1000,1)==0 &&
					   findEmployeeById(arrayEmployees, QTY_EMPLOYEES, &indexToModify, idToSearch)==0)
					{
					   removeEmployee(arrayEmployees, QTY_EMPLOYEES, indexToModify, idToSearch);
					}
				}
				else
				{
					printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
				}
				break;
			case 4:
				//INFORME (FUNCIONA IMPRIMIR, FALTA SORT)
				if(firstLoad == TRUE)
				{
					printEmployees(arrayEmployees, QTY_EMPLOYEES);
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
