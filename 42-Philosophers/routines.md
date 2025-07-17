1. Sin límite de comidas (solo termina si alguien muere)

./philo 5 800 200 200

Comportamiento esperado:
Los filósofos comen y piensan indefinidamente.
El programa solo termina si algún filósofo muere (por ejemplo, si los tiempos son muy ajustados).
Si nadie muere, el programa sigue ejecutándose.

2. Con límite de comidas (termina cuando todos han comido lo suficiente)

./philo 5 800 200 200 3

Comportamiento esperado:
Cada filósofo debe comer 3 veces.
Cuando todos han comido 3 veces, la simulación termina sin imprimir ningún mensaje extra.
Si algún filósofo muere antes de alcanzar las comidas requeridas, se imprime el mensaje de muerte y termina.

3. Un solo filósofo (caso borde)

./philo 1 800 200 200

Comportamiento esperado:
El filósofo no puede comer (solo hay un tenedor).
El filósofo muere tras time_to_die milisegundos.
Se imprime el mensaje de muerte y el programa termina.

4. Tiempos ajustados (probable muerte rápida)

./philo 2 300 200 200

Comportamiento esperado:
Es probable que algún filósofo muera porque el tiempo para morir es muy bajo comparado con comer/dormir.
Se imprime el mensaje de muerte y el programa termina.

5. Todos comen rápido y terminan

./philo 3 1000 100 100 2

Comportamiento esperado:
Cada filósofo debe comer 2 veces.
Si nadie muere antes, el programa termina cuando todos han comido 2 veces, sin imprimir mensaje extra.