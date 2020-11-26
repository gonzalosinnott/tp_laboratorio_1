/*
============================================================================
Name        : Controller.C
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Library Controller.c
============================================================================
*/

#include <stdio_ext.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include "parser.h"
#include "Employee.h"
#include "utn.h"
#include "menu.h"

#define PATHTXT "data.csv"
#define PATHBIN "data.bin"
#define MODIFYERROR_MSJ "ERROR, EL CAMPO NO PUDO SER MODIFICADO"


/*
 * \brief controller_saveAsText:Guarda los datos de los empleados en el archivo data.csv (modo texto).
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int output = -1;
	FILE *pArch;
	if (path != NULL && pArrayListEmployee != NULL)
	{
		pArch = fopen(path, "w");
		if (pArch != NULL)
		{
			output = parser_EmployeeToText(pArch, pArrayListEmployee);
		}
		else
		{
			printf("\nERROR, NO SE PUDO GUARDAR EL ARCHIVO\n");
		}

	}
	fclose(pArch);
	return output;
}

/*
 * \brief controller_loadFromText: Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
	int output = -1;
	FILE *pArch;

	ll_clear(pArrayListEmployee);

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pArch = fopen(path, "r");
		if (pArch != NULL)
		{
			output = parser_EmployeeFromText(pArch, pArrayListEmployee);
		}
		else
		{
			printf("ERROR, EL ARCHIVO NO EXISTE");
		}
	}
	fclose(pArch);
	return output;
}

/*
 * \brief controller_saveAsBinary: Guarda los datos de los empleados en el archivo data.csv (modo binario).
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output = -1;
	FILE *pArch;

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pArch = fopen(path, "wb");
		if (pArch != NULL)
		{
			output = parser_EmployeeToBinary(pArch, pArrayListEmployee);
		}
		else
		{
			printf("\nERROR, NO SE PUDO GUARDAR.\n");
		}
	}
	fclose(pArch);
	return output;
}

/*
 * \brief controller_loadFromBinary: Carga los datos de los empleados desde el archivo data.csv (modo binario).
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output = -1;
	FILE *pArch;

	ll_clear(pArrayListEmployee);

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pArch = fopen(path, "rb");
		if (pArch != NULL)
		{
			output = parser_EmployeeFromBinary(pArch, pArrayListEmployee);
		}
		else
		{
			printf("ERROR, NO SE PUDO CARGAR EL ARCHIVO");
		}
		fclose(pArch);
	}

	return output;
}

/*
 * \brief controller_addEmployee: Alta de empleados
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee* pEmployee;
	Employee bufferEmployee;

	if (pArrayListEmployee != NULL)
	{
		pEmployee = employee_new();
		if(pEmployee != NULL &&
		   utn_getString("Ingrese nombre: ", "Error", bufferEmployee.nombre, 3, sizeof(bufferEmployee.nombre)) == 0 &&
		   utn_getIntNumber("Ingrese horas trabajadas: ", "Error", &bufferEmployee.horasTrabajadas, 3,INT_MAX ,1) == 0 &&
		   utn_getFloatNumber("Ingrese sueldo: ", "Error", &bufferEmployee.sueldo, 3, INT_MAX, 1) == 0)
		{
			bufferEmployee.id = employee_generateNewId(pArrayListEmployee);
			if (bufferEmployee.id > 0 &&
			    employee_setNombre(pEmployee, bufferEmployee.nombre) == 0 &&
				employee_setHorasTrabajadas(pEmployee, bufferEmployee.horasTrabajadas) == 0	&&
				employee_setSueldo(pEmployee, bufferEmployee.sueldo) == 0 &&
				employee_setId(pEmployee,bufferEmployee.id) == 0)
			{
				output = ll_add(pArrayListEmployee, pEmployee);
			}
			else
			{
				printf("ERROR, NO SE PUDO CARGAR EL EMPLEADO");
				employee_delete(pEmployee);
			}
		}
	}
	return output;
}

/*
 * \brief controller_printSingleEmployee: Imprime un empleado a partir de su indice
 * \param path char*: ruta del archivo a cargar
 * \param index int: indice a imprimir
 * \return (-1) Error / (0) Ok
 */

