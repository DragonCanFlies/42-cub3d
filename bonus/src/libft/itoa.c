/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:21:47 by latabagl          #+#    #+#             */
/*   Updated: 2026/02/02 16:21:49 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_number_length(int n)
{
	int	digits;

	digits = 0;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static	char	*ft_build_array(char *result, int n, int len)
{
	unsigned int	nb;
	int				i;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	i = len - 1;
	while (nb != 0)
	{
		result[i] = '0' + (nb % 10);
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*result;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_number_length(n);
	if (n < 0)
		len++;
	result = (char *) malloc (len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	return (ft_build_array(result, n, len));
}
