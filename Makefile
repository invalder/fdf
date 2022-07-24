# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 14:05:51 by nnakarac          #+#    #+#              #
#    Updated: 2022/07/24 15:31:31 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = includes
LIB_DIR = libft/
# MLX_DIR = mlx/

# INCS = -Iincludes/ -I$(LIB_DIR)includes/ -I$(MLX_DIR)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_DIR		= minilibx-linux
	MLX_FLAGS	= -Imlx_Linux -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm -lz
	INCS		= -I$(INC_DIR) \
				  -I$(LIB_DIR)includes \
				  -I/usr/include
	LIBS		= -L$(LIB_DIR) -lft \
				  -L/usr/lib
else
	MLX_DIR		= minilibx_macos
	# MLX_DIR		= minilibx_mms_20191025_beta
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx \
				  -framework OpenGL \
				  -framework AppKit
	INCS		= -I$(INC_DIR) \
				  -I$(LIB_DIR)includes \
				  -I$(MLX_DIR)
	LIBS		= -L$(LIB_DIR) -lft
endif

SRCS =  fdf.c \
		fdf_utils.c \
		fdf_err.c \
		fdf_input_chk.c \
		fdf_init_map.c \
		fdf_mlx_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(addprefix $(OBJ_DIR),$(OBJS))
		@make -C $(LIB_DIR) --silent
		@make -C $(MLX_DIR) --silent
		@$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

clean:
	@make -C $(LIB_DIR) clean --silent
	@make -C $(MLX_DIR) clean --silent
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean --silent

re: fclean all

.PHONY: fclean all clean re fdf
