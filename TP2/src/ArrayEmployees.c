 /**
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library ArrayEmployees.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "mi_biblioteca.h"
#include "ArrayEmployees.h"

static int checkFirstEmptyIndex(sEmployee* list, int len, int *emptyIndex);
static int generateNewId(void);
static int addEmployees(sEmployee* list,int len,int id,char name[],char lastName[],float salary,int sector,int index);
static int findEmployeeById(sEmployee* list, int len,int* index, int id);
static int sortEmployeeByLastName(sEmployee* list, int len, int order);
static int sortEmployeeBySector(sEmployee* list, int len, int order);
static int printEmployees(sEmployee* list, int len);
static int salaryInfo(sEmployee* list, int len);
static int salaryAverage(sEmployee* list, int len,float *salarySum, float *salaryAverage);
static int employeeAboveAverage(sEmployee* list, int len, float salaryAverage, int *overAverage);

int getEmployeeMenu(int* choosenOption)
{
	int retorno = -1;
	if(utn_getInt("\nIngrese una opcion:"
					   "\n 1-Alta de empleado."
					   "\n 2-Modificar datos de empleado."
					   "\n 3-Baja de empleado."
					   "\n 4-Informe de personal."
					   "\n 5-Salir"
					   "\nOpcion:", "\nError.", choosenOption, 3, 5, 1)==0)
	{
		retorno =0;
	}
	else
	{
		*choosenOption = 5;
	}

	return retorno;
}

/**
 * \brief initEmployees: To indicate that all positions in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all position of the array
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \return (-1) Error / (0) Ok
 */

