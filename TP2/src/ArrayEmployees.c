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
#include <limits.h>
#include "mi_biblioteca.h"
#include "ArrayEmployees.h"

static int checkFirstEmptyIndex(Employee* list, int len, int *emptyIndex);
static int getEmployeeForm(char *name, char *lastName, float *salary, int *sector);
static int generateNewId(void);
static int addEmployees(Employee* list,int len,int id,char name[],char lastName[],float salary,int sector);
static int findEmployeeById(Employee* list, int len,int id);
static int modifyEmployee(Employee* list, int len,int id);
static int removeEmployee(Employee* list, int len,int id);
static int sortEmployees(Employee* list, int len, int order);
static int sortEmployeeByLastName(Employee* list, int len, int order);
static int sortEmployeeBySector(Employee* list, int len, int order);
static int printEmployees(Employee* list, int len);
static int salaryInfo(Employee* list, int len);

/**
 * \brief getEmployeeMenu: Menu for choosing options of the program,
 * \param choosenOption* list: Pointer to variable that stores choosen option
 * \return (-1) Error / (0) Ok
 */

int getEmployeeMenu(int* choosenOption)
{
	int retorno = -1;
	if(utn_getIntNumber("\nIngrese una opcion:"
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

int initEmployees(Employee* list, int len)
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
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: Pointer to space in memory where is the
 *  variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int loadEmployeeData(Employee* list,int len, int *firstLoad)
{
	int retorno = -1;
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int index;

	if(list != NULL && len > 0 && firstLoad >0 && checkFirstEmptyIndex(list, QTY_EMPLOYEES, &index)==0)
	{
		if(getEmployeeForm(name, lastName, &salary, &sector)== 0)
		{
			id=generateNewId();
			if(addEmployees(list,QTY_EMPLOYEES,id,name,lastName,salary,sector)==0)
			{
				*firstLoad = TRUE;
				retorno=0;
			}
		}
		else
		{
			printf("\nERROR EN LA CARGA DEL EMPLEADO.\n");
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

static int checkFirstEmptyIndex(Employee* list, int len, int *emptyIndex)
{
	int retorno = -1;
	if(list != NULL && len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				*emptyIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

static int getEmployeeForm(char *name, char *lastName, float *salary, int *sector)
{
	int retorno = -1;

	if(name != NULL && lastName != NULL && salary > 0 && sector > 0)
	{
		if((utn_getString("Ingrese Apellido:", "Error. ", lastName, 3, LONG_NAME)==0) &&
		   (utn_getString("Ingrese Nombre:", "Error. ", name, 3, LONG_NAME)==0) &&
		   (utn_getFloatNumber("Ingrese sueldo: ", "Error. ", salary, 3, INT_MAX , 0)==0) &&
		   (utn_getIntNumber("Ingrese sector de trabajo(1-2-3-4): ", "\nError. ", sector, 3, 4, 1)== 0))
		{
			retorno = 0;
		}
	}
	return retorno;
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
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char name[]: Input by user
 * \param char lastName[]: Input by user
 * \param float salary: Input by user
 * \param int sector: Input by user
 * \return (-1) Error / (0) Ok
 */
///sobra INDEX
static int addEmployees(Employee* list,int len,int id,char name[],char lastName[],float salary,int sector)
{
	int retorno = -1;
	int emptyIndex;

	if(checkFirstEmptyIndex(list, QTY_EMPLOYEES, &emptyIndex)==0)
	{
		list[emptyIndex].id=id;
		strcpy(list[emptyIndex].name,name);
		strcpy(list[emptyIndex].lastName,lastName);
		list[emptyIndex].salary=salary;
		list[emptyIndex].sector=sector;
		list[emptyIndex].isEmpty=FALSE;
		printf("\nEl ID para %s %s es: %d\n",list[emptyIndex].lastName,list[emptyIndex].name,list[emptyIndex].id);
		retorno=0;
	}

    return retorno;
}

/**
 *  \brief findEmployeeById: find an Employee by Id then returns the index position in array.
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int id: id to search
 * \return Return employee index position or (-1) if ERROR
 */

static int findEmployeeById(Employee* list, int len,int id)
{
	int retorno;

	if (list != NULL && len > 0 && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].id == id )
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief modifyEntry: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int modifyEntry(Employee* list, int len, int firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   modifyEmployee(list,QTY_EMPLOYEES,idToSearch)== 0)
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief modifyEmployee: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

static int modifyEmployee(Employee* list, int len,int id)
{
	int retorno = -1;
	int choosenOption;
	char answer;
	int indexToModify;

	Employee bufferEmployee;

	indexToModify = findEmployeeById(list, QTY_EMPLOYEES, id);

	if(list != NULL && len>0 && id > 0 && indexToModify > -1)
	{
		do
		{
			printf("Empleado a modificar\n");
			printf("Apellido y Nombre: %s %s Sueldo: %.2f Sector: %d.\n", list[indexToModify].lastName,list[indexToModify].name,list[indexToModify].salary,list[indexToModify].sector);
			if(utn_getIntNumber("\nQue campo desea modificar:"
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
						strcpy(list[indexToModify].lastName,bufferEmployee.lastName);
					break;
				case 2:
					if(utn_getString("\nNombre:","\nError. ",bufferEmployee.name,2,LONG_NAME)==0)
						strcpy(list[indexToModify].name,bufferEmployee.name);
					break;
				case 3:
					if(utn_getIntNumber("Sector de trabajo(1-2-3-4): ", "\nError. ", &bufferEmployee.sector, 3, 4, 1)==0)
						list[indexToModify].sector=bufferEmployee.sector;
					break;
				case 4:
					if(utn_getFloatNumber("Sueldo: ", "\Error. ", &bufferEmployee.salary, 3, INT_MAX , 0)==0)
						list[indexToModify].salary=bufferEmployee.salary;
					break;
			}
		}
		utn_getChar("¿Desea seguir modificando este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
		}while(answer!='N');
		retorno = 0;
	}

	return retorno;
}

/**
 * \brief removeEntry: Remove a Employee by Id (put isEmpty Flag in TRUE)
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int *firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int removeEntry(Employee* list, int len,int *firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(*firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   removeEmployee(list,QTY_EMPLOYEES,idToSearch)== 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == TRUE)
				{
					*firstLoad = FALSE;
				}
				else
				{
					*firstLoad = TRUE;
					break;
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief removeEmployee: Remove a Employee by Id (put isEmpty Flag in TRUE)
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

static int removeEmployee(Employee* list, int len,int id)
{
	int retorno = -1;
	int indexToModify;
	char answer;

	indexToModify = findEmployeeById(list, QTY_EMPLOYEES, id);

	if(list != NULL && len>0 && id > 0 && indexToModify > -1)
	{
		printf("Empleado a eliminar\n");
		printf("Apellido y Nombre: %s %s Sueldo: %.2f Sector: %d.\n", list[indexToModify].lastName,list[indexToModify].name,list[indexToModify].salary,list[indexToModify].sector);
		utn_getChar("¿Desea eliminar este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
		switch(answer)
		{
			case 'Y':
				list[indexToModify].isEmpty = TRUE;
				printf("REGISTRO DE EMPLEADO BORRADO CON EXITO.");
				break;
			case'N':
				printf("REGISTRO NO BORRADO");
				break;
			default:
				printf("ERROR, INGRESE 'Y' PARA BORRAR EL REGISTRO.");
		}
		retorno = 0;
	}
	else
	{
		printf("\nERROR, ID INEXISTENTE.\n");
	}
	return retorno;
}

/**
 *  \brief getEmployeeReport: Reports employees by alphabetical order and numerical order
 *  of sector. Also gives info about total money spend on salaries, average salary and
 *  how many employees have a salary above the average.
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \param int firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int getEmployeeReport(Employee* list, int len, int firstLoad)
{
	int retorno = -1;
	int sortOrder;

	if(firstLoad == FALSE)
	{

		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");

	}
	else
	{
		if(utn_getIntNumber("\n1- Orden Descendente"
						    "\n2- Orden Ascendente"
						    "\nOpcion:","Error. ",&sortOrder,3,2,1)==0)
		{
			if(list!= NULL && len > 0)
			{
				sortEmployees(list, QTY_EMPLOYEES, sortOrder);
				printEmployees(list, QTY_EMPLOYEES);
				salaryInfo(list, QTY_EMPLOYEES);
				retorno = 0;
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
 * \param int order: [2] indicate UP (order Z->A) - [1] indicate DOWN (order A->Z)
 * \return (-1) Error / (0) Ok
 */

static int sortEmployees(Employee* list, int len, int order)
{
	int retorno = 0;

	if (list != NULL && len > 0 && order >0)
	{
		sortEmployeeBySector(list, QTY_EMPLOYEES, order);
		sortEmployeeByLastName(list, QTY_EMPLOYEES, order);
		retorno = 0;
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

static int sortEmployeeByLastName(Employee* list, int len, int order)
{
	int retorno = -1;
	int sorted;
	Employee bufferEmployee;
	do
	{
		sorted = TRUE;
		for(int i = 0; i < (len-1); i++)
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

static int sortEmployeeBySector(Employee* list, int len, int order)
{
	int retorno = -1;
	int sorted;
	Employee bufferEmployee;

	do
	{
		sorted = TRUE;
		for(int i = 0; i < (len-1); i++)
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
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \return (-1) Error / (0) Ok*
 */

static int printEmployees(Employee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		printf("\nApellido        Nombre          Sector  ID     Sueldo\n");
		for(int i=0;i< len ;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("%-15s %-15s %-6d  %-6d $%.2f\n",list[i].lastName,list[i].name,list[i].sector, list[i].id, list[i].salary);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief salaryInfo: print sum of salaries, average salaries
 * \and number of employees with salaries above average
 * \param Employee* list: Pointer to array of employees
 * \param int len: Array length
 * \return (-1) Error / (0) Ok*
 */

static int salaryInfo(Employee* list, int len)
{
	int retorno = -1;
	int counter = 0;
	float sumSalary;
	float averageSalary;
	int overAverage = 0;

	if(list != NULL && len  > 0)
	{
		for(int i=0;i<len ;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				sumSalary = sumSalary + list[i].salary;
				counter++;
			}
		}
		averageSalary = (float)sumSalary/counter;

		for(int i=0;i<len ;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].salary>averageSalary)
			{
				overAverage++;
			}
		}
		printf("\nEl total de salarios es $ %.2f\n",sumSalary);
		printf("\nEl promedio de salarios es $ %.2f\n",averageSalary);
		printf("\nLa cantidad de empleados que ganan por encima de la media son %d\n",overAverage);
		retorno = 0;
	}
	return retorno;
}

