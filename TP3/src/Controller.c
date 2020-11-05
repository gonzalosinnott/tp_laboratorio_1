#include <stdio_ext.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include "parser.h"
#include "Employee.h"
#include "utn.h"
#include "menu.h"


#define MODIFYERROR_MSJ "ERROR, EL CAMPO NO PUDO SER MODIFICADO"


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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
			printf("ERROR, NO SE PUDO CARGAR EL ARCHIVO");
		}
	}
	else
	{
		printf("ERROR, EL ARCHIVO NO EXISTE");
	}
	fclose(pArch);
	return output;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output = -1;
	FILE *pArch;

	controller_loadFromText("data.csv", pArrayListEmployee);
	controller_saveAsBinary("data.bin", pArrayListEmployee);

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
	}
	fclose(pArch);
	return output;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int output = -1;
    int len;
    int i;

    if(pArrayListEmployee != NULL)
    {
    	len = ll_len(pArrayListEmployee);
		printf("---------------------------------------------------------------");
    	printf("\n|  ID  |        NOMBRE        | HORAS TRABAJADAS |   SUELDO   |\n");
    	for(i=0;i<len;i++)
    	{
    		  printf("---------------------------------------------------------------");
    		output = controller_printSingleEmployee(pArrayListEmployee,i);
    	}
		printf("---------------------------------------------------------------");
    }
	return output;
}

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


/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
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

			pEmployee = (Employee*) ll_get(pArrayListEmployee, index);
			do
			{
				menu_getModifyMenu(&choosenOption);
				switch (choosenOption)
				{
					case 1:
						if (utn_getString("Ingrese nombre: ", "Error", bufferEmployee.nombre, 3, sizeof(bufferEmployee.nombre)) == 0)
						{
							employee_setNombre(pEmployee, bufferEmployee.nombre);

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
						}
						else
						{
							printf(MODIFYERROR_MSJ);
						}
						break;
				}
			} while (choosenOption != 4);
			output = 0;
		}
	}
	else
	{
		printf("ERROR INDICE INEXISTENTE");
	}
	return output;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}






/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}






