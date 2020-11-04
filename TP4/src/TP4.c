/*
 ============================================================================
 Name        : TP1.c
 Author      : Gonzalo Sinnott
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

#define NOMBRE_LEN 50

typedef struct
{
	int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new()
{
	Employee* this;
	this=(Employee*)malloc(sizeof(Employee));
	return this;
}

Employee* employee_newParametros(char* id,char* nombre,char* horasTrabajadas, char* sueldo)
{
	Employee* pEmployee = NULL;

	if (id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		pEmployee = employee_new();
		if (pEmployee != NULL)
		{
			if(employee_setNombre(pEmployee,nombre) == 0 &&
			   employee_setHorasTrabajadasTxt(pEmployee,horasTrabajadas) == 0 &&
			   employee_setSueldoTxt(pEmployee,sueldo) == 0 &&
			   employee_setIdTxt(pEmployee,id) == 0)
			{
				return pEmployee;
				printf("EMPLEADO CARGADO CON EXITO");
			}
			else
			{
				printf("ERROR EN LA CARGA DE EMPELADO.\n");
			}
		}
	}
	return NULL;
}

int employee_setNombre(Employee *this, char* nombre)
{
	int output = -1;
	if (this != NULL && nombre != NULL && isValidNombre(nombre, sizeof(nombre)))
	{
		strncpy(this->nombre, nombre,sizeof(nombre));
		output = 0;
	}
	return output;
}

int isValidNombre(char* string, int len)
{
	int output = 0;

	if(string!= NULL)
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
	return output;;
}

int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
    int output = -1;
    if (this != NULL && horasTrabajadas != NULL && isValidNumber(horasTrabajadas, sizeof(horasTrabajadas)))
    {
        this->horasTrabajadas = atoi(horasTrabajadas);
        output = 0;
    }
    return output;
}

int isValidNumber(char* string, int len)
{
	int output = 1;
	int i = 0;

	if(string != NULL)
	{
		if(string)
		{
			i = 1;
		}
		if(string != NULL && len > 0)
		{
			while(string[i] != '\0')
			{
				if(string[i] < '0' || string[i] > '9' )
				{
					output = 0;
					break;
				}
				i++;
			}
		}
	}
	return output;
}

int employee_setSueldoTxt(Employee* this, char* sueldo)
{
    int output = -1;
    if (this != NULL && sueldo != NULL && isValidFloat(sueldo, sizeof(sueldo)))
    {
        this->sueldo = atof(sueldo);
        output = 0;
    }
    return output;
}

int isValidFloat(char* string, int len)
{
	int retorno = 1;
	int i = 0;

	if(string[0] == '-')
	{
		i = 1;
	}
	if(string != NULL && len > 0)
	{
		while(string[i] != '\0')
		{
			if((string[i] < '0' || string[i] > '9') && string[i] != '.')
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

int employee_setIdTxt(Employee* this, char* id)
{
    int output = -1;
    if (this != NULL && id != NULL && isValidNumber(id, sizeof(id)))
    {
        this->id = atoi(id);
        output = 0;
    }
    return output;
}
