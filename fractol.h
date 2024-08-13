/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:16:50 by efelaous          #+#    #+#             */
/*   Updated: 2024/08/13 03:00:56 by efelaous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# ifndef FRACTOL_H
# define FRACTOL_H

# ifndef MAX_ITERATIONS
# define MAX_ITERATIONS 50
# endif

# ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 800
# endif

# ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT 800
# endif

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>


typedef struct {
    void	*mlx;
    void	*win;
    void	*img;
    char	*img_data;
    int		bpp;
    int		size_line;
    int		endian;
    int		color;
    double	zoom;
    int		width;
    int		height;
    int		max_iterations;
    int     fractal_type;
    double  julia_c_real;
    double  julia_c_imag;
} tdata;


int             ft_strcmp(char *arg, char *str);
unsigned int    map_colors(unsigned int x, unsigned int x_max);
int             mandelbrot_iterations(double real, double imag, int max_iterations);
double          ft_atodbl(const char *str);
double          check_double(double arg);
void            error(char *error);
int             handle_mouse(int button, int x, int y, tdata *data);
int             close_window(tdata *data);
int             handle_key(int keysym, tdata *data);
void            draw_mandelbrot(tdata *data);
void            draw_julia(tdata *data);
void            mandelbrot(tdata *data);
void            julia(tdata *data, int argc, char **argv);

# endif