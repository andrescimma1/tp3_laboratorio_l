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
    int r = -1;
    char buffer[4][1500];
    Employee* auxEmp;

    cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    while(!feof(pFile))
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        if(cant == 4)
        {
            auxEmp = employee_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
            if(auxEmp != NULL)
            {
                ll_add(pArrayListEmployee, auxEmp);
                r = 1;
            }
        }
    }

    if(r == 1)
    {
        printf("\nEmpleados cargados con exito!!\n");
    }
    else
    {
        printf("\nProblemas con el archivo\n");
    }

    return r;
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
    int r = -1;
    int cant;
    Employee* auxEmp;

    while(!feof(pFile))
    {
        auxEmp = employee_new();
        cant = fread(auxEmp, sizeof(Employee), 1, pFile);

        if(auxEmp != NULL)
        {
            ll_add(pArrayListEmployee, auxEmp);
            r = 1;
        }

        if(cant < 1)
        {
            if(!feof(pFile))
            {
                break;
            }
            else
            {
                free(auxEmp);
                break;
            }
        }
    }

    if(r == 1)
    {
        printf("\nEmpleados cargados con exito!!\n");
    }
    else
    {
        printf("\nProblemas con el archivo\n");
    }

    return r;
}
