/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:30:17 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/21 09:52:19 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	nbr_digits(long int n)
{
	int	numdigit;

	numdigit = 1;
	while (n / 10)
	{
		numdigit++;
		n = n / 10;
	}
	return (numdigit);
}

static int	divisor_(long int num)
{
	int	divisor;

	divisor = 1;
	while (num / divisor >= 10)
		divisor *= 10;
	return (divisor);
}

static char	*ft_transform(char *str, int n, int divisor, int i)
{
	int long	num;
	int			len;

	num = (long)n;
	len = nbr_digits(num) + i + 1;
	while (num >= 10)
	{
		str[len - 2] = num % 10 + '0';
		num /= 10;
		len--;
		divisor /= 10;
	}
	str[len - 2] = num % 10 + '0';
	len = nbr_digits(n) + i + 1;
	str[len - 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	int			signe;
	long int	num;
	int			divisor;
	char		*str;

	i = 0;
	signe = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		i = 1;
		signe = -1;
		n = -n;
	}
	num = (long)n;
	str = (char *)malloc((nbr_digits(num) + i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (signe < 0)
		str[0] = '-';
	divisor = divisor_(num);
	return (ft_transform(str, n, divisor, i));
}
