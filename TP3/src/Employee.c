#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"

static int employee_isValidNombre(char* string, int len);
static int employee_isValidInt(char* string, int len);
static int employee_isValidFloat(char* string, int len);


Employee* employee_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* id,char* nombre,char* horasTrabajadas, char* sueldo)
{
	Employee* pEmployee = NULL;

	if (id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		pEmployee = employee_new();
		if (pEmployee != NULL)
		{
			employee_setNombre(pEmployee,nombre);
			employee_setHorasTrabajadas(pEmployee,horasTrabajadas);
			employee_setSueldo(pEmployee,sueldo);
			employee_setId(pEmployee,id);
		}
	}
	return pEmployee;
}

void employee_delete(Employee* this)
{
	free(this);
}

int employee_setId(Employee* this, char* id)
{
    int output = -1;
    if (this != NULL && id != NULL && employee_isValidInt(id,sizeof(id))==0)
    {
        this->id = atoi(id);
        output = 0;
    }
    return output;
}

int employee_getId(Employee* this, int* id)
{
    int output = -1;
    if (this != NULL && id != NULL)
    {
        *id = this->id;
        output = 0;
    }
    return output;
}

int employee_setNombre(Employee *this, char* nombre)
{
	int output = -1;
	if (this != NULL && nombre != NULL && employee_isValidNombre(nombre, sizeof(nombre))==0)
	{
		strncpy(this->nombre, nombre, NOMBRE_LEN);
		output = 0;
	}
	return output;
}

int employee_getNombre(Employee* this, char* nombre)
{
    int output = -1;
    if (this != NULL && nombre != NULL)
    {
        strncpy(nombre, this->nombre, sizeof(nombre));
        output = 0;
    }
    return output;
}

int employee_setHorasTrabajadas(Employee* this, char* horasTrabajadas)
{
    int output = -1;
    if (this != NULL && horasTrabajadas != NULL && employee_isValidInt(horasTrabajadas,sizeof(horasTrabajadas))==0)
    {
        this->horasTrabajadas = atoi(horasTrabajadas);
        output = 0;
    }
    return output;
}

int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
    int result = -1;
    if (this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        result = 0;
    }
    return result;
}

int employee_setSueldo(Employee* this, char* sueldo)
{
    int output = -1;
    if (this != NULL && sueldo != NULL && employee_isValidFloat(sueldo,sizeof(sueldo))==0)
    {
        this->sueldo = atof(sueldo);
        output = 0;
    }
    return output;
}

int employee_getSueldo(Employee* this, float* sueldo)
{
    int result = -1;
    if (this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        result = 0;
    }
    return result;
}

static int employee_isValidNombre(char* string, int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if(	(string[i] < 'A' || string[i] > 'Z') &&
				(string[i] < 'a' || string[i] > 'z') &&
				 string[i] != ' ')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

static int employee_isValidInt(char* string, int len)
{
	int output = -1;
	int i = 0;

	if(string!= NULL && len > 0)
	{
		output = 0;
		if(string[0] == '-' || string[0] == '+')
		{
			i = 1;
		}
		for(i = 1; string[i]!= '\0' && i < len; i++)
		{
			if(string[i] < '0' || string[i] > '9')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

static int employee_isValidFloat(char* string, int len)
{
	int output = -1;
		int i = 0;

		if(string!= NULL && len > 0)
		{
			output = 0;
			if(string[0] == '-' || string[0] == '+')
			{
				i = 1;
			}
			for(i = 1; string[i]!= '\0' && i < len; i++)
			{
				if(string[i] < '0' || string[i] > '9' || string[i] != ',' )
				{
					output = -1;
					break;
				}
			}
		}
		return output;
}
