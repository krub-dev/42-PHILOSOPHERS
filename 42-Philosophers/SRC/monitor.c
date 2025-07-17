#include "philosophers.h"

// Verifica si algún filósofo ha muerto de hambre
// Devuelve 1 si un filósofo ha muerto, 0 si todos siguen vivos
static int	check_death(t_philo *philos)
{
	int     i;
	long    current_time;

	i = 0;
	while (i < philos->data->num_philos)
	{
		current_time = get_current_time();
		if (current_time - philos[i].last_meal_time > philos->data->time_to_die)
		{
			philos[i].is_dead = 1;
			safe_print("died", &philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

// Verifica si todos han comido suficiente (si meals_required != -1)
// Devuelve 1 si todos han comido lo suficiente, 0 en caso contrario
static int	check_meals(t_philo *philos)
{
	int	i;

	if (philos->data->meals_required == -1)
		return (0);
	i = 0;
	while (i < philos->data->num_philos)
	{
		if (philos[i].meals_eaten < philos->data->meals_required)
			return (0);
		i++;
	}
	return (1);
}

// Hilo de monitorización (ejecutado en paralelo)
// Controla si algún filósofo ha muerto o si todos han comido suficiente
void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_death(philos))
			return (NULL);
		if (check_meals(philos))
		{
			// Marcamos el fin de la simulación
			philos->data->simulation_end = 1;
			return (NULL);
		}
		usleep(1000);
	}
}
