# Patrón Consonante-Vocal - Optimización mediante Divide y Vencerás

Proyecto desarrollado como parte de la asignatura **Algorítmos y Estructuras de Datos** del Grado en Ingeniería Informática.

**Autoras:** María Ballester Martínez y Lucía Olmos Martínez  
**Fecha de creación:** Mayo de 2024

---

## Descripción

Este proyecto resuelve de forma eficiente el problema de encontrar la subcadena más larga compuesta por parejas consecutivas de caracteres que sigan el patrón **Consonante-Vocal** dentro de una cadena de texto $C$ de tamaño $n$.

Para garantizar un rendimiento óptimo frente a grandes volúmenes de datos ($n \ge 170.000$), el núcleo del problema se ha abordado utilizando el paradigma de diseño de algoritmos **Divide y Vencerás (DyV)**, reduciendo drásticamente el tiempo de computación comparado con una solución por fuerza bruta.

---

## Características

- Algoritmo recursivo basado en el paradigma Divide y Vencerás.
- Tratamiento eficiente y combinación de soluciones en el paso de división/fusión.
- **Estudio Empírico:** Módulo de recolección de tiempos de ejecución para contrastar la complejidad teórica con la práctica.
- Automatización del proceso de compilación y pruebas mediante `makefile`.

---

## Tecnologías utilizadas

- C++ 
- GNU Make 
- Herramientas de análisis experimental y benchmarking de tiempos de CPU

---

## Estructura del proyecto

├── doc/
│   └── Memoria práctica 1.pdf 
├── src/
│   └── consonante-vocal.cpp
├── data/
│   ├── aleatorio.txt
│   ├── mejor.txt
│   └── peor.txt
├── makefile
└── README.md

---

## Requisitos

- Sistema operativo Linux / Ubuntu (o entorno compatible con soporte para `make`).
- Compilador de C++ (`g++`).