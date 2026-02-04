#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 8

float stack[MAX];
int top = -1;

/* Mostrar pila */
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

/* Push */
void push(float value)
{
    if (top < MAX - 1)
    {
        stack[++top] = value;
    }
    else
    {
        printf("Math Error\n");
    }
}

/* Pop */
int pop(float *value)
{
    if (top >= 0)
    {
        *value = stack[top--];
        return 1;
    }
    else
    {
        printf("Math Error\n");
        return 0;
    }
}

/* Limpiar último */
void clear_last()
{
    if (top >= 0)
        top--;
}

/* Limpiar todo */
void clear_all()
{
    top = -1;
}

int main()
{
    int opcion;
    float a, b, result;
    char op[10];

    printf("Calculadora RPN estilo HP\n");

    while (1)
    {
        mostrar_pila();

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
        case 1:
            printf("Ingrese número: ");
            scanf("%f", &a);
            push(a);
            break;

        case 2:
            printf("Operación (+ - * / sin cos tan): ");
            scanf("%s", op);

            /* Operadores binarios */
            if (strlen(op) == 1 && strchr("+-*/", op[0]))
            {
                if (!pop(&b) || !pop(&a))
                    break;

                if (op[0] == '/' && b == 0)
                {
                    printf("Math Error\n");
                    push(a);
                    push(b);
                    break;
                }

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
                push(result);
            }
            /* Trigonométricas */
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

        case 3:
            clear_last();
            break;

        case 4:
            clear_all();
            break;

        case 5:
            return 0;

        default:
            printf("Opción inválida\n");
        }
    }
}
