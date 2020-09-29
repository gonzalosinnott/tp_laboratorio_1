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
#define QTY_EMPLOYEES 3

typedef struct
{
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int getEmployeeMenu(int* choosenOption);
int initEmployees(Employee* list, int len);
int loadEmployeeData(Employee* list,int len, int *firstLoad);
int modifyEntry(Employee* list, int len, int firstLoad);
int removeEntry(Employee* list, int len,int *firstLoad);
int getEmployeeReport(Employee* list, int len, int firstLoad);

#endif /* ARRAYEMPLOYEES_H_ */
