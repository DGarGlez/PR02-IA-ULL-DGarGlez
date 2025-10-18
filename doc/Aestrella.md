# Implementación del algoritmo A* en el proyecto

Este documento resume de forma breve cómo se ha creado e implementado el algoritmo de búsqueda A* dentro del proyecto.

## Archivos relevantes
- `src/og/include/labyrinth.h`: contiene la implementación del laberinto, la representación de las celdas (`Cell`), obtención de vecinos, y la función `AStarSearch` que ejecuta el algoritmo.
- `src/og/aux_functions.cc`: funciones auxiliares usadas por la búsqueda dinámica y la gestión de nodos en simulaciones dinámicas.
- `src/og/include/aux_functions.h`: declaraciones de utilidades para la búsqueda y el manejo dinámico de obstáculos.

## Estructura y conceptos principales
- Representación: El laberinto se almacena como un vector de vectores de `Cell`. Cada `Cell` contiene información de posición, tipo (`kind`: libre, muro, inicio, fin, camino), y valores de A* (g, h, f).

- Listas de trabajo:
  - `open_nodes`: nodos que están pendientes de exploración (frontera).
  - `closed_nodes`: nodos ya inspeccionados.
  - `generated`: registro de todos los nodos generados durante la búsqueda (útil para análisis/depuración).

- Padres y reconstrucción:
  - Se mantiene un vector `parents` con pares (hijo, padre) para reconstruir el camino final una vez alcanzado el nodo destino.
  - La función `ConstructPath` reconstruye el camino desde el destino hasta el inicio consultando ese vector.

## Cálculo de costes y heurística
- Coste de movimiento:
  - Movimiento ortogonal: coste 5
  - Movimiento diagonal: coste 7
  Estos costes se usan para actualizar g(n) en `CalculateValues`.

- Heurísticas soportadas:
  - Distancia Manhattan (opción 1)
  - Distancia Euclidiana (opción 2)
  La heurística elegida se aplica en cada nodo con `CalculateHeuristic`, y f = g + h.

## Algoritmo A*
1. Inicialización: se inicia `open_nodes` con el nodo inicio y se calcula su heurística y f.
2. Bucle principal: mientras haya nodos en `open_nodes` y no se exceda un límite de iteraciones:
   - Seleccionar el nodo con menor f (ordenando `open_nodes` por f).
   - Moverlo a `closed_nodes`.
   - Si es el destino, reconstruir el camino y terminar.
   - Para cada vecino válido:
     - Si está en `closed_nodes` o no es transitable, ignorarlo.
     - Si no está en `open_nodes`, calcular g,h,f, añadirlo a `open_nodes` y registrar el padre.
     - Si ya está en `open_nodes`, comprobar si el nuevo camino es mejor y actualizar valores y padre si procede.
3. Si no quedan nodos en `open_nodes`, no existe camino.

## Consideraciones de implementación
- Ordenación de `open_nodes`: se utiliza `SortByFValue` para reordenar los nodos pendientes por su valor f.
- Vecinos inválidos: se manejan celdas fuera de rango o muros como vecinos inválidos (representados internamente como `Cell(-1,-1,1)`).
- Robustez: existe un límite de iteraciones para prevenir bucles infinitos (`max_iter`).

## Extensiones dinámicas
- El proyecto incluye lógica para simulaciones con obstáculos dinámicos. Tras cada paso del agente se puede modificar aleatoriamente el laberinto y volver a ejecutar A* desde la posición actual.
- La función `StoreSearchDynamic` y utilidades en `aux_functions.cc` gestionan estos cambios, respetando límites máximos de obstáculos y asegurando que los nodos inicio y fin no se conviertan en muros.
