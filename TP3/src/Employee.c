/*
============================================================================
Name        : Employee.c
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Library Employee.c
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "LinkedList.h"

static int employee_isValidNombre(char* string, int len);
static int employee_isValidInt(char* string, int len);
static int employee_isValidFloat(char* string, int len);

/*
 * \brief employee_new:Pide memoria para generar un nuevo registro de empleado
 * \param void:
 * \return puntero con espacio de memoria con tipo Employee*
 */

Employee* employee_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}

/*
 * \brief employee_newParametros: Pide memoria para un nuevo empleado y sus campos correspondientes
 * \param id char*: campo id
 * \param nombre char*: campo nombre
 * \param horasTrabajadas char*: campo Horas trabajadas
 * \param sueldo char*: campo sueldo
 * \return int Return puntero con espacio de memoria con tipo Employee* con el espacio para los campos correspondientes
 */

Employee* employee_newParametros(char* id,char* nombre,char* horasTrabajadas, char* sueldo)
{
	Employee* pEmployee = NULL;

	if (id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		pEmployee = employee_new();
		if (pEmployee != NULL &&
			employee_setNombre(pEmployee,nombre) == 0 &&
			employee_setHorasTrabajadasFromTxtFile(pEmployee,horasTrabajadas) == 0 &&
			employee_setSueldoFromTxtFile(pEmployee,sueldo) == 0 &&
			employee_setIdFromTxtFile(pEmployee,id) == 0)
		{
			return pEmployee;
		}
		else
		{
			pEmployee = NULL;
		}
	}
	return pEmployee;
}

/*
 * \brief employee_delete: Libera espacio de memoria de un empleado
 * \param this Employee*: puntero a empleado
 * \return void
 */

void employee_delete(Employee* this)
{
	free(this);
}

/*
 * \brief employee_setIdFromTxtFile: Carga el id obtenido como texto en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setIdFromTxtFile(Employee* this, char* id)
{
    int output = -1;
    if (this != NULL && id != NULL && employee_isValidInt(id,sizeof(id))==0)
    {
        this->id = atoi(id);
        output = 0;
    }
    return output;
}

/*
 * \brief employee_setId: Carga el id en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setId(Employee* this, int id)
{
	int output = -1;
	if (this != NULL && id >= 0)
	{
		this->id = id;
		output = 0;
	}
	return output;
}

/*
 * \brief employee_getId: Obtiene el id del empleado
 * \param this Employee*: puntero a empleado
 * \param id int*: puntero al espacio donde va a guardar el id obtenido
 * \return (-1) Error / (0) Ok
 */

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

/*
 * \brief employee_findMaxId: Busca en el array el maximo id existente
 * \param pArrayListEmployee LinkedList* puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int employee_findMaxId(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;
	int len;
	int i;
	int max;
	int id = -1;

	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(i=0;i<len;i++)
		{
			pEmployee = ll_get(pArrayListEmployee,i);
			employee_getId(pEmployee,&id);
			if (i == 0 || id > max)
			{
				max = id;
			}
		}
		id = max;
	}
	return id;
}

/*
 * \brief employee_generateNewId:Genera un nuevo id para un nuevo empleado
 * \param pArrayListEmployee LinkedList* puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int employee_generateNewId(LinkedList* pArrayListEmployee)
{
    static int id = -1;

    if(pArrayListEmployee != NULL)
    {
    	if(ll_isEmpty(pArrayListEmployee)==0)
    	{
    		id = employee_findMaxId(pArrayListEmployee);
    		id++;
    	}
    }
    return id;
}

/*
 * \brief employee_setNombre: Carga el nombre en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param nombre char*: nombre a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setNombre(Employee *this, char* nombre)
{
	int output = -1;
	if (this != NULL && nombre != NULL && employee_isValidNombre(nombre, NOMBRE_LEN)==0)
	{
		strncpy(this->nombre, nombre, NOMBRE_LEN);
		output = 0;
	}
	return output;
}

/*
 * \brief employee_getNombre: Obtiene el nombre del empleado
 * \param this Employee*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int employee_getNombre(Employee* this, char* nombre)
{
    int output = -1;
    if (this != NULL && nombre != NULL)
    {
        strncpy(nombre, this->nombre,NOMBRE_LEN);
        output = 0;
    }
    return output;
}

/*
 * \brief employee_setHorasTrabajadasFromTxtFile: Carga las horas trabajadas obtenidas como texto en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param horasTrabajadas char*: puntero al horasTrabajadas que va a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setHorasTrabajadasFromTxtFile(Employee* this, char* horasTrabajadas)
{
    int output = -1;
    if (this != NULL && horasTrabajadas != NULL && employee_isValidInt(horasTrabajadas,sizeof(horasTrabajadas))==0)
    {
        this->horasTrabajadas = atoi(horasTrabajadas);
        output = 0;
    }
    return output;
}

/*
 * \brief employee_setHorasTrabajadas: Carga  horasTrabajadas en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param horasTrabajadas int: horasTrabajadas a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int output = -1;
	if(this != NULL && horasTrabajadas > 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		output = 0;
	}
	return output;
}

/*
 * \brief employee_getHorasTrabajadas: Obtiene las horasTrabajadas del empleado
 * \param this Employee*: puntero a empleado
 * \param horasTrabajadas int*: puntero al espacio donde va a guardar las horasTrabajadas obtenidas
 * \return (-1) Error / (0) Ok
 */

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

