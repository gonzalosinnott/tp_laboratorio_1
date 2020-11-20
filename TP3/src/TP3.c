/*
============================================================================
Name        : TP3.c
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : TP 3 Programacion - Laboratorio I

Una empresa requiere una aplicación que le permita administrar su nomina de empleados,
para lo cual se deberá desarrollar una solución implementando la biblioteca LinkedList.
Se deberá modelar la entidad que representa un empleado con todos sus datos asociados
de tal  manera que la misma permita interactuar con las estructuras de datos almacenadas
en los archivos.

	Menu:
	1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
	2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
	3. Alta de empleado
	4. Modificar datos de empleado
	5. Baja de empleado
	6. Listar empleados
	7. Ordenar empleados
	8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
	9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
	10. Salir
============================================================================
*/

#include <stdio_ext.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#include "menu.h"

#define PATHTXT "data.csv"
#define PATHBIN "data.bin"
#define PATHBACKUPTXT "databackup.csv"
#define PATHBACKUPBIN "databackup.bin"
#define LOADSUCCESS "\nREGISTRO DE EMPLEADOS CARGADO CON EXITO\n"
#define FILEFORMATERROR "\nERROR, EN EL FORMATO DE LOS DATOS DEL ARCHIVO\n"
#define OVERLOADERROR "\nERROR, YA EXISTE UN ARCHIVO CARGADO\n"
#define LOADERROR "\nERROR, CARGUE UN ARCHIVO PRIMERO\n"
#define SAVESUCCESS "\nREGISTRO DE EMPLEADOS GUARDADO CON EXITO\n"
#define ADDSUCCESS "\nREGISTRO DE EMPLEADO CARGADO CON EXITO\n"
#define MODIFYSUCCESS "\nREGISTRO DE EMPLEADO MODIFICADO CON EXITO\n"
#define REMOVESUCCESS "\nREGISTRO DE EMPLEADO ELIMINADO CON EXITO\n"
#define SORTSUCCESS "\nREGISTRO DE EMPLEADO ORDENADO CON EXITO\n"
#define EXITWARNING "\nCUIDADO, ESTA POR SALIR DEL PROGRAMA SIN GUARDAR LOS CAMBIOS REALIZADOS\n"

#define TRUE 1
#define FALSE 0

int main()
{
    int choosenOption;
    int fileLoaded = FALSE;
    int savedFile = FALSE;

    LinkedList* employeesList = ll_newLinkedList();

    do
    {
    	menu_getMainMenu(&choosenOption);
        switch(choosenOption)
        {
            case 1: //Cargar los datos de los empleados desde el archivo (modo texto).
            	if(fileLoaded == FALSE)
				{
            		if(controller_loadFromText(PATHTXT, employeesList) == 0)
            		{
            			controller_saveAsText(PATHBACKUPTXT, employeesList);
						printf(LOADSUCCESS);
						fileLoaded = TRUE;
            		}
            		else
					{
						printf(FILEFORMATERROR);
						choosenOption = 10;
					}
        		}
            	else
            	{
            		printf(OVERLOADERROR);
            	}
            	break;
            case 2://Cargar los datos de los empleados desde el archivo (modo binario).
            	if(fileLoaded == FALSE)
            	{
					if(controller_loadFromBinary(PATHBIN, employeesList) == 0)
					{
						controller_saveAsBinary(PATHBACKUPBIN, employeesList);
						printf(LOADSUCCESS);
						fileLoaded = TRUE;
					}
					else
					{
						printf(FILEFORMATERROR);
						choosenOption = 10;
					}
            	}
				else
				{
					printf(OVERLOADERROR);
				}
				break;
            case 3: //Alta de empleado
				if(ll_isEmpty(employeesList)==0)
				{
					if(controller_addEmployee(employeesList)==0)
					{
						printf(ADDSUCCESS);
					}
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 4://Modificar datos de empleado
				if(ll_isEmpty(employeesList)==0)
				{
					if(controller_editEmployee(employeesList)==0)
					{
						printf(MODIFYSUCCESS);
					}
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 5://Baja de empleado
				if(ll_isEmpty(employeesList)==0)
				{
					if(controller_removeEmployee(employeesList)==0)
					{
						printf(REMOVESUCCESS);
					}
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 6: //Listar empleados
				if(ll_isEmpty(employeesList)==0)
				{
					controller_ListEmployee(employeesList);
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 7: //Ordenar empleados
				if(ll_isEmpty(employeesList)==0 &&
				   controller_sortEmployee(employeesList)==0)
				{
						printf(SORTSUCCESS);

				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 8://Guardar los datos de los empleados en el archivo (modo texto).
				if(ll_isEmpty(employeesList)==0 &&
				   controller_saveAsText(PATHTXT, employeesList)==0)
				{
					printf(SAVESUCCESS);
					savedFile = TRUE;
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 9://Guardar los datos de los empleados en el archivo (modo binario).
				if(ll_isEmpty(employeesList)==0 &&
				   controller_saveAsBinary(PATHBIN, employeesList)==0)
				{
					printf(SAVESUCCESS);
					savedFile = TRUE;
				}
				else
				{
					printf(LOADERROR);
				}
				break;
            case 10://Guardar los datos de los empleados en el archivo (modo binario).
				if(fileLoaded == TRUE && savedFile == FALSE)
				{
					printf(EXITWARNING);
					menu_exitMenu(&choosenOption);
				}
				break;
        }
    }while(choosenOption != 10);
    ll_clear(employeesList);
	ll_deleteLinkedList(employeesList);
	printf("\nPROGRAMA TERMINADO\n");
    return 0;
}
