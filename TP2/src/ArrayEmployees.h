/*
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
#define QTY_EMPLOYEES 2

typedef struct
{
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int initEmployees(Employee* list, int len);
int checkFirstEmptyIndex(Employee* list, int len, int *emptyIndex);
int loadEmployeeData(Employee* list,int len, int index);
int findEmployeeById(Employee* list, int len,int* index, int id);
int modifyEmployee(Employee* list, int len,int index, int id);
int removeEmployee(Employee* list, int len,int index, int id);
int printEmployees(Employee* list, int len);

#endif /* ARRAYEMPLOYEES_H_ */
