#include <stdio.h>
#include <stdlib.h>
#include "../include/polinomio.h"

void mostrarMenu(void) {
    printf("\n----- CALCULADORA DE POLINOMIOS -----\n");
    printf("Seleccione una opcionn: ");
    printf("1. Insertar termino en P1\n");
    printf("2. Insertar termino en P2\n");
    printf("3. Mostrar polinomios\n");
    printf("4. Sumar P1 + P2\n");
    printf("5. Multiplicar P1 * P2\n");
    printf("6. Evaluar P1\n");
    printf("7. Evaluar P2\n");
    printf("8. Salir\n");

}

void insertarEnPolinomio(Polinomio *p, const char *nombre) {
    float coeficiente;
    int exponente;

    printf("\nIngrese el coeficiente del termino: ");
    if (scanf("%f", &coeficiente) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Ingrese el exponente del termino: ");
    if (scanf("%d", &exponente) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }

    insertarTermino(p, coeficiente, exponente);

    printf("Termino insertado en %s.\n", nombre);
}

void mostrarPolinomio(Polinomio *p, const char *nombre) {
    char *texto = polinomioToString(p);

    if (texto == NULL) {
        printf("Error al convertir %s a texto.\n", nombre);
        return;
    }

    printf("%s = %s\n", nombre, texto);

    free(texto);
}

void evaluar(Polinomio *p, const char *nombre) {
    float x;
    float resultado;

    printf("\nIngrese el valor de x: ");
    if (scanf("%f", &x) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }

    resultado = evaluarPolinomio(p, x);

    printf("%s(%g) = %g\n", nombre, x, resultado);
}

int main(void) {
    Polinomio *p1;
    Polinomio *p2;
    int opcion;

    p1 = crearPolinomio();
    p2 = crearPolinomio();

    if (p1 == NULL || p2 == NULL) {
        printf("Error al crear los polinomios.\n");

        destruirPolinomio(p1);
        destruirPolinomio(p2);

        return 1;
    }

    do {
        mostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1:
                insertarEnPolinomio(p1, "P1");
                break;

            case 2:
                insertarEnPolinomio(p2, "P2");
                break;

            case 3:
                printf("\n");
                mostrarPolinomio(p1, "P1");
                mostrarPolinomio(p2, "P2");
                break;

            case 4: {
                Polinomio *suma = sumarPolinomios(p1, p2);

                if (suma == NULL) {
                    printf("Error al sumar los polinomios.\n");
                    break;
                }

                printf("\nResultado de P1 + P2:\n");
                mostrarPolinomio(suma, "Suma");

                destruirPolinomio(suma);
                break;
            }

            case 5: {
                Polinomio *producto = multiplicarPolinomios(p1, p2);

                if (producto == NULL) {
                    printf("Error al multiplicar los polinomios.\n");
                    break;
                }

                printf("\nResultado de P1 * P2:\n");
                mostrarPolinomio(producto, "Producto");

                destruirPolinomio(producto);
                break;
            }

            case 6:
                evaluar(p1, "P1");
                break;

            case 7:
                evaluar(p2, "P2");
                break;

            case 8:
                printf("Bye : )\n");
                break;

            default:
                printf("Error fatal.\n");
                break;
        }

    } while (opcion != 8);

    destruirPolinomio(p1);
    destruirPolinomio(p2);

    return 0;
}