int controller_printSingleEmployee(LinkedList* pArrayListEmployee, int index)
{
	int output = -1;
	Employee* pEmployee;
	Employee bufferEmployee;

	if(pArrayListEmployee != NULL && index >= 0)
	{
		pEmployee = (Employee*)ll_get(pArrayListEmployee,index);
		if(	pEmployee != NULL &&
			employee_getId(pEmployee, &bufferEmployee.id) == 0 &&
			employee_getNombre(pEmployee, bufferEmployee.nombre) == 0 &&
			employee_getHorasTrabajadas(pEmployee, &bufferEmployee.horasTrabajadas) == 0 &&
			employee_getSueldo(pEmployee, &bufferEmployee.sueldo) == 0)
		{
			printf("\n| %-4d | %-20s | %-16d | %-11.2f|\n",
					bufferEmployee.id,
					bufferEmployee.nombre,
					bufferEmployee.horasTrabajadas,
					bufferEmployee.sueldo);
			output = 0;
		}
	}
	return output;
}


int controller_printSingleWithMap(void* pEmployee)
{
	int output = -1;
	Employee* bufferEmployee;
	bufferEmployee = (Employee*) pEmployee;

	int bufferId;
	char bufferNombre[NOMBRE_LEN];
	int bufferHorasTrabajadas;
	float bufferSueldo;

	if(bufferEmployee != NULL &&
	   employee_getId(bufferEmployee, &bufferId) ==0 &&
	   employee_getNombre(bufferEmployee, bufferNombre) ==0 &&
	   employee_getHorasTrabajadas(bufferEmployee, &bufferHorasTrabajadas) ==0 &&
	   employee_getSueldo(bufferEmployee, &bufferSueldo)==0 )
	{

		printf("\n| %-4d | %-20s | %-16d | %-11.2f|\n",
				bufferId,
				bufferNombre,
				bufferHorasTrabajadas,
				bufferSueldo);
		printf("---------------------------------------------------------------");
		output = 0;

	}
	return output;
}

/** \brief controller_ListEmployee: Imprime la lista de empleados
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int output = -1;

    if(pArrayListEmployee != NULL)
    {
		printf("---------------------------------------------------------------");
    	printf("\n|  ID  |        NOMBRE        | HORAS TRABAJADAS |   SUELDO   |\n");
		printf("---------------------------------------------------------------");
   		output = ll_map(pArrayListEmployee, controller_printSingleWithMap);
    }
	return output;
}

/*
 * \brief controller_findIndexById: Devuelve el indice del empleado a partir del ID
 * \param path char*: ruta del archivo a cargar
 * \param id int: Id a partir del cual se busca el indice
 * \return (-1) Error / (i) Ok
 */

int controller_findIndexById(LinkedList* pArrayListEmployee, int id)
{
	int output = -1;
	int i;
	int bufferId;
	int len;
	Employee* pEmployee;

	if (pArrayListEmployee != NULL && id > 0)
	{
		len = ll_len(pArrayListEmployee);
		for (i = 0; i < len; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee,i);
			if (pEmployee != NULL &&
				employee_getId(pEmployee, &bufferId) == 0 &&
				bufferId == id)
			{
				output = i;
				break;
			}
		}
	}
	return output;
}


/*
 * \brief controller_editEmployee: Modificar datos de empleado
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (i) Ok
 */

