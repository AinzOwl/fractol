/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:18:41 by efelaous          #+#    #+#             */
/*   Updated: 2024/08/13 02:31:26 by efelaous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mandelbrot_iterations(double real, double imag, int max_iterations)
{
	double	zr, zi, temp;
	int		iterations;

	zr = 0;
	zi = 0;
	iterations = 0;
	while ((hypot(zr, zi) )<= 2.0 && iterations < max_iterations)
{
		temp = zr * zr - zi * zi + real;
		zi = 2 * zr * zi + imag;
		zr = temp;
		iterations++;
	}
	return iterations;
}

void draw_mandelbrot(tdata *data)
{
	int				x, y, iterations, pixel_index;
	double			real, imag;
	unsigned int	color;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			real = (x - data->width / 2.0) * 4.0 / (data->zoom * data->width);
			imag = (y - data->height / 2.0) * 4.0 / (data->zoom * data->height);
			iterations = mandelbrot_iterations(real, imag, data->max_iterations);
			color = map_colors(iterations, data->max_iterations);
			pixel_index = (y * data->size_line) + (x * (data->bpp / 8));
			data->img_data[pixel_index] = color & 0xFF;           // Blue
			data->img_data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
			data->img_data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
			data->img_data[pixel_index + 3] = (color >> 24) & 0xFF; // Alpha
			x++;
		}
		y++;
	}
}

void mandelbrot(tdata *data)
{
	data->fractal_type = 2;
 	draw_mandelbrot(data);
}
