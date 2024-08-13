/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:14 by efelaous          #+#    #+#             */
/*   Updated: 2024/08/13 02:31:26 by efelaous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

int julia_iterations(double real, double imag, double creal, double cimag, int max_iterations)
{
	double	zr;
	double	zi;
	int		iterations;
	double	temp;

	zr = real;
	zi = imag;
	iterations = 0;
	while ((hypot(zr, zi) )<= 2.0 && iterations < max_iterations)
{
		temp = zr * zr - zi * zi + creal;
		zi = 2 * zr * zi + cimag;
		zr = temp;
		iterations++;
	}
	return iterations;
}

void draw_julia(tdata *data)
{
	int x, y, pixel_index, iterations;
	double real, imag;
	unsigned int color;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			real = (x - data->width / 2.0) * 4.0 / (data->zoom * data->width);
			imag = (y - data->height / 2.0) * 4.0 / (data->zoom * data->height);
			iterations = julia_iterations(real, imag, data->julia_c_real, data->julia_c_imag, data->max_iterations);
			color = map_colors(iterations, data->max_iterations);
			pixel_index = (y * data->size_line) + (x * (data->bpp / 8));
			data->img_data[pixel_index] = color & 0xFF;
			data->img_data[pixel_index + 1] = (color >> 8) & 0xFF;
			data->img_data[pixel_index + 2] = (color >> 16) & 0xFF;
			data->img_data[pixel_index + 3] = (color >> 24) & 0xFF;
			x++;
		}
		y++;
	}
}

void julia(tdata *data, int argc, char **argv)
{
    if (argc != 4)
        error("Julia take 2 doubles as argument\nExample: ./fractol julia 0 -1\n");
    data->fractal_type = 2;  
    data->julia_c_real = check_double(ft_atodbl(argv[2]));
    data->julia_c_imag = check_double(ft_atodbl(argv[3]));
    draw_julia(data);
}
