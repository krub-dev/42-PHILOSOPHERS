#include "philosophers.h"

// isdigit: Verifica si un carácter es un dígito
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// ft_atol: Convierte una cadena a un número entero largo
long	ft_atol(const char *str)
{
	size_t	i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}


// Obtiene el tiempo actual en milisegundos (con gettimeofday)
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Versión simple de usleep
// Recibe milisegundos y los convierte a microsegundos para usleep
void	precise_usleep(long ms)
{
	usleep(ms * 1000);
}

// Imprime mensajes sincronizados (evita mezclas en la salida)
// Usa un mutex para garantizar que solo un filósofo imprime a la vez
// No imprime nada si la simulación ha terminado, excepto el mensaje de muerte
void	safe_print(char *msg, t_philo *philo)
{
	int	is_death_msg;

	is_death_msg = (msg[0] == 'd' && msg[1] == 'i' && 
		msg[2] == 'e' && msg[3] == 'd' && msg[4] == '\0');
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_end || is_death_msg)
	{
		printf("%ld %d %s\n", get_current_time() - philo->data->start_time,
			philo->id, msg);
		if (is_death_msg)
			philo->data->simulation_end = 1;
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