/*
 * \brief employee_setSueldoFromTxtFile: Carga el sueldo obtenido como texto en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param sueldo char*: puntero al horasTrabajadas que va a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setSueldoFromTxtFile(Employee* this, char* sueldo)
{
    int output = -1;
    if (this != NULL && sueldo != NULL && employee_isValidFloat(sueldo,sizeof(sueldo))==0)
    {
        this->sueldo = atof(sueldo);
        output = 0;
    }
    return output;
}
/*
 * \brief employee_setSueldo: Carga  sueldo en el campo del empleado
 * \param this Employee*: puntero a empleado
 * \param sueldo float: horasTrabajadas a cargar
 * \return (-1) Error / (0) Ok
 */

int employee_setSueldo(Employee* this, float sueldo)
{
	int output = -1;
	if(this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		output = 0;
	}
	return output;
}

/*
 * \brief employee_getSueldo: Obtiene el sueldo del empleado
 * \param this Employee*: puntero a empleado
 * \param sueldo float*: puntero al espacio donde va a guardar el sueldo obtenidas
 * \return (-1) Error / (0) Ok
 */

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

/*
 * \brief employee_isValidNombre:Valida que la cadena recibida solo tenga letras, espacios o guiones
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

static int employee_isValidNombre(char* string, int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if(	(string[i] < 'A' || string[i] > 'Z') &&
				(string[i] < 'a' || string[i] > 'z') &&
				string[i] != ' ' && string[i] != '-')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief employee_isValidInt: Valida que la cadena recibida solo tenga numeros
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

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

/*
 * \brief employee_isValidFloat: Valida que la cadena recibida solo tenga numeros y a lo sumo un punto
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

static int employee_isValidFloat(char* string, int len)
{
	int output = -1;
	int i = 0;
	int comaCounter = 0;

	if(string!= NULL && len > 0)
	{
		output=0;
		if(string[0] == '-' || string[0] == '+')
		{
			i = 1;
		}
		for( ; string[i]!= '\0' && i < len; i++)
		{
			if(string[i] == '.')
			{
				comaCounter++;
			}
			else if(string[i] < '0' || string[i] > '9' || comaCounter>1)
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief employee_compareId: compara los id de dos empleados
 * \param fieldOne void*: puntero al primer empleado a comparar
 * \param fieldTwo void*: puntero al segundo empleado a comparar
 * \return int Return:
 * \(-1) Si el id del primer empleado es menor al segundo
 * \(1) Si el id del primer empleado es mayor al segundo
 * \(0) Si los id son iguales
 */

