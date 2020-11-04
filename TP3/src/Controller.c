#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "Employee.h"


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
			output = -1;
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

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pArch = fopen(path, "rb");
		if (pArch != NULL)
		{
			output = parser_EmployeeFromBinary(pArch, pArrayListEmployee);
		}
		else
		{
			output = -2; //couldn't open the file
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
    return 1;
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
    return 1;
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



int controller_printSingleEmployee(LinkedList* pArrayListEmployee, int index)
{
	int output = -1;
	Employee buffer;
	Employee* pEmployee;

	if(pArrayListEmployee != NULL && index >= 0)
	{
		pEmployee = (Employee*)ll_get(pArrayListEmployee,index);
		if(	pEmployee != NULL &&
			employee_getId(pEmployee, &buffer.id) == 0 &&
			employee_getNombre(pEmployee, buffer.nombre) == 0 &&
			employee_getHorasTrabajadas(pEmployee, &buffer.horasTrabajadas) == 0 &&
			employee_getSueldo(pEmployee, &buffer.sueldo) == 0)
		{
			printf("\n| %-4d | %-20s | %-16d | %-11.2f|\n",
					buffer.id,
					buffer.nombre,
					buffer.horasTrabajadas,
					buffer.sueldo);
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





