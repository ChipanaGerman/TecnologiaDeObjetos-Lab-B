# Laboratorio 01: Tecnología de Objetos - Programación en Scala

Este repositorio contiene la solución al ejercicio de conteo de cambio (vuelto) de forma recursiva, aplicando los conceptos de programación funcional en Scala.

## Preguntas y Respuestas

### 1. Explique el caso base implementado.
En esta implementación, la función `countChange` consolida el control de la recursividad en dos bloques lógicos que actúan como casos base:

*   **El caso de éxito (`if (money == 0)`):** Se activa cuando las restas sucesivas del valor de las monedas igualan exactamente el monto objetivo. Al retornar **1**, la pila de llamadas contabiliza que esta rama específica representa una combinación válida para el vuelto.
*   **El caso de falla unificado (`else if (money < 0 || coins.isEmpty)`):** Agrupa matemáticamente dos escenarios de invalidez mediante un operador lógico OR:
    *   `money < 0`: Indica que la última moneda restada excedió la cantidad objetivo.
    *   `coins.isEmpty`: Indica que la lista de denominaciones se agotó sin haber logrado reducir el dinero a cero.
    
En cualquiera de estos subcasos, se retorna **0** para podar el árbol de recursión y descartar ese camino.

---

### 2. ¿Este problema se resuelve mejor en el modelo de programación funcional?
**Sí.** Aunque el código incluye un bloque imperativo en el `main` para la interacción con el usuario mediante `StdIn`, la función principal `countChange` está modelada puramente bajo el paradigma funcional, lo cual es ideal por lo siguiente:

*   **Ausencia de Estado Mutable:** No se utilizan variables contadoras locales o globales, ni bucles tradicionales (`for`/`while`). El estado fluye naturalmente a través de los parámetros en cada llamada recursiva.
*   **Estructuras Inmutables:** El uso de las propiedades funcionales de la lista en Scala (`head` para el primer elemento y `tail` para el resto) permite dividir el problema de forma elegante sin necesidad de manejar índices, punteros, ni mutar la estructura de datos original.
*   **Transparencia Referencial:** La función es matemáticamente pura. Para una misma entrada de `money` y `coins`, siempre producirá la misma salida y no genera efectos secundarios (*side-effects*), lo que hace que la lógica combinatoria sea predecible y fácilmente testeable.

---

### 3. ¿Qué beneficios se podrían obtener para este problema utilizando memoización?
La función implementada realiza dos llamadas recursivas por iteración. Esto genera un árbol de ejecución con subproblemas superpuestos (se recalculan combinaciones idénticas de dinero restante y lista de monedas múltiples veces). Aplicar memoización otorgaría las siguientes ventajas de ingeniería:

*   **Optimización de la Complejidad Temporal:** El tiempo de ejecución se reduciría de una escala exponencial a una pseudo-polinomial $O(M \times N)$ (donde $M$ es el monto y $N$ la cantidad de monedas). La función recuperaría valores del caché en tiempo constante $O(1)$ en lugar de expandir ramas redundantes.
*   **Estabilidad ante Entradas Dinámicas:** Dado que el programa ahora permite ingresos arbitrarios del usuario vía teclado (`StdIn`), valores de dinero altos y listas largas de monedas podrían causar un error de desbordamiento de pila (*Stack Overflow*) en una recursión pura. La memoización mitigaría drásticamente la profundidad de la pila de llamadas, garantizando que el sistema escale y no colapse ante entradas grandes.