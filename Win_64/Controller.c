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
    FILE* f = fopen(path, "r");

    if(f == NULL)
    {
        printf("Problema al abrir el archivo\n");
        return -1;
    }
    else
    {
        parser_EmployeeFromText(f, pArrayListEmployee);
    }

    return 1;
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

    fscanf(f, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
    printf("%s                 %s     %s    %s\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    while(!feof(f))
    {
        cant = fscanf(f, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

        if(cant == 4)
        {
            printf("%s    %20s       %s             %s\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        }
        else
        {
            break;
        }
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
    int todoOk = 0;
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

    for(int i=0; i<tam; i++)
    {
        auxEmp = (Employee*)ll_get(pArrayListEmployee, i);
        if(auxEmp == NULL)
        {
            auxEmp = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
            ll_add(pArrayListEmployee, auxEmp);
            todoOk = 1;
            break;
        }
    }

    if(todoOk == 1)
    {
        printf("Empleado registrado con exito!!!\n");
    }
    else
    {
        printf("No se ha cargado el empleado\n");
    }

    return 1;
}

int submenuModificar()
{
    int todoOk = 0;
    int opcion;

    printf("\n*** Que desea modificar? ***\n\n");
    printf("1. Nombre\n");
    printf("2. Horas Trabajadas\n");
    printf("3. Sueldo\n");
    printf("\n\n");

    do
    {
        printf("Ingrese opcion: ");
        fflush(stdin);
        scanf("%d", &opcion);

        if(opcion == 1 || opcion == 2 || opcion == 3)
        {
            todoOk = 1;
        }
        else
        {
            printf("Error, ingrese opcion: ");
            fflush(stdin);
            scanf("%d", &opcion);
        }
    }while(todoOk != 1);

    return opcion;

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
    int id;
    int todoOk = 0;
    int todoOkNombre = 0;
    int todoOkHorasTrabajadas = 0;
    int todoOkSueldo = 0;
    int tam = ll_len(pArrayListEmployee);
    char nombre[20];
    int horasTrabajadas;
    int sueldo;
    Employee* auxEmp;

    mostrarEmployees(pArrayListEmployee);

    printf("\nIngrese el ID del empleado a modificar: ");
    scanf("%d", &id);

    for(int i=0; i<tam; i++)
    {
        auxEmp = ll_get(pArrayListEmployee, i);

        if(auxEmp->id == id && auxEmp != NULL)
        {
            mostrarEmployee(auxEmp);
            switch(submenuModificar())
            {
                case 1:     do
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
                            if(todoOkNombre == 1)
                            {
                                strcpy(auxEmp->nombre, nombre);
                                todoOk = 1;
                            }

                            break;

                case 2:     do
                            {
                                printf("Ingrese nuevas horas trabajadas: ");
                                fflush(stdin);
                                scanf("%d", &horasTrabajadas);

                                if(horasTrabajadas > 2 && horasTrabajadas < 800)
                                {
                                    todoOkHorasTrabajadas = 1;
                                }
                                else
                                {
                                    printf("Error, ingrese nuevas horas trabajadas: ");
                                    fflush(stdin);
                                    scanf("%d", &horasTrabajadas);
                                }
                            }while(todoOkHorasTrabajadas != 1);
                            if(todoOkHorasTrabajadas == 1)
                            {
                                auxEmp->horasTrabajadas = horasTrabajadas;
                                todoOk = 1;
                            }
                            break;

                case 3:     do
                            {
                                printf("Ingrese sueldo: ");
                                fflush(stdin);
                                scanf("%d", &sueldo);

                                if(sueldo > 0 && sueldo < 800000)
                                {
                                    todoOkSueldo = 1;
                                }
                                else
                                {
                                    printf("Error, ingrese sueldo: ");
                                    fflush(stdin);
                                    scanf("%d", &sueldo);
                                }
                            }while(todoOkSueldo != 1);
                            if(todoOkSueldo == 1)
                            {
                                auxEmp->sueldo = sueldo;
                                todoOk = 1;
                            }
                            break;

                default: break;

            }
        }
    }

    if(todoOk == 1)
    {
        printf("\nDatos modificados con exito!!\n\n");
    }
    else
    {
        printf("\nError al modificar el empleado\n\n");
    }


    return 1;
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
    return 1;
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
    return 1;
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
    return 1;
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

    return 1;
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
    return 1;
}



