#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int cant;
    int todoOk = 0;
    char buffer[4][1500];
    Employee* auxEmp;

    cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    while(!feof(pFile))
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        if(cant == 4)
        {
            auxEmp = employee_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
            ll_add(pArrayListEmployee, auxEmp);
            todoOk = 1;
        }
    }

    if(todoOk == 1)
    {
        printf("\nEmpleados cargados con exito!!\n");
    }
    else
    {
        printf("\nProblemas con el archivo\n");
    }

    return 1;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

    return 1;
}