int initEmployees(sEmployee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 *  \brief loadEmployeeData: Asks the user for the employee data
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: Pointer to space in memory where is the
 *  variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int loadEmployeeData(sEmployee* list,int len, int *firstLoad)
{
	int retorno = -1;
    int id;
    char name[LONG_NAME];
    char lastName[LONG_NAME];
    float salary;
    int sector;
    int emptyIndex;

    checkFirstEmptyIndex(list, len, &emptyIndex);

    if(list != NULL && len > 0 && index >= 0 && emptyIndex < len)
    {

        if(utn_getString("Ingrese Apellido:", "\nError. ", lastName, 3, LONG_NAME) == 0 &&
        utn_getString("Ingrese Nombre:", "\nError. ", name, 3, LONG_NAME)== 0 &&
        utn_getFloat("Ingrese sueldo: ", "\Error. ", &salary, 3) == 0 &&
        utn_getInt("Ingrese sector de trabajo(1-2-3-4): ", "\nError. ", &sector, 3, 4, 1) == 0)
        {
        	id=generateNewId();
			addEmployees(list,QTY_EMPLOYEES,id,name,lastName,salary,sector,emptyIndex);
			printf("\nEl ID para %s %s es: %d\n",list[emptyIndex].lastName,list[emptyIndex].name,list[emptyIndex].id);
			list[emptyIndex].isEmpty=FALSE;
			*firstLoad = TRUE;
			retorno=0;
		}
    }
    else
	{
		printf("\nNO SE PUEDEN CARGAR MAS REGISTROS.\n");
	}
    return retorno;
}

/**
 *  \brief checkFirstEmptyIndex: Checks first empty index in the array
 * this function search the array for the first index with the value TRUE in the isEmpty item
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int *EmptyIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */

static int checkFirstEmptyIndex(sEmployee* list, int len, int *emptyIndex)
{
	int retornar = -1;
	if(list != NULL && len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				*emptyIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**
 *  \brief generateNewId: Generates a new ID that's +1 from previous loaded employee ID.
 */

static int generateNewId(void)
{
	static int id;

	id = id+1;
	return id;
}

/**
 *  \brief addEmployees: add in a existing list of employees the values received
 *  as parameters in the first empty position.
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char name[]: Input by user
 * \param char lastName[]: Input by user
 * \param float salary: Input by user
 * \param int sector: Input by user
 * \return (-1) Error / (0) Ok
 */

static int addEmployees(sEmployee* list,int len,int id,char name[],char lastName[],float salary,int sector,int index)
{
    int retorno=0;
    list[index].id=id;
    strcpy(list[index].name,name);
    strcpy(list[index].lastName,lastName);
    list[index].salary=salary;
    list[index].sector=sector;
    return retorno;
}

/**
 *  \brief findEmployeeById: find an Employee by Id then returns the index position in array.
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int index: Pointer to index of ID searched
 * \param int id: id to search
 * \return (-1) Error / (0) Ok
 */

static int findEmployeeById(sEmployee* list, int len,int* index, int id)
{
	int retorno = -1;

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				if(list[i].id == id)
				{
					*index = i;
					retorno = 0;
					break;
				}
			}
			else
			{
				printf("\nERROR, ID INEXISTENTE.\n");
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief modifyEmployee: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int modifyEmployee(sEmployee* list, int len, int firstLoad)
{
	int retorno = -1;
	int idToSearch;
	int choosenOption;
	char answer;
	int index;
	sEmployee bufferEmployee;

	if(firstLoad == FALSE)
	{

		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");

	}
	else
	{
		utn_getInt("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,1000,1);

		if(findEmployeeById(list, QTY_EMPLOYEES, &index, idToSearch)==0)
		{
			if(	list != NULL &&	len>0 && index>=0 && index<len && list[index].isEmpty == FALSE)
			{
				do
				{
					printf("Empleado a modificar\n");
					printf("Apellido y Nombre: %s %s Sueldo: %.2f Sector: %d.\n", list[index].lastName,list[index].name,list[index].salary,list[index].sector);
					if(utn_getInt("\nQue campo desea modificar:"
								"\n 1-Apellido."
								"\n 2-Nombre."
								"\n 3-Sector."
								"\n 4-Salario."
								"\nOpcion:", "\nError.", &choosenOption, 3, 4, 1)==0)
					{
						switch(choosenOption)
						{
							case 1:
								if(utn_getString("\nApellido:","\nError. ",bufferEmployee.lastName,2,LONG_NAME)==0)
									strcpy(list[index].lastName,bufferEmployee.lastName);
								break;
							case 2:
								if(utn_getString("\nNombre:","\nError. ",bufferEmployee.name,2,LONG_NAME)==0)
									strcpy(list[index].name,bufferEmployee.name);
								break;
							case 3:
								if(utn_getInt("Sector de trabajo(1-2-3-4): ", "\nError. ", &bufferEmployee.sector, 3, 4, 1)==0)
									list[index].sector=bufferEmployee.sector;
								break;
							case 4:
								if(utn_getFloat("Sueldo: ", "\Error. ", &bufferEmployee.salary, 3)==0)
									list[index].salary=bufferEmployee.salary;
								break;
						}
					}
					utn_getChar("¿Desea seguir modificando este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
				}while(answer!='N');
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 *  \brief removeEmployee:Remove a Employee by Id (put isEmpty Flag in TRUE)
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int *firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int removeEmployee(sEmployee* list, int len,int *firstLoad)
{
	int retorno = -1;
	int idToSearch;
	char answer;
	int index;
	sEmployee bufferEmployee;

	if(*firstLoad == FALSE)
	{

		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");

	}
	else
	{
		utn_getInt("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,1000,1);
		if(findEmployeeById(list, QTY_EMPLOYEES, &index, idToSearch)==0)
		{
			if(	list != NULL && len>0 && index>=0 && index<len && list[index].isEmpty == FALSE)
			{
				printf("Empleado a eliminar\n");
				printf("Apellido y Nombre: %s %s Sueldo: %.2f Sector: %d.\n", list[index].lastName,list[index].name,list[index].salary,list[index].sector);
				utn_getChar("¿Desea eliminar este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
				if(answer=='Y')
				{
					bufferEmployee.id = idToSearch;
					bufferEmployee.isEmpty = TRUE;
					list[index] = bufferEmployee;
					printf("REGISTRO DE EMPLEADO BORRADO CON EXITO.");
					retorno = 0;
					for (int i = 0; i < len; i++)
					{
						if(list[i].isEmpty == FALSE)
						{
							*firstLoad = TRUE;
						}
						else
						{
							*firstLoad = FALSE;
						}
					}
				}
				else
				{
					printf("ERROR, INGRESE 'Y' PARA BORRAR EL REGISTRO.");
				}
			}
		}
	}
	return retorno;
}

/**
 *  \brief sortEmployees: Sort the elements in the array of employees, the argument order
 * indicate UP or DOWN order
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int sortEmployees(sEmployee* list, int len, int firstLoad)
{
	int retorno = -1;
	int sortOrder;

	if(firstLoad == FALSE)
	{

		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");

	}
	else
	{
		if(utn_getInt("\n1- Orden Descendente"
					  "\n2- Orden Ascendente"
					  "\nOpcion:","Error. ",&sortOrder,3,2,1)==0)
		{
			if(list!= NULL && len > 0)
			{
				sortEmployeeByLastName(list, QTY_EMPLOYEES, sortOrder);
				sortEmployeeBySector(list, QTY_EMPLOYEES, sortOrder);
				printEmployees(list, QTY_EMPLOYEES);
				salaryInfo(list, QTY_EMPLOYEES);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 *  \brief sortEmployeeByLastName:sort the elements in the array by last name and name
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int order: [2] indicate UP (order Z->A) - [1] indicate DOWN (order A->Z)
 * \return (-1) Error / (0) Ok
 */

static int sortEmployeeByLastName(sEmployee* list, int len, int order)
{
	int retorno = -1;
	int sorted;
	sEmployee bufferEmployee;
	do
	{
		sorted = TRUE;
		for(int i = 0; i < (len - 1); i++)
		{
			switch(order)
			{
				case 1:
					if(strncmp(list[i].lastName, list[i + 1].lastName,LONG_NAME)>0 ||
					  (strncmp(list[i].lastName, list[i + 1].lastName,LONG_NAME)==0 &&
					   strncmp(list[i].name, list[i + 1].name,LONG_NAME)>0))
					{
						bufferEmployee = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferEmployee;
						sorted = FALSE;
					}
					break;
			case 2:
				if(strncmp(list[i].lastName, list[i + 1].lastName,LONG_NAME)<0 ||
				  (strncmp(list[i].lastName, list[i + 1].lastName,LONG_NAME)==0 &&
				   strncmp(list[i].name, list[i + 1].name,LONG_NAME)<0))
				{
					bufferEmployee = list[i];
					list[i] = list[i + 1];
					list[i + 1] = bufferEmployee;
					sorted = FALSE;
				}
				break;
			}
		}
	}while(sorted == FALSE);
	retorno = 0;
	return retorno;
}

/**
 *  \brief sortEmployeeBySector: sort the elements in the array by sector
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int order: [2] indicate UP (order 9->1) - [1] indicate DOWN (order 1->9)
 * \return (-1) Error / (0) Ok
 */

static int sortEmployeeBySector(sEmployee* list, int len, int order)
{
	int retorno = -1;
	int sorted;
	sEmployee bufferEmployee;

	do
	{
		sorted = TRUE;
		for(int i = 0; i < (len - 1); i++)
		{
			switch(order)
			{
				case 1:
					if(list[i].sector > list[i + 1].sector)
					{
						bufferEmployee = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferEmployee;
						sorted = FALSE;
					}
					break;
				case 2:
					if(list[i].sector < list[i + 1].sector)
					{
						bufferEmployee = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferEmployee;
						sorted = FALSE;
					}
					break;
			}
		}
	}while(sorted == FALSE);
	retorno = 0;
	return retorno;
}

/**
 * \brief printEmployees: print the content of employees array
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \return (-1) Error / (0) Ok*
 */

static int printEmployees(sEmployee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len  > 0)
	{
		for(int i=0;i< len ;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("\nSector: %d ID: %d - Apellido y Nombre: %s %s\n",list[i].sector, list[i].id, list[i].lastName,list[i].name);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief salaryInfo: print sum of salaries, average salaries
 * \and number of employees with salaries above average
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \return (-1) Error / (0) Ok*
 */

static int salaryInfo(sEmployee* list, int len)
{
	int retorno = -1;
	float sumSalary;
	float averageSalary;
	int overAverage;

	if(list != NULL && len  > 0)
	{
		salaryAverage(list, QTY_EMPLOYEES, &sumSalary, &averageSalary);
		employeeAboveAverage(list, QTY_EMPLOYEES, averageSalary, &overAverage);
		printf("\nEl total de salarios es $ %.2f\n",sumSalary);
		printf("\nEl promedio de salarios es $ %.2f\n",averageSalary);
		printf("\nLa cantidad de empleados que ganan por encima de la media son %d\n",overAverage);
	}
	return retorno;
}

/**
 * \brief salaryAverage: gets the average salary and the sum of all salaries
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param float *salarySum: Pointer to sum of all salaries
 * \param int *salaryAverage: pointer to value of average salary
 * \return (-1) Error / (0) Ok*
 */

static int salaryAverage(sEmployee* list, int len,float *salarySum, float *salaryAverage)
{
	int retorno = -1;
	float sum;
	int counter = 0;
	float average;

	if(list!=NULL && len > 0 && salarySum != NULL && salaryAverage != NULL)
	{
		for(int i=0;i< len ;i++)
		{
			if(list[i].isEmpty==FALSE)
			{
				sum = sum + list[i].salary;
				counter++;
			}
		}
		average = (float)sum/counter;
		*salaryAverage = average;
		*salarySum = sum;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief employeeAboveAverage: gets the number of employees with salaries over the average
 * \param sEmployee* list: Pointer to array of employees
 * \param int len: Array length
 * \param float salaryAverage: sum of all salaries
 * \param int *overAverage: pointer to number of employees with salaries over the average
 * \return (-1) Error / (0) Ok*
 */

static int employeeAboveAverage(sEmployee* list, int len, float salaryAverage, int *overAverage)
{
	int retorno = -1;
	int counter=0;

	if(list!=NULL && len > 0)
	{
		for(int i=0;i< len ;i++)
		{
			if(list[i].salary>salaryAverage)
			{
				counter++;
			}
		}
		*overAverage = counter;
		retorno = 0;
	}
	return retorno;
}

