#include <unistd.h>

int	ft_get_digits(int num)
{
	int	number_of_digits;

	number_of_digits = 0;
	if (num == 0)
		return (0);
	if (num < 0)
		num = -num;
	while (num != 0)
	{
		num /= 10;
		number_of_digits++;
	}
	return (number_of_digits);
}

int	ft_check(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (1);
	}
	else if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (0);
}

void	ft_reverse_write(char *num_str, int counter)
{
	while (counter >= 0)
	{
		write(1, &num_str[counter], 1);
		counter--;
	}
}

void	ft_putnbr(int nb)
{
	char	num_str[11];
	int		counter;
	int		negative;

	negative = 0;
	if (ft_check(nb) == 1)
		return ;
	if (nb < 0)
	{
		nb = -nb;
		negative = 1;
	}
	counter = 0;
	while (nb > 0)
	{
		num_str[counter] = (nb % 10) + '0';
		counter++;
		nb = nb / 10;
	}
	counter--;
	if (negative == 1)
		write(1, "-", 1);
	ft_reverse_write(num_str, counter);
}
