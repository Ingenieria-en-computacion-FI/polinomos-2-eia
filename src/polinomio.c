#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/polinomio.h"

static void agregarTexto(char **cadena, size_t *capacidad, const char *texto) {
    size_t longitudActual;
    size_t longitudTexto;
    size_t nuevaLongitud;
    char *temporal;

    if (*cadena == NULL || texto == NULL) {
        return;
    }

    longitudActual = strlen(*cadena);
    longitudTexto = strlen(texto);
    nuevaLongitud = longitudActual + longitudTexto + 1;

    if (nuevaLongitud > *capacidad) {
        while (nuevaLongitud > *capacidad) {
            *capacidad *= 2;
        }

        temporal = realloc(*cadena, *capacidad);

        if (temporal == NULL) {
            free(*cadena);
            *cadena = NULL;
            *capacidad = 0;
            return;
        }

        *cadena = temporal;
    }

    strcat(*cadena, texto);
}

Nodo* crearNodo(float coef, int exp){
    Nodo* nuevo = malloc(sizeof(Nodo));
    if (nuevo==NULL){
        return NULL;
    }
    nuevo->termino.coeficiente=coef;
    nuevo->termino.exponente =exp;
    nuevo->siguiente = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo){
    Nodo *actual;
    if (p==NULL || nuevo ==NULL){
        return;
    }
    if(p->cabeza==NULL){
        p->cabeza = nuevo;
        p->cola = nuevo;
        return;
    }
    if(nuevo->termino.exponente < p->cola->termino.exponente){
        nuevo->anterior = p->cola;
        p->cola->siguiente=nuevo;
        p->cola = nuevo;
        return;
    }
    actual=p->cabeza;

    while(actual!=NULL && actual->termino.exponente > nuevo->termino.exponente){
        actual = actual->siguiente;
    }

    if(actual != NULL && actual->termino.exponente == nuevo->termino.exponente){
        actual->termino.coeficiente += nuevo->termino.coeficiente;
        free(nuevo);

        if (actual->termino.coeficiente==0){
            eliminarNodo(p, actual->termino.exponente);
        }
        return;

    }
    nuevo->siguiente=actual;
    nuevo->anterior=actual->anterior;
    
    if(actual->anterior!=NULL){
        actual->anterior->siguiente = nuevo;

    }
    actual->anterior=nuevo;
}

void eliminarNodo(Polinomio* p, int exp){
    Nodo *actual;
    if(p==NULL || p->cabeza==NULL){
        return;
    }
    actual=p->cabeza;

    while(actual!=NULL && actual->termino.exponente!= exp){
        actual=actual->siguiente;

    }
    if(actual->siguiente!=NULL){
        actual->siguiente->anterior = actual->anterior;
    }else{
        p->cola=actual->anterior;
    }
    free(actual);
}

Polinomio* crearPolinomio(void){
    Polinomio* p = malloc(sizeof(Polinomio));
    if(p==NULL){
        return NULL;
    }
    p->cabeza=NULL; 
    p->cola=NULL;
    return p;
}

void insertarTermino(Polinomio* p, float coef, int exp){
    Nodo *actual;
    Nodo *nuevo;

    if (p == NULL || coef == 0) {
        return;
    }

    actual = p->cabeza;

    while (actual != NULL) {
        if (actual->termino.exponente == exp) {
            actual->termino.coeficiente += coef;

            if (actual->termino.coeficiente == 0) {
                eliminarNodo(p, exp);
            }

            return;
        }

        actual = actual->siguiente;
    }

    nuevo = crearNodo(coef, exp);

    if (nuevo == NULL) {
        return;
    }

    insertarNodoOrdenado(p, nuevo);
}


