/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:04:18 by efelaous          #+#    #+#             */
/*   Updated: 2024/08/17 00:08:12 by efelaous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window(tdata *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
    return 0;
}

int handle_key(int keysym, tdata *data)
{
    if (keysym == XK_Escape)
{
       close_window(data);
    }
    return 0;
}

int handle_mouse(int button, int x, int y, tdata *data)
{
    (void)x;
    (void)y;
    if (button == 4)
    {
        data->zoom *= 1.2;
    } else if (button == 5)
    {
        data->zoom /= 1.2;
    }

    if (data->fractal_type == 1)
        draw_mandelbrot(data);
    else if (data->fractal_type == 2)
        draw_julia(data);

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}

tdata init( tdata data)
{
    data.mlx = mlx_init();
    if (!data.mlx)
    {
        write(2, "Failed to initialize mlx\n", 25);
        exit(1);
    }
    data.win = mlx_new_window(data.mlx, data.width, data.height, "Mandelbrot Fractal");
    if (!data.win)
    {
        write(2, "Failed to create window\n", 24);
        exit(1);
    }
    data.img = mlx_new_image(data.mlx, data.width, data.height);
    data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
    return data;
}
int main(int argc, char **argv)
{
    tdata data;

    if (argc <= 1)
        error("No Paramter Was Passed\nPlease insert the desired fractol set\nEither: manedlbrot\nOr: julia r i\nExample: ./fractol julia 0 -1\n");
    data.width = SCREEN_WIDTH;
    data.height = SCREEN_HEIGHT;
    data.max_iterations = MAX_ITERATIONS;
    data.zoom = 1;
    data = init(data);
    if (ft_strcmp(argv[1], "mandelbrot"))
	{
		if (argc != 2)
			error("Mandelbrot takes no arguments");
        mandelbrot(&data);
	}
    else if (ft_strcmp(argv[1], "julia"))
        julia(&data, argc, argv);
    else
        error("Wrong Set Argument Please Specify: mandelbrot or julia\n");
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_mouse_hook(data.win, handle_mouse, &data);
    mlx_loop(data.mlx);
    return 0;
}
