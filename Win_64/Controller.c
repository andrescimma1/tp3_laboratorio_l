#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int r = 1;

    FILE* f = fopen(path, "r");

    if(f == NULL)
    {
        printf("Problema al abrir el archivo\n");
        r = -1;
    }
    else
    {
        r = parser_EmployeeFromText(f, pArrayListEmployee);
    }

    fclose(f);

    return r;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    char buffer[4][1500];
    int cant;

    FILE* f;

    f = fopen(path, "rb");

    if(f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return -1;
    }


    fclose(f);

    return 1;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int tam;
    char id[20];
    char nombre[20];
    char horasTrabajadas[20];
    char sueldo[20];
    int todoOkId = 0;
    int todoOkNombre = 0;
    int todoOkHorasTrabajadas = 0;
    int todoOkSueldo = 0;
    int todoOk = -1;
    int r = -1;
    tam = ll_len(pArrayListEmployee);
    Employee* auxEmp;

    do
    {
        printf("Ingrese id: ");
        fflush(stdin);
        gets(id);



        if(atoi(id) >= 0 && atoi(id) < 10000)
        {
            todoOkId = 1;
        }
        else
        {
            printf("Error, ingrese id: ");
            fflush(stdin);
            gets(id);
        }
    }while(todoOkId != 1);

    do
    {
        printf("Ingrese nombre: ");
        fflush(stdin);
        gets(nombre);

        if(strlen(nombre) > 2 && strlen(nombre) < 20)
        {
            todoOkNombre = 1;
        }
        else
        {
            printf("Error, ingrese nombre: ");
            fflush(stdin);
            gets(nombre);
        }
    }while(todoOkNombre != 1);

    do
    {
        printf("Ingrese horas trabajadas: ");
        fflush(stdin);
        gets(horasTrabajadas);

        if(atoi(horasTrabajadas) > 2 && atoi(horasTrabajadas) < 800)
        {
            todoOkHorasTrabajadas = 1;
        }
        else
        {
            printf("Error, ingrese horas trabajadas: ");
            fflush(stdin);
            gets(horasTrabajadas);
        }
    }while(todoOkHorasTrabajadas != 1);

    do
    {
        printf("Ingrese sueldo: ");
        fflush(stdin);
        gets(sueldo);

        if(atoi(sueldo) > 0 && atoi(sueldo) < 800000)
        {
            todoOkSueldo = 1;
        }
        else
        {
            printf("Error, ingrese sueldo: ");
            fflush(stdin);
            gets(sueldo);
        }
    }while(todoOkSueldo != 1);

    auxEmp = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
    r = ll_add(pArrayListEmployee, auxEmp);

    if(r != 1)
    {
        printf("Empleado registrado con exito!!!\n");
    }
    else
    {
        printf("No se ha cargado el empleado\n");
    }

    return r;
}



/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int r = -1;
    int id;
    int indice;
    int error = 1;
    Employee* auxEmp;

    mostrarEmployees(pArrayListEmployee);

    printf("\nIngrese el ID del empleado a modificar: ");
    fflush(stdin);
    scanf("%d", &id);

    indice = buscarId(id, pArrayListEmployee);

    if(indice != -1)
    {
        auxEmp = (Employee*)ll_get(pArrayListEmployee, indice);

        mostrarEmployee(auxEmp);

        error = submenuModificar(auxEmp);
    }


    if(error == 0)
    {
        r = 1;
        printf("\nDatos modificados con exito!!\n\n");
    }
    else
    {
        printf("\nError al modificar el empleado\n\n");
    }


    return r;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int r = -1;
    int id;
    int indice;
    char seguro;
    Employee* auxEmp;

    printf("Ingrese el id del empleado a eliminar: ");
    fflush(stdin);
    scanf("%d", &id);

    indice = buscarId(id, pArrayListEmployee);

    if(indice == -1)
    {
        printf("ID incorrecta\n\n");
    }
    else
    {
        auxEmp = (Employee*)ll_get(pArrayListEmployee, indice);
        mostrarEmployee(auxEmp);
        printf("Seguro que desea eliminar este empleado? s/n: ");
        fflush(stdin);
        scanf("%c", &seguro);
        if(seguro == 's')
        {
            ll_remove(pArrayListEmployee, indice);
            printf("Empleado eliminado con exito!\n\n");
            r = 1;
        }
        else if(seguro == 'n')
        {
            printf("No se ha eliminado al empleado\n\n");
            r = 1;
        }
        else
        {
            printf("Error, es 's' o 'n'\n\n");
            r = 1;
        }
    }

    return r;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int r;

    r = mostrarEmployees(pArrayListEmployee);

    return r;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int r;

    r = submenuSorts(pArrayListEmployee);

    return r;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int r = 1;
    int tam = ll_len(pArrayListEmployee);
    FILE* f;
    Employee* auxEmp;

    f = fopen(path, "w");

    if(f == NULL)
    {
        printf("Error al abrir el archivo\n\n");
    }
    else
    {
        fprintf(f, "id,nombre,horasTrabajadas,sueldo\n");

        for(int i=0; i<tam; i++)
        {
            auxEmp = (Employee*)ll_get(pArrayListEmployee, i);
            fprintf(f, "%d,%s,%d,%d \n", auxEmp->id, auxEmp->nombre, auxEmp->horasTrabajadas, auxEmp->sueldo);
            r = 1;
        }
    }

    if(r == 1)
    {
        printf("Se han guardado con exito!!\n\n");
    }

    fclose(f);

    return r;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int r = -1;
    FILE* f;
    int tam;
    tam = ll_len(pArrayListEmployee);
    Employee* auxEmp;

    f = fopen(path, "wb");

    if(f == NULL)
    {
        printf("Ha ocurrido un error\n\n");
    }
    else
    {
        for(int i = 0; i<tam; i++)
        {
            auxEmp = (Employee*)ll_get(pArrayListEmployee, i);
            fwrite(auxEmp, sizeof(Employee), 1, f);
            r = 1;
        }
    }

    if(r == 1)
    {
        printf("Se han guardado con exito!!\n\n");
    }

    return r;
}



