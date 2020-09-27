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
#define QTY_EMPLOYEES 5

typedef struct
{
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	int isEmpty;
}sEmployee;

int getEmployeeMenu(int* choosenOption);
int initEmployees(sEmployee* list, int len);
int checkFirstEmptyIndex(sEmployee* list, int len, int *emptyIndex);
int loadEmployeeData(sEmployee* list,int len, int index);
int modifyEmployee(sEmployee* list, int len);
int removeEmployee(sEmployee* list, int len,int *thereIsData);
int sortEmployees(sEmployee* list, int len);




#endif /* ARRAYEMPLOYEES_H_ */
