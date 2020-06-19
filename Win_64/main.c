#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int menu();

int main()
{
    int option = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    /*Employee* auxiliarEmployee;

    //printf("Cant: %d\n", ll_len(listaEmpleados));

    auxiliarEmployee = employee_newParametros("1234", "Andres", "40", "45000");
    ll_add(listaEmpleados, auxiliarEmployee); //Agrega un empleado a la lista

    auxiliarEmployee = employee_newParametros("4862", "Juana", "54", "70000");
    ll_add(listaEmpleados, auxiliarEmployee);

    auxiliarEmployee = employee_newParametros("3249", "Daniela", "49", "58000");
    ll_add(listaEmpleados, auxiliarEmployee);

    mostrarEmployees(listaEmpleados);

    ll_remove(listaEmpleados, 1); //Elimina un empleado de la lista

    mostrarEmployees(listaEmpleados);

    //printf("Cant: %d\n", ll_len(listaEmpleados));

    auxiliarEmployee = (Employee*)ll_get(listaEmpleados, 1);

    employee_setSueldo(auxiliarEmployee, (auxiliarEmployee->sueldo * 1.5));

    mostrarEmployees(listaEmpleados);

    ll_sort(listaEmpleados, compararEmpleadosPorId, 1);

    mostrarEmployees(listaEmpleados);*/

    int r;

    do{
        switch(menu())
        {
            case 1:
                r = controller_loadFromText("data.csv", listaEmpleados);
                if(r == -1)
                {
                    exit(EXIT_FAILURE);
                }
                break;

            case 2:
                r = controller_loadFromBinary("data.bin", listaEmpleados);
                if(r == -1)
                {
                    exit(EXIT_FAILURE);
                }
                break;
            case 3:
                controller_addEmployee(listaEmpleados);
                break;
            case 4:
                r = controller_editEmployee(listaEmpleados);
                break;
            case 5:
                r = controller_removeEmployee(listaEmpleados);
                if(r == -1)
                {
                    exit(EXIT_FAILURE);
                }
                break;
            case 6:
                mostrarEmployees(listaEmpleados);
                break;
            /*case 8:
                r = controller_saveAsText("data.csv", listaEmpleados);
                if(r == -1)
                {
                    exit(EXIT_FAILURE);
                }
                break;*/
            default:
                printf("Opcion incorrecta\n\n");
        }
    }while(option != 10);

    ll_deleteLinkedList(listaEmpleados);

    return 0;
}

int menu()
{
    int opcion;
    printf("\n\n");
    printf("*** MENU DE OPCIONES ***\n\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
    printf("3. Alta de empleado.\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");


    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");

    printf("\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}
