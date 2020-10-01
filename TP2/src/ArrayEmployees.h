/**
 ============================================================================
 Name        : mi_biblioteca.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for library ArrayEmployees.c
 ============================================================================
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define TRUE 1
#define FALSE 0
#define LONG_NAME 51
#define QTY_EMPLOYEES 1000
#define SALARY_MIN 0.00
#define SALARY_MAX INT_MAX

typedef struct
{
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;
//INICIALIZAR
int initEmployees(Employee* list, int len);
//MENU
int getEmployeeMenu(int* choosenOption);
//ALTA
int checkFirstEmptyIndex(Employee* list, int len, int *emptyIndex);
int addEmployees(Employee* list,int len,int id,char name[],char lastName[],float salary,int sector);
int getEmployeeForm(char *name, char *lastName, float *salary, int *sector);
int loadEmployeeData(Employee* list,int len, int *firstLoad);
//MODIFICAR Y BAJA
int findEmployeeById(Employee* list, int len,int id);
//MODIFICAR
int modifyEntry(Employee* list, int len, int firstLoad);
int modifyEmployee(Employee* list, int len,int id);
//BAJA
int removeEntry(Employee* list, int len,int *firstLoad);
int removeEmployee(Employee* list, int len,int id);
//INFORME
int getEmployeeReport(Employee* list, int len, int firstLoad);
int sortEmployees(Employee* list, int len, int order);
int sortEmployeeByLastName(Employee* list, int len, int order);
int sortEmployeeBySector(Employee* list, int len, int order);
int printEmployees(Employee* list, int len);
int salaryInfo(Employee* list, int len);

#endif /* ARRAYEMPLOYEES_H_ */