int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee* pEmployee;
	Employee bufferEmployee;
	int index = -1;
	int choosenOption;

	if (pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getIntNumber("\nIngrese el id del empleado que quiere modificar: ", "\nID INEXISTENTE. , ", &bufferEmployee.id, 3,employee_findMaxId(pArrayListEmployee), 1)==0)
		{
			index = controller_findIndexById(pArrayListEmployee, bufferEmployee.id);
			printf("---------------------------------------------------------------");
			printf("\n|                     EMPLEADO A MODIFICAR                    |\n");
			printf("---------------------------------------------------------------");
			printf("\n|  ID  |        NOMBRE        | HORAS TRABAJADAS |   SUELDO   |\n");
			printf("---------------------------------------------------------------");
			controller_printSingleEmployee(pArrayListEmployee, index);
			printf("---------------------------------------------------------------");

			pEmployee = (Employee*)ll_get(pArrayListEmployee, index);
			do
			{
				menu_getModifyMenu(&choosenOption);
				switch (choosenOption)
				{
					case 1:
						if (utn_getString("Ingrese nombre: ", "Error", bufferEmployee.nombre, 3, sizeof(bufferEmployee.nombre)) == 0)
						{
							employee_setNombre(pEmployee, bufferEmployee.nombre);
							output = 0;
						}
						else
						{
							printf(MODIFYERROR_MSJ);
						}
						break;
					case 2:
						if (utn_getIntNumber("Ingrese horas trabajadas: ", "Error", &bufferEmployee.horasTrabajadas, 3,INT_MAX ,1) == 0)
						{
							employee_setHorasTrabajadas(pEmployee, bufferEmployee.horasTrabajadas);
							output = 0;
						}
						else
						{
							printf(MODIFYERROR_MSJ);
						}
						break;
					case 3:
						if(utn_getFloatNumber("Ingrese sueldo: ", "Error", &bufferEmployee.sueldo, 3, INT_MAX, 1) == 0)

						{
							employee_setSueldo(pEmployee, bufferEmployee.sueldo);
							output = 0;
						}
						else
						{
							printf(MODIFYERROR_MSJ);
						}
						break;
				}
			} while (choosenOption != 4);
			ll_set(pArrayListEmployee, index, pEmployee);
		}
		else
		{
			printf("\nERROR ID INEXISTENTE\n");
		}
	}
	return output;
}

/*
 * \brief controller_removeEmployee: Baja de empleado
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee* pEmployee;
	Employee bufferEmployee;
	int index = -1;
	int choosenOption;

	if (pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		if(utn_getIntNumber("\nIngrese el id del empleado que quiere eliminar: ", "\nID INEXISTENTE. , ", &bufferEmployee.id, 3,employee_findMaxId(pArrayListEmployee), 1)==0)
		{
			index = controller_findIndexById(pArrayListEmployee, bufferEmployee.id);
			printf("---------------------------------------------------------------");
			printf("\n|                     EMPLEADO A ELIMINAR                    |\n");
			printf("---------------------------------------------------------------");
			printf("\n|  ID  |        NOMBRE        | HORAS TRABAJADAS |   SUELDO   |\n");
			printf("---------------------------------------------------------------");
			controller_printSingleEmployee(pArrayListEmployee, index);
			printf("---------------------------------------------------------------");

			pEmployee = (Employee*) ll_get(pArrayListEmployee, index);
			utn_getIntNumber("\n¿Desea eliminar el siguiente registro?\n 1-SI\n 2-NO\nOpcion:", "ERROR INGRESE UNA OPCION VALIDA", &choosenOption, 3, 2, 1);
			if(choosenOption==1)
			{
				employee_delete(pEmployee);
				output = ll_remove(pArrayListEmployee,index);
				output = 0;
			}
			else
			{
				printf("\nEL EMPLEADO NO FUE ELIMINADO.\n");
			}
		}
		else
		{
			printf("\nERROR ID INEXISTENTE\n");
		}
	}
	return output;
}

/*
 * \brief controller_sortEmployee: Ordenar empleados
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int output = -1;
	int choosenOption;
	int choosenOrder;

	if (pArrayListEmployee != NULL)
	{
		if(menu_getSortMenu(&choosenOption,&choosenOrder)==0)
		{
			switch (choosenOption)
			{
				case 1:
					output = ll_sort(pArrayListEmployee, employee_compareId,choosenOrder);
					break;
				case 2:
					output = ll_sort(pArrayListEmployee, employee_compareNombre,choosenOrder);
					break;
				case 3:
					output = ll_sort(pArrayListEmployee, employee_compareHorasTrabajadas,choosenOrder);
					break;
				case 4:
					output = ll_sort(pArrayListEmployee, employee_compareSueldo,choosenOrder);
					break;
				case 5:
					output = 0;
					break;
			}
		}
	}
	return output;
}






