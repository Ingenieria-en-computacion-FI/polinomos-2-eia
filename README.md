[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Xb5XzbAV)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=23887572&assignment_repo_type=AssignmentRepo)
# edaI_polinomios
# Proyecto — TAD Polinomio con Listas Doblemente Ligadas

## Descripción

En este proyecto se implementará un Tipo Abstracto de Datos (TAD) Polinomio utilizando listas doblemente ligadas en lenguaje C.

El polinomio deberá:

- Mantener orden descendente por exponente
- Simplificar términos semejantes automáticamente
- Eliminar términos cuyo coeficiente sea cero
- Permitir operaciones algebraicas básicas

---

# Estructura del repositorio

```text
.
├── include/
│   └── polinomio.h
│
├── student/
│   └── polinomio.c
│
├── tests/
│   └── test_runner.c
│
├── .github/
│   └── workflows/
│       └── autograding.yml
│
└── README.md
```

## Archivos que debe modificar el estudiante

```
Solo los que estan en src
```

## Archivos que NO deben modificarse

No se deben modificar los siguientes archivos

```
include/polinimo.h
tests/test_runner.c
tests/test_all.c
```
Modificar dichos archivos puede provocar:
  - errores de compilación
  - fallos en la autoevaluación
  - pérdida de puntos

## Funcionalidades requeridas

El proyecto debe implementar correctamente:

  - Creación de polinomios
  - Inserción ordenada
  - Simplificación de términos semejantes
  - Eliminación de términos
  - Evaluación numérica
  - Suma de polinomios
  - Multiplicación de polinomios
  - Conversión a cadena
## Restricciones
  - Uso obligatorio de listas doblemente ligadas
  - Manejo dinámico de memoria
  - No usar arreglos para almacenar términos
  - No modificar estructuras definidas en el header
  
## Consideraciones importantes
  ### Orden
  Los términos deben mantenerse SIEMPRE en orden descendente.

  Ejemplo:
  ```
  5x^5+3x^2+x+1
```
  ### Simplificación automática

Al insertar términos con el mismo exponente:
```
3x^2 + 5x^2
```
debe obtenerse:
```
8x^2
```
### Eliminación automática

Si un término resulta con coeficiente cero:
```
3x^2 - 3x^2
```
el término debe eliminarse automáticamente.

## Evaluación automática

El proyecto será evaluado automáticamente mediante GitHub Actions.

Cada push ejecutará:

  - compilación automática
  - pruebas automáticas
  - validación de resultados
    
## Recomendaciones
  - Implementar primero la lista doblemente ligada
  - Verificar cuidadosamente enlaces anterior/siguiente
  - Probar inserciones en:
        - inicio
        - medio
        - final
  - Verificar memoria dinámica correctamente

## Entrega

La entrega se realiza mediante commits y pushes al repositorio asignado en GitHub Classroom.

