#include <stdio_ext.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

#define BUFFER_LEN 500

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int parser_EmployeeToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee *pEmployee;
	int bufferId;
	char bufferNombre[NOMBRE_LEN];
	int bufferHorasTrabajadas;
	float bufferSueldo;
	int len;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		fprintf(pFile, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");
		for (int i = 0; i < len; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			if (pEmployee != NULL &&
				employee_getId(pEmployee, &bufferId) == 0 &&
				employee_getNombre(pEmployee, bufferNombre) == 0 &&
				employee_getSueldo(pEmployee, &bufferSueldo) == 0 &&
				employee_getHorasTrabajadas(pEmployee, &bufferHorasTrabajadas) == 0)
			{
				fprintf(pFile, "%d,%s,%d,%.2f\n", bufferId, bufferNombre, bufferHorasTrabajadas, bufferSueldo);
			}
		}
		output = 0;
	}
	return output;
}

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee* pEmployee;
	char bufferHeader[BUFFER_LEN];
	char bufferId[BUFFER_LEN];
	char bufferName[BUFFER_LEN];
	char bufferWorkedHours[BUFFER_LEN];
	char bufferSalary[BUFFER_LEN];

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile, "%[^\n]\n", bufferHeader);//for skipping the header
		do
		{
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferName, bufferWorkedHours, bufferSalary) == 4)
			{
				pEmployee = employee_newParametros(bufferId, bufferName, bufferWorkedHours, bufferSalary);
				if (pEmployee != NULL)
				{
					output = ll_add(pArrayListEmployee, pEmployee);
				}
				else
				{
					output = -1;
					break;
				}
			}
		}while (!feof(pFile));
	}
	return output;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int output = -1;
	int retornoLectura;
	Employee* pBufferEmployee;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pBufferEmployee = employee_new();
			if(pBufferEmployee != NULL)
			{
				retornoLectura = fread(pBufferEmployee,sizeof(Employee),1,pFile);
				if (retornoLectura==1)
				{
					output = ll_add(pArrayListEmployee, pBufferEmployee);
				}
				else
				{
					employee_delete(pBufferEmployee);
					break;
				}
			}
		} while (!feof(pFile));
	}
	return output;
}

int parser_EmployeeToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	int len = ll_len(pArrayListEmployee);
	Employee* pEmployee;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			pEmployee = ll_get(pArrayListEmployee, i);
			fwrite(pEmployee,sizeof(Employee),1,pFile);
		}
		output = 0;
	}
	return output;
}
