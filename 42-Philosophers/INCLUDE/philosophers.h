#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>    // Para hilos y mutexes
# include <stdio.h>      // Para printf
# include <stdlib.h>     // Para malloc/free
# include <unistd.h>     // Para usleep
# include <sys/time.h>   // Para gettimeofday
# include <string.h>     // Para memset

typedef struct s_data {
    int             num_philos;      // Número total de filósofos
    int             time_to_die;     // Tiempo máximo sin comer (ms)
    int             time_to_eat;     // Tiempo que tarda en comer (ms)
    int             time_to_sleep;   // Tiempo que tarda en dormir (ms)
    int             meals_required;  // Comidas requeridas (opcional)
    int             simulation_end;  // Flag de fin de simulación
    pthread_mutex_t *forks;          // Array de tenedores (mutexes)
    pthread_mutex_t print_mutex;     // Mutex para imprimir seguro
    long            start_time;      // Tiempo de inicio (ms)
} t_data;

typedef struct s_philo {
    int             id;              // ID del filósofo (1 a N)
    pthread_t       thread;          // Hilo del filósofo
    pthread_mutex_t *left_fork;      // Puntero a tenedor izquierdo
    pthread_mutex_t *right_fork;     // Puntero a tenedor derecho
    long            last_meal_time;  // Última vez que comió (ms)
    int             meals_eaten;     // Veces que ha comido
    int             is_dead;         // Flag que indica si este filósofo murió
    t_data          *data;           // Puntero a datos compartidos
} t_philo;

// ----- Funciones principales -----
int     init_data(t_data *data, int argc, char **argv);  // Inicializa estructura data
int     init_philos(t_data *data, t_philo **philos);     // Inicializa filósofos
void    *philo_routine(void *arg);                       // Rutina de cada filósofo
void    *monitor_routine(void *arg);                     // Monitoriza muertes

// ----- Utils -----
long    get_current_time(void);               // Obtiene tiempo actual en ms
void    safe_print(char *msg, t_philo *philo); // Print con mutex
void    precise_usleep(long ms);              // Usleep preciso
int     is_digit(char c);                     // Verifica si un carácter es un dígito
long    ft_atol(const char *str);             // Convierte string a long

// ----- Limpieza -----
void    cleanup(t_data *data, t_philo *philos); // Libera recursos

#endif