float evaluarPolinomio(Polinomio *p, float x) {
    Nodo *actual;
    float resultado = 0.0f;

    if (p == NULL) {
        return 0.0f;
    }

    actual = p->cabeza;

    while (actual != NULL) {
        float potencia = 1.0f;
        int i;

        for (i = 0; i < actual->termino.exponente; i++) {
            potencia *= x;
        }

        resultado += actual->termino.coeficiente * potencia;

        actual = actual->siguiente;
    }

    return resultado;
}

Polinomio *sumarPolinomios(Polinomio *p1, Polinomio *p2) {
    Polinomio *resultado;
    Nodo *actual;

    resultado = crearPolinomio();

    if (resultado == NULL) {
        return NULL;
    }

    if (p1 != NULL) {
        actual = p1->cabeza;

        while (actual != NULL) {
            insertarTermino(
                resultado,
                actual->termino.coeficiente,
                actual->termino.exponente
            );

            actual = actual->siguiente;
        }
    }

    if (p2 != NULL) {
        actual = p2->cabeza;

        while (actual != NULL) {
            insertarTermino(
                resultado,
                actual->termino.coeficiente,
                actual->termino.exponente
            );

            actual = actual->siguiente;
        }
    }

    return resultado;
}

Polinomio *multiplicarPolinomios(Polinomio *p1, Polinomio *p2) {
    Polinomio *resultado;
    Nodo *actual1;
    Nodo *actual2;
    float nuevoCoef;
    int nuevoExp;

    resultado = crearPolinomio();

    if (resultado == NULL) {
        return NULL;
    }

    if (p1 == NULL || p2 == NULL) {
        return resultado;
    }

    actual1 = p1->cabeza;

    while (actual1 != NULL) {
        actual2 = p2->cabeza;

        while (actual2 != NULL) {
            nuevoCoef = actual1->termino.coeficiente * actual2->termino.coeficiente;
            nuevoExp = actual1->termino.exponente + actual2->termino.exponente;

            insertarTermino(resultado, nuevoCoef, nuevoExp);

            actual2 = actual2->siguiente;
        }

        actual1 = actual1->siguiente;
    }

    return resultado;
}

char *polinomioToString(Polinomio *p) {
    Nodo *actual;
    char *cadena;
    size_t capacidad = 128;
    int primero = 1;

    cadena = malloc(capacidad);

    if (cadena == NULL) {
        return NULL;
    }

    cadena[0] = '\0';

    if (p == NULL || p->cabeza == NULL) {
        strcpy(cadena, "0");
        return cadena;
    }

    actual = p->cabeza;

    while (actual != NULL) {
        float coef = actual->termino.coeficiente;
        int exp = actual->termino.exponente;
        char termino[80];

        if (coef != 0) {
            termino[0] = '\0';

            if (coef > 0 && !primero) {
                strcat(termino, "+");
            }

            if (exp == 0) {
                char numero[40];

                snprintf(numero, sizeof(numero), "%g", coef);
                strcat(termino, numero);
            } else {
                if (coef == 1.0f) {
                    /*
                       Si el coeficiente es 1, no se escribe el 1.
                       Ejemplo: 1x^2 se escribe como x^2.
                    */
                } else if (coef == -1.0f) {
                    strcat(termino, "-");
                } else {
                    char numero[40];

                    snprintf(numero, sizeof(numero), "%g", coef);
                    strcat(termino, numero);
                }

                strcat(termino, "x");

                if (exp != 1) {
                    char exponente[40];

                    snprintf(exponente, sizeof(exponente), "^%d", exp);
                    strcat(termino, exponente);
                }
            }

            agregarTexto(&cadena, &capacidad, termino);

            if (cadena == NULL) {
                return NULL;
            }

            primero = 0;
        }

        actual = actual->siguiente;
    }

    if (strlen(cadena) == 0) {
        strcpy(cadena, "0");
    }

    return cadena;
}

void destruirPolinomio(Polinomio *p) {
    Nodo *actual;
    Nodo *siguiente;

    if (p == NULL) {
        return;
    }

    actual = p->cabeza;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    free(p);
}
