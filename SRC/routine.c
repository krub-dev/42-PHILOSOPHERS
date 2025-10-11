#include "philosophers.h"

// Gestiona la toma de tenedores y la comida del filósofo
// Maneja el caso especial de 1 filósofo para evitar deadlock
static void	philo_take_forks_and_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	safe_print("has taken a fork", philo);
	if (data->num_philos == 1)
	{
		while (!data->simulation_end)
			precise_usleep(1);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	safe_print("has taken a fork", philo);
	safe_print("is eating", philo);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	precise_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// Rutina principal de cada filósofo: pensar, comer, dormir
// Se ejecuta en bucle hasta que alguien muere o todos han comido lo suficiente
void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->simulation_end)
	{
		safe_print("is thinking", philo);
		philo_take_forks_and_eat(philo);
		if (data->simulation_end || philo->is_dead)
			break ;
		safe_print("is sleeping", philo);
		precise_usleep(data->time_to_sleep);
	}
	return (NULL);
}
