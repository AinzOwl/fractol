# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efelaous <efelaous@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 02:47:38 by efelaous          #+#    #+#              #
#    Updated: 2024/08/13 02:52:01 by efelaous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
SRCS = fractol.c julia.c mandelbrot.c libft.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = fractol

# minilibx Path
MINILIBX_DIR = minilibx-linux

# Define the default rule
all: $(TARGET)

# Rule to run make inside minilibx-linux
$(MINILIBX_DIR)/libmlx_Linux.a:
	cd $(MINILIBX_DIR) && $(MAKE)

# Rule to compile the source files
$(TARGET): $(MINILIBX_DIR)/libmlx_Linux.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean object files and the target executable
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
