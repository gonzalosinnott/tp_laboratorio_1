#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "menu.h"
#include "utn.h"


#define MAINMENU_HEADER "|                               REGISTRO DE EMPLEADOS                          |\n"
#define MAINMENU_MSJ "\nIngrese una opción:\n 1. Cargar los datos de los empleados desde el archivo(modo texto).\n 2. Cargar los datos de los empleados desde el archivo (modo binario).\n 3. Alta de empleado.\n 4. Modificar datos de empleado.\n 5. Baja de empleado.\n 6. Listar empleados.\n 7. Ordenar empleados.\n 8. Guardar los datos de los empleados en el archivo (modo texto).\n 9. Guardar los datos de los empleados en el archivo (modo binario).\n 10. Salir.\nOpcion:"
#define MODIFYMENU_MSJ "\nIngrese campo a modificar: \n 1.Nombre: \n 2.Horas trabajadas: \n 3.Sueldo: \n 4.Volver al menu principal\nOpcion: "
#define ERROR_MSJ "ERROR, INGRESE UNA OPCION VALIDA. "

int menu_getMainMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		printf("\n--------------------------------------------------------------------------------\n");
		printf(MAINMENU_HEADER);
		printf("--------------------------------------------------------------------------------\n");
		if(utn_getIntNumber(MAINMENU_MSJ,ERROR_MSJ, choosenOption, 3, 10, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 10;
		}
	}
	return output;
}

int menu_getModifyMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		if(utn_getIntNumber(MODIFYMENU_MSJ,ERROR_MSJ, choosenOption, 3, 4, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 4;
		}
	}
	return output;
}


