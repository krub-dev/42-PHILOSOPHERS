#include "philosophers.h"

// Verifica que un string contenga solo dígitos
// Devuelve 1 si solo contiene dígitos, 0 si contiene caracteres no numéricos
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Parsea los argumentos de la línea de comandos y asigna los valores a la estructura de datos
// Convierte strings a enteros usando atol y verifica que sean números válidos
// Devuelve 0 si todo es correcto, 1 si hay error en los argumentos
static int	parse_args(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: Arguments must be int\n");
			return (1);
		}
		i++;
	}
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->meals_required = -1;
	if (argc == 6)
		data->meals_required = ft_atol(argv[5]);
	
	if (data->num_philos <= 0 || data->time_to_die <= 0 || 
		data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
		(argc == 6 && data->meals_required <= 0))
	{
		printf("Error: Arguments must be positive integers\n");
		return (1);
	}
	return (0);
}

// Inicializa la estructura de datos compartidos para la simulación
// Reserva memoria para los mutexes de los tenedores y los inicializa
// Configura el mutex de impresión y establece el tiempo de inicio
// Devuelve 0 en éxito, 1 en error
int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	memset(data, 0, sizeof(t_data));
	if (parse_args(data, argc, argv))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = get_current_time();
	return (0);
}

// Inicializa las estructuras de los filósofos con sus datos individuales
// Asigna memoria para el array de filósofos y configura sus atributos
// Establece los punteros a los tenedores izquierdo y derecho de cada filósofo
// Devuelve 0 en éxito, 1 en error
int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		(*philos)[i].last_meal_time = data->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].is_dead = 0;
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
