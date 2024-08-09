# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achak <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 18:33:45 by achak             #+#    #+#              #
#    Updated: 2024/08/09 18:43:38 by achak            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRC		= src
SRCS		= src/main.c src/parse_file.c src/params.c src/ft_list_funcs.c \
		  src/exit_funcs.c src/helper_funcs.c src/init_xpm_and_colours.c \
		  src/error_checking.c src/parse_map_arr.c \
		  src/keys_and_continuous_movement.c \
		  src/player_movement.c src/find_texture_x_coord_and_dir.c \
		  src/find_real_wall_height.c \
		  src/find_distances_and_intercept_coords.c \
		  src/find_initial_intercept_dists_and_coords.c \
		  src/find_horizontal_intercept_dist_to_wall.c \
		  src/shoot_win_width_nbr_of_rays.c src/ray_utils.c
OBJ		= obj
OBJS		= $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
CC		= cc
CFLAGS		= -Wall -Werror -Wextra
INCLD		= includes
LFLAGS		= -L$(INCLD)/mlx_linux -L$(INCLD)/libft \
		  -I$(INCLD) -lm -lmlx -lXext -lX11 -lft
LIBFT		= $(INCLD)/libft/libft.a
LIBFT_PATH	= $(INCLD)/libft
MLX		= $(INCLD)/mlx_linux/libmlx.a
MLX_PATH	= $(INCLD)/mlx_linux
RM		= rm

all:	$(NAME)

asan:	CFLAGS	+= -g -fsanitize=address
asan:	fclean
asan:	$(NAME)

#efence:	CFLAGS	+= -g
#efence:	LFLAGS	+= -Lincludes/e_fence -lefence
#efence:	fclean
#efence:	$(NAME)

$(NAME):$(OBJ) $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(FSAN) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(OBJ)/%.o:$(SRC)/%.c
	$(CC) -c $(CFLAGS) -I$(INCLD) -I$(INCLD)/mlx_linux -I$(LIBFT_PATH) $^ -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean
	$(RM) -rf $(OBJ)
	#$(RM) $(OBJS)

fclean:	clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all asan clean fclean re
