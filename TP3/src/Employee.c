
#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "utn.h"

static int isValidId(int id);
static int isValidHorasTrabajadas(int horasTrabajadas);
static int isValidNombre(char* nombre);
static int isValidSueldo(int sueldo);



Employee* employee_new(void)
{
	return (Employee*)malloc(sizeof(Employee));
}

Employee* employee_newParam(int id, char* nombre, int horasTrabajadas, int sueldo)
{
	Employee* this = Employee_new();
	if(this != NULL)
	{
		if(!(employee_setId(this, id))
			&& !(employee_setNombre(this, nombre))
			&& !(employee_setHorasTrabajadas(this, horasTrabajadas))
			&& !(employee_setSueldo(this, sueldo)))
		{
			return this;
		}
	}
	return NULL;
}

int employee_getId(Employee* this)
{
	return this->id;
}

int employee_setId(Employee* this, int id)
{
	int output = -1;
	if(this != NULL  && IsValidId(id))
	{
		this->id = id;
		output = 0;
	}
	 return output;
}

static int isValidId(int id)
{
	return 1;
}

char* employee_getNombre(Employee* this)
{
	return this->nombre;
}

int employee_setNombre(Employee* this, char* nombre)
{
	int output = -1;
	if(this != NULL && IsValidNombre(nombre))
	{
		strncpy(this->nombre,nombre,(int)sizeof(this->nombre));
		output = 0;
	}
	return output;
}

static int isValidNombre(char* nombre)
{
	return 1;
}

int employee_getHorasTrabajadas(Employee* this)
{
	return this->horasTrabajadas;
}

int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int output = -1;
	if(this != NULL  && IsValidHorasTrabajadas(horasTrabajadas))
	{
		this->horasTrabajadas = horasTrabajadas;
		output = 0;
	}
	 return output;
}

static int isValidHorasTrabajadas(int horasTrabajadas)
{
	return 1;
}

int employee_getSueldo(Employee* this)
{
	return this->sueldo;
}

int employee_setSueldo(Employee* this, int sueldo)
{
	int output = -1;
	if(this != NULL  && IsValidSueldo(sueldo));
	{
		this->sueldo = sueldo;
		output = 0;
	}
	 return output;
}

static int isValidSueldo(int sueldo)
{
	return 1;
}


