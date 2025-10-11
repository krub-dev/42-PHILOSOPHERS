<h1 align="center">
  <img src="https://iili.io/KNDwcgt.png" alt="philo header krub" width="1200" height="auto" style="align: bottom;"> 
</h1>

Implementación del clásico problema de los filósofos comensales utilizando threads y mutexes en C. Este proyecto explora conceptos fundamentales de programación concurrente como sincronización de hilos, prevención de deadlocks y gestión de recursos compartidos.

## Descripción

El problema de los filósofos comensales es un clásico problema de sincronización que ilustra los desafíos de la programación concurrente. Varios filósofos están sentados alrededor de una mesa circular, alternando entre pensar, comer y dormir. Para comer, cada filósofo necesita dos tenedores (uno a cada lado), pero solo hay un tenedor entre cada par de filósofos adyacentes.

### Objetivos

- Implementar una solución eficiente sin deadlocks
- Gestionar correctamente threads y mutexes
- Sincronizar el acceso a recursos compartidos
- Detectar cuando un filósofo muere de hambre

## Estructura del Proyecto

```
42-PHILOSOPHERS/
├── .gitignore
├── Makefile
├── README.md
├── routines.md          # Documentación de rutinas
├── test_philo.sh        # Script de pruebas
├── DOCS/
│   ├── en.norm.pdf      # Normas en inglés
│   ├── es.subject.pdf   # Subject en español
│   └── norm.md          # Normas en markdown
├── INCLUDE/
│   └── philosophers.h   # Cabeceras del proyecto
└── SRC/
    ├── cleanup.c        # Limpieza de recursos
    ├── init.c           # Inicialización
    ├── main.c           # Punto de entrada
    ├── monitor.c        # Monitoreo de filósofos
    ├── routine.c        # Rutinas de los filósofos
    └── utils.c          # Funciones auxiliares
```

## Compilación e Instalación

### Requisitos

- gcc, clang, cc
- Make
- Sistema operativo compatible con POSIX threads (Linux, macOS)

### Compilar el proyecto

```bash
make
```

### Limpiar archivos objeto

```bash
make clean
```

### Limpiar todo (incluido el binario)

```bash
make fclean
```

### Recompilar desde cero

```bash
make re
```

## Uso

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parámetros

- `number_of_philosophers`: Número de filósofos (y tenedores)
- `time_to_die`: Tiempo en ms antes de que un filósofo muera sin comer
- `time_to_eat`: Tiempo en ms que tarda un filósofo en comer
- `time_to_sleep`: Tiempo en ms que tarda un filósofo en dormir
- `[number_of_times_each_philosopher_must_eat]`: (Opcional) Número de veces que cada filósofo debe comer antes de terminar

### Ejemplos

```bash
# 5 filósofos, mueren en 800ms, comen en 200ms, duermen en 200ms
./philo 5 800 200 200

# 4 filósofos, mueren en 410ms, comen en 200ms, duermen en 200ms, cada uno come 5 veces
./philo 4 410 200 200 5

# Test sin muertes
./philo 4 500 200 200

# Test que debería fallar (un filósofo muere)
./philo 4 310 200 100
```

## Conceptos Clave

### Threads (Hilos)

Cada filósofo es representado por un thread independiente que ejecuta su rutina de forma concurrente.

### Mutexes

Los tenedores son protegidos por mutexes para evitar que dos filósofos tomen el mismo tenedor simultáneamente.

### Sincronización

El programa debe:
- Evitar **deadlocks** (bloqueos mutuos)
- Evitar **race conditions** (condiciones de carrera)
- Detectar cuando un filósofo muere de hambre

### Estados del Filósofo

1. **Pensando** - El filósofo está pensando
2. **Tomando tenedores** - Intenta tomar los dos tenedores
3. **Comiendo** - Come durante `time_to_eat` milisegundos
4. **Durmiendo** - Duerme durante `time_to_sleep` milisegundos
5. **Muerto** - Ha pasado `time_to_die` sin comer

## Testing

El proyecto incluye un script de pruebas:

```bash
./test_philo.sh
```

Este script ejecuta múltiples casos de prueba para verificar el correcto funcionamiento del programa.

## Arquitectura del Código

### main.c
Punto de entrada del programa. Parsea argumentos, inicializa estructuras y lanza los threads.

### init.c
Inicializa la estructura de datos, los mutexes y los filósofos.

### routine.c
Contiene la rutina principal que ejecuta cada filósofo (pensar, comer, dormir).

### monitor.c
Monitorea el estado de los filósofos para detectar muertes.

### cleanup.c
Libera recursos, destruye mutexes y limpia memoria.

### utils.c
Funciones auxiliares (obtención de tiempo, impresión de estados, etc.).

## Recursos Adicionales

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Mutex Tutorial](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

## Autor

**krub-dev** - [GitHub Profile](https://github.com/krub-dev)
