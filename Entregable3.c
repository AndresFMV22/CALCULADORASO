#include <stdio.h>  // Entrada y salida estándar (printf, scanf)
#include <stdlib.h> // Funciones generales (exit)
#include <string.h> // Manejo de cadenas (strcmp, strlen, strchr)
#include <math.h>   // Funciones matemáticas (sin, cos, tan)

#define MAX 8 //  Tamaño máximo de la pila (8 niveles)

/*
    Aca ponermo un arreglo que representa la pila de la calculadora RPN.
    Cada posición almacena un valor.
*/
float stack[MAX];

/*
    Aca tenemos la variable que indica la cima de la pila.
    -1 indica que la pila está vacía.
*/
int top = -1;

/*
    Aca tenemos la funcion que muestra la pila completa en la terminal.
    Se imprimen siempre los 8 niveles, aunque estén vacíos,
    para simular el comportamiento de una calculadora HP.
*/
void mostrar_pila()
{
    printf("\n");
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (i <= top)
            printf("%d. %.6f\n", i + 1, stack[i]);
        else
            printf("%d. 0.000000\n", i + 1);
    }
    printf("\n");
}

/*
    Función push:
    Inserta un valor en la cima de la pila.
    Valida que no se exceda el tamaño máximo.
*/
void push(float value)
{
    if (top < MAX - 1)
    {
        stack[++top] = value;
    }
    else
    {
        // Error si la pila ya está llena
        printf("Math Error\n");
    }
}

/*
    Función pop:
    Extrae el valor de la cima de la pila.
    Retorna 1 si fue exitoso y 0 si la pila está vacía.
*/
int pop(float *value)
{
    if (top >= 0)
    {
        *value = stack[top--];
        return 1;
    }
    else
    {
        // Error si se intenta sacar de una pila vacía
        printf("Math Error\n");
        return 0;
    }
}

/*
    Elimina únicamente el último valor ingresado en la pila.
*/
void clear_last()
{
    if (top >= 0)
        top--;
}

/*
    Limpia completamente la pila.
*/
void clear_all()
{
    top = -1;
}

int main()
{
    int opcion;   // Opción del menú
    float a, b;   // Operandos
    float result; // Resultado de la operación
    char op[10];  // Operador o función ingresada

    printf("Calculadora RPN estilo HP\n");

    /*
        Aca tenemos el bucle principal del programa.
        Permite interacción continua hasta que el usuario decida salir.
    */
    while (1)
    {

        // Mostrar el estado actual de la pila
        mostrar_pila();

        // Menú de opciones
        printf("¿Qué desea hacer?\n");
        printf("1. Ingresar número\n");
        printf("2. Seleccionar operación\n");
        printf("3. Limpiar último\n");
        printf("4. Limpiar todo\n");
        printf("5. Salir\n");
        printf("> ");
        scanf("%d", &opcion);

        switch (opcion)
        {

        // Opción para ingresar un número a la pila
        case 1:
            printf("Ingrese número: ");
            scanf("%f", &a);
            push(a);
            break;

        // Opción para seleccionar una operación
        case 2:
            printf("Operación (+ - * / sin cos tan): ");
            scanf("%s", op);

            /*
                Operaciones binarias:
                Requieren dos operandos de la pila.
            */
            if (strlen(op) == 1 && strchr("+-*/", op[0]))
            {

                if (!pop(&b) || !pop(&a))
                    break;

                // Validación de división por cero
                if (op[0] == '/' && b == 0)
                {
                    printf("Math Error\n");
                    push(a);
                    push(b);
                    break;
                }

                // Ejecución de la operación
                switch (op[0])
                {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                }

                // Se guarda el resultado en la pila
                push(result);
            }

            /*
                Funciones trigonométricas:
                Requieren un solo operando.
            */
            else if (
                strcmp(op, "sin") == 0 ||
                strcmp(op, "cos") == 0 ||
                strcmp(op, "tan") == 0)
            {

                if (!pop(&a))
                    break;

                if (strcmp(op, "sin") == 0)
                    result = sin(a);
                else if (strcmp(op, "cos") == 0)
                    result = cos(a);
                else
                    result = tan(a);

                push(result);
            }
            else
            {
                printf("Operación inválida\n");
            }
            break;

        // Elimina el último valor ingresado
        case 3:
            clear_last();
            break;

        // Limpia toda la pila
        case 4:
            clear_all();
            break;

        // Finaliza el programa
        case 5:
            return 0;

        default:
            printf("Opción inválida\n");
        }
    }
}
