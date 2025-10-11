#include "philosophers.h"

// Valida los argumentos de la línea de comandos para la simulación
// Devuelve 0 si son correctos, 1 si hay error
static int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Use: %s <num_philos> <time_to_die>", argv[0]);
		printf(" <time_to_eat> <time_to_sleep> [meals_required]\n");
		return (1);
	}
	return (0);
}

// Inicializa la simulación llamando a init_data e init_philos
// Devuelve 0 en éxito, 1 en error
static int	init_simulation(t_data *data, t_philo **philos, int argc, 
	char **argv)
{
	if (init_data(data, argc, argv) || init_philos(data, philos))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	return (0);
}

// Crea los hilos de los filósofos y los inicia en philo_routine
static void	create_philo_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
}

// Espera a que todos los hilos de filósofos terminen
static void	wait_philo_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

// Función principal: valida argumentos, inicializa, 
// lanza hilos y monitor, espera y limpia
int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor_thread;

	if (validate_args(argc, argv))
		return (1);
	if (init_simulation(&data, &philos, argc, argv))
		return (1);
	create_philo_threads(&data, philos);
	pthread_create(&monitor_thread, NULL, monitor_routine, philos);
	pthread_join(monitor_thread, NULL);
	wait_philo_threads(&data, philos);
	cleanup(&data, philos);
	return (0);
}