int employee_compareId (void* fieldOne, void* fieldTwo)
{
	int output = 0;
	int bufferFirstEmployee;
	int bufferSecondEmployee;

	if(fieldOne != NULL && fieldTwo != NULL)
	{
		employee_getId((Employee*)fieldOne,&bufferFirstEmployee);
		employee_getId((Employee*)fieldTwo,&bufferSecondEmployee);
		if(bufferFirstEmployee > bufferSecondEmployee)
		{
			output = 1;
		} else if (bufferFirstEmployee < bufferSecondEmployee) {
			output = -1;
		}
	}
	return output;
}

/*
 * \brief employee_compareNombre: compara los nombres de dos empleados
 * \param fieldOne void*: puntero al primer empleado a comparar
 * \param fieldTwo void*: puntero al segundo empleado a comparar
 * \return int Return:
 * \(-1) Si el nombre del primer empleado es menor al segundo
 * \(1) Si el nombre del primer empleado es mayor al segundo
 * \(0) Si los nombres son iguales
 */

int employee_compareNombre(void* fieldOne, void* fieldTwo)
{
	int result = 0;
	Employee* bufferFirstEmployee;
	Employee* bufferSecondEmployee;

	bufferFirstEmployee = fieldOne;
	bufferSecondEmployee = fieldTwo;

	char nameFirstEmployee[NOMBRE_LEN];
	char nameSecondEmployee[NOMBRE_LEN];

	if(fieldOne != NULL && fieldOne != NULL)
	{
		employee_getNombre(bufferFirstEmployee,nameFirstEmployee);
		employee_getNombre(bufferSecondEmployee,nameSecondEmployee);
		if(strncmp(nameFirstEmployee, nameSecondEmployee, NOMBRE_LEN) > 0)
		{
			result = 1;
		}
		else if (strncmp(nameFirstEmployee, nameSecondEmployee, NOMBRE_LEN) < 0)
		{
			result = -1;
		}
	}
	return result;
}

/*
 * \brief employee_compareHorasTrabajadas: compara las horas trabajadas de dos empleados
 * \param fieldOne void*: puntero al primer empleado a comparar
 * \param fieldTwo void*: puntero al segundo empleado a comparar
 * \return int Return:
 * \(-1) Si las horas trabajadas del primer empleado es menor al segundo
 * \(1) Si las horas trabajadas del primer empleado es mayor al segundo
 * \(0) Si las horas trabajadas son iguales
 */

int employee_compareHorasTrabajadas(void* fieldOne, void* fieldTwo)
{
	int output = 0;
	int bufferFirstEmployee;
	int bufferSecondEmployee;

	if(fieldOne != NULL && fieldTwo != NULL)
	{
		employee_getHorasTrabajadas((Employee*)fieldOne,&bufferFirstEmployee);
		employee_getHorasTrabajadas((Employee*)fieldTwo,&bufferSecondEmployee);
		if(bufferFirstEmployee > bufferSecondEmployee)
		{
			output = 1;
		} else if (bufferFirstEmployee < bufferSecondEmployee) {
			output = -1;
		}
	}
	return output;
}

/*
 * \brief employee_compareSueldo: compara los sueldos de dos empleados
 * \param fieldOne void*: puntero al primer empleado a comparar
 * \param fieldTwo void*: puntero al segundo empleado a comparar
 * \return int Return:
 * \(-1) Si el sueldo del primer empleado es menor al segundo
 * \(1) Si el sueldo del primer empleado es mayor al segundo
 * \(0) Si los nombres son iguales
 */

int employee_compareSueldo(void* fieldOne, void* fieldTwo)
{
	int output = 0;
	float bufferFirstEmployee;
	float bufferSecondEmployee;

	if(fieldOne != NULL && fieldTwo != NULL)
	{
		employee_getSueldo((Employee*)fieldOne,&bufferFirstEmployee);
		employee_getSueldo((Employee*)fieldTwo,&bufferSecondEmployee);
		if(bufferFirstEmployee > bufferSecondEmployee)
		{
			output = 1;
		} else if (bufferFirstEmployee < bufferSecondEmployee) {
			output = -1;
		}
	}
	return output;
}
