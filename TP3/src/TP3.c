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


#define PATHTXT "data.csv"
#define PATHBIN "data.bin"
#define PATHNEWTXT "dataNew.csv"
#define PATHNEWBIN "dataNew.bin"
#define LOADSUCCESS "\nREGISTRO DE EMPLEADOS CARGADO CON EXITO\n"
#define LOADERROR "\nERROR, CARGUE UN ARCHIVO PRIMERO\n"
#define SAVESUCCESS "\nREGISTRO DE EMPLEADOS GUARDADO CON EXITO\n"
#define TRUE 0
#define FALSE 1

int main()
{
    int choosenOption;
    int savedFile = FALSE;

    LinkedList* listaEmpleados = ll_newLinkedList();

    do
    {
    	utn_getMainMenu(&choosenOption);
        switch(choosenOption)
        {
            case 1: //Cargar los datos de los empleados desde el archivo (modo texto).
            	if(controller_loadFromText(PATHTXT, listaEmpleados) == 0)
				{
					printf(LOADSUCCESS);
				}
            	break;
            case 2://Cargar los datos de los empleados desde el archivo (modo binario).
				if(controller_loadFromBinary(PATHBIN, listaEmpleados) == 0)
				{
					printf(LOADSUCCESS);
				}
				break;



            case 6: //Listar empleados
				if(ll_isEmpty(listaEmpleados)==0)
				{
					controller_ListEmployee(listaEmpleados);
				}
				else
				{
					printf(LOADERROR);
				}
				break;

            case 8://Guardar los datos de los empleados en el archivo (modo texto).
				if(ll_isEmpty(listaEmpleados)==0 &&
				   controller_saveAsText(PATHNEWTXT, listaEmpleados)==0)
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
				if(ll_isEmpty(listaEmpleados)==0 &&
				   controller_saveAsBinary(PATHNEWBIN, listaEmpleados)==0)
				{
					printf(SAVESUCCESS);
					savedFile = TRUE;
				}
				else
				{
					printf(LOADERROR);
				}
				break;
        }
    }while(choosenOption != 10);
    return 0;
}
