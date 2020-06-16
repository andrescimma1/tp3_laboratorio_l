#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int mostrarEmployee(Employee* employee);
int mostrarEmployees(LinkedList* lista);


int compararEmpleadosPorId(void* emp1, void* emp2);
int compararEmpleadosPorNombre(void* emp1, void* emp2);
int compararEmpleadosPorHorasTrabajadas(void* emp1, void* emp2);
int compararEmpleadosPorSueldo(void* emp1, void* emp2);


#endif // employee_H_INCLUDED
