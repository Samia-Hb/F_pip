/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:10:19 by shebaz            #+#    #+#             */
/*   Updated: 2023/11/20 12:32:10 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_div(int n, int divisor)
{
	while (n / divisor >= 10)
		divisor *= 10;
	return (divisor);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	divisor;

	divisor = 1;
	if (n == 0)
	{
		ft_putchar('0', fd);
		return ;
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = -n;
	}
	divisor = ft_div(n, divisor);
	while (divisor > 0)
	{
		ft_putchar(n / divisor + '0', fd);
		n %= divisor;
		divisor /= 10;
	}
}
