/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:12:26 by efelaous          #+#    #+#             */
/*   Updated: 2024/08/17 01:15:22 by efelaous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strcmp(char *arg, char *str)
{
	while(*arg)
	{
		if (*str != *arg)
			return 0;
		str++;
		arg++;
	}
	return 1;
}

double check_double(double arg)
{
	if (arg < -2 || arg > 2)
		error("Argument must be a double\n");
	return arg;
}

void error(char *error)
{
    write(1, "\033[31m", 6); 
    while (*error) {
        write(1, error, 1);
        error++;
    }
    write(1, "\033[0m\n", 5);
    exit(1);
}

unsigned int map_colors(unsigned int x, unsigned int x_max)
{
	float r, g, b, ratio;

	if (x > x_max)
		x = x_max;
	if (x <= x_max / 3)
	{
		ratio = (float)x / ((float)x_max / 3);
		r = 0x80 * (1 - ratio) + 0x10 * ratio;
		g = 0x00 * (1 - ratio) + 0x8E * ratio;
		b = 0x80 * (1 - ratio) + 0xC4 * ratio;
	}
	else if (x > x_max / 3 && x <= (x_max / 3)*2)
	{
		ratio = (float)(x - (float)x_max / 3) / ((float)x_max / 3);
		r = 0x10 * (1 - ratio) + 0x48 * ratio;
		g = 0x8E * (1 - ratio) + 0xA3 * ratio;
		b = 0xC4 * (1 - ratio) + 0x9A * ratio;
	}
	else {
		ratio = (float)(x - ((float)x_max / 3*2)) / ((float)x_max / 3);
		r = 0x48 * (1 - ratio) + 0xDC * ratio;
		g = 0xA3 * (1 - ratio) + 0x14 * ratio;
		b = 0x9A * (1 - ratio) + 0x3C * ratio;
	}
	return (unsigned int)(((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b);
}
double ft_atodbl(const char *str)
{
	int		sign;
	double	result;
	double	divisor;
	
	sign = 1;
	divisor = 1;
    result = 0.0;

    while (*str == ' ')
		++str;
	if (*str == '\0')
		error("Wrong Value");
	while ('+' == *str || '-' == *str)
		if ('-' == *str++)
			sign = -sign;
	while(*str != '.' && (((*str >= '0' && *str <= '9') || *str == '.')))
		result = result * 10.0 + (*str++ - '0');	
	if ('.' == *str)
		++str;
	while (*str >= '0' && *str <= '9')
	{
		divisor *= 10;
		result += (*str++ - '0') / divisor;
	}
	while (*str == ' ')
        ++str;
    
    if (*str != '\0')
        error("Wrong value");
    return sign * result;
}