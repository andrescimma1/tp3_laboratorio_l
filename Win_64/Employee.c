#include "Employee.h"

Employee* employee_new()
{
    Employee* newEmployee;
    newEmployee = (Employee*)malloc(sizeof(Employee));

    if(newEmployee != NULL)
    {
        newEmployee->id = 0;
        strcpy(newEmployee->nombre, "");
        newEmployee->horasTrabajadas = 0;
        newEmployee->sueldo = 0;
    }

    return newEmployee;
}


Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
    Employee* newEmployee;

    newEmployee = employee_new();

    if(newEmployee != NULL)
    {
        if(employee_setId(newEmployee, atoi(idStr))
        || employee_setNombre(newEmployee, nombreStr)
        || employee_setHorasTrabajadas(newEmployee, atoi(horasTrabajadasStr))
        || employee_setSueldo(newEmployee, atoi(sueldoStr)))
        {
            free(newEmployee);
            newEmployee = NULL;
        }
    }

    return newEmployee;
}


void employee_delete();

int employee_setId(Employee* this,int id)
{
    int error = 1;

    if(this != NULL && id >= 0 && id <= 20000)
    {
        this->id = id;
        error = 0;
    }

    return error;
}

int employee_getId(Employee* this,int* id)
{
    int error = 1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        error = 0;
    }

    return error;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int error = 1;

    if(this != NULL && strlen(nombre) >= 3 && strlen(nombre) < 20)
    {
        strcpy(this->nombre, nombre);
        error = 0;
    }

    return error;
}


int employee_getNombre(Employee* this,char* nombre)
{
    int error = 1;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        error = 0;
    }

    return error;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int error = 1;

    if(this != NULL && horasTrabajadas >= 1 && horasTrabajadas <= 1000)
    {
        this->horasTrabajadas = horasTrabajadas;
        error = 0;
    }

    return error;
}


int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int error = 1;

    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        error = 0;
    }

    return error;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int error = 1;

    if(this != NULL && sueldo >= 5000 && sueldo <= 100000)
    {
        this->sueldo = sueldo;
        error = 0;
    }

    return error;
}


int employee_getSueldo(Employee* this,int* sueldo)
{
    int error = 1;

    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        error = 0;
    }

    return error;
}


int mostrarEmployee(Employee* employee)
{
    int error = 1;

    if(employee != NULL)
    {
        printf("%d  %10s     %d                   %d\n", employee->id, employee->nombre, employee->horasTrabajadas, employee->sueldo);
        error = 0;
    }

    return error;
}


int mostrarEmployees(LinkedList* lista)
{
    int error = 1;
    int flag = 0;

    int tam = ll_len(lista); //Contiene el tamaño de la lista
    Employee* auxEmp;

    if(lista != NULL)
    {
        printf("ID         NOMBRE    HORAS TRABAJADAS     SUELDO\n");
        printf("------------------------------------------------\n");
        for(int i=0; i<tam; i++)
        {
            auxEmp = (Employee*)ll_get(lista, i); //Mediante el indice obtiene la ubicacion del empleado
            if(auxEmp != NULL)
            {
                mostrarEmployee(auxEmp);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            printf("No hay empleados para mostrar\n");
        }
        printf("\n\n");
        error = 0;
    }

    return error;
}

int submenuModificar(Employee* auxEmpp)
{
    int todoOk = 0;
    int opcion;
    int error = 1;
    char nombre[20];
    int horasTrabajadas;
    int sueldo;

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

    switch(opcion)
    {
        case 1:     do
                        {
                            printf("Ingrese nombre: ");
                            fflush(stdin);
                            gets(nombre);

                            error = employee_setNombre(auxEmpp, nombre);

                            if(error == 1)
                            {
                                printf("Error, ingrese nombre: ");
                                fflush(stdin);
                                gets(nombre);

                                error = employee_setNombre(auxEmpp, nombre);
                            }
                        }while(error != 0);
                        break;

            case 2:     do
                        {
                            printf("Ingrese nuevas horas trabajadas: ");
                            fflush(stdin);
                            scanf("%d", &horasTrabajadas);

                            error = employee_setHorasTrabajadas(auxEmpp, horasTrabajadas);

                            if(error == 1)
                            {
                                printf("Error, ingrese nuevas horas trabajadas: ");
                                fflush(stdin);
                                scanf("%d", &horasTrabajadas);

                                error = employee_setHorasTrabajadas(auxEmpp, horasTrabajadas);
                            }
                        }while(error != 0);
                        break;

            case 3:     do
                        {
                            printf("Ingrese sueldo: ");
                            fflush(stdin);
                            scanf("%d", &sueldo);

                            error = employee_setSueldo(auxEmpp, sueldo);

                            if(error == 1)
                            {
                                printf("Error, ingrese sueldo: ");
                                fflush(stdin);
                                scanf("%d", &sueldo);

                                error = employee_setSueldo(auxEmpp, sueldo);
                            }
                        }while(error != 0);
                        break;

            default: break;
    }

    return error;

}


int compararEmpleadosPorId(void* emp1, void* emp2)
{
    int rta;
    Employee* a = (Employee*)emp1;
    Employee* b = (Employee*)emp2;

    if(a->id == b->id)
    {
        rta = 0;
    }
    else if(a->id > b->id)
    {
        rta = -1;
    }
    else
    {
        rta = 1;
    }

    return rta;
}

int compararEmpleadosPorNombre(void* emp1, void* emp2)
{
    int rta;
    Employee* a = (Employee*)emp1;
    Employee* b = (Employee*)emp2;

    if(strcmp(a->nombre, b->nombre) == 0)
    {
        rta = 0;
    }
    else if(strcmp(a->nombre, b->nombre) > 1)
    {
        rta = -1;
    }
    else
    {
        rta = 1;
    }

    return rta;
}

int compararEmpleadosPorHorasTrabajadas(void* emp1, void* emp2)
{
    int rta;
    Employee* a = (Employee*)emp1;
    Employee* b = (Employee*)emp2;

    if(a->horasTrabajadas == b->horasTrabajadas)
    {
        rta = 0;
    }
    else if(a->horasTrabajadas > b->horasTrabajadas)
    {
        rta = -1;
    }
    else
    {
        rta = 1;
    }

    return rta;
}

int compararEmpleadosPorSueldo(void* emp1, void* emp2)
{
    int rta;
    Employee* a = (Employee*)emp1;
    Employee* b = (Employee*)emp2;

    if(a->sueldo == b->sueldo)
    {
        rta = 0;
    }
    else if(a->sueldo > b->sueldo)
    {
        rta = -1;
    }
    else
    {
        rta = 1;
    }

    return rta;
}


int buscarId(int id, LinkedList* pArrayListEmployee)
{
    int indice = -1;
    int salir = 0;
    int tam = ll_len(pArrayListEmployee);
    Employee* auxEmpp;


    if(pArrayListEmployee != NULL && salir == 0)
    {
        for(int i=0; i<tam; i++)
        {
            auxEmpp = (Employee*)ll_get(pArrayListEmployee, i);
            if(auxEmpp->id == id)
            {
                indice = i;
                printf("Entra");
                break;
            }
        }

    }



    return indice;
}
