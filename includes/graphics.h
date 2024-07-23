/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:57:29 by achak             #+#    #+#             */
/*   Updated: 2024/07/09 15:08:50 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

# define FOV 1.0472
# define ERROR 1
# define WIN_WIDTH 720
# define WIN_HEIGHT 500
# define PLAYER_SIZE 8
# define TEXTURES_NBR 4
# define TURN_SPEED 0.005
# define MOVE_SPEED 1
# define ONE_DEGREE 0.0174533
# define BLACK_PIXEL 0x00000000
# define WHITE_PIXEL 0x00FFFFFF
# define GREY_PIXEL 0x00808080
# define RED_PIXEL 0x00FF0000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x00002BFF
# define YELLOW_PIXEL 0x00FFEF00
# define VERTICAL 10
# define HORIZONTAL 11
# define CLEANUP -1
# define X 1
# define Y 0
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define MAP_COMPONENT 4
# define FLOOR 5
# define CEILING 6
# define INVALID 7
# define MAP_GRID 64
# define SHADE_DIST_LIMIT 100.0
# define RECURSION_LIMIT 300000

typedef struct s_image
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		colour;
	char	*data_addr;
}	t_image;

typedef struct s_cub_list
{
	struct s_cub_list	*next;
	void				*data;
}	t_cub_list;

typedef struct s_key_flags
{
	bool	w_flag;
	bool	s_flag;
	bool	a_flag;
	bool	d_flag;
	bool	left_flag;
	bool	right_flag;
}	t_key_flags;

typedef struct s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		image;
	t_image		textures[4];
	float		player_x;
	float		player_y;
	float		player_angle;
	float		x_nearest;
	float		y_nearest;
	float		diff_x;
	float		diff_y;
	float		x_intercept;
	float		corresponding_y_coord;
	float		corresponding_x_coord;
	float		y_intercept;
	float		distance_x;
	float		distance_y;
	float		real_wall_height;
	bool		exceed_win_height;
	float		texture_x;
	int			texture_dir;
	int			wall_side;
	int			sign_x;
	int			sign_y;
	int			map_x;
	int			map_y;
	int			floor_colour;
	int			ceiling_colour;
	char		*xpm_files[4];
	char		**map_arr;
	bool		done_parsing_map;
	t_cub_list	*begin_list;
	t_key_flags	key_flags;
}	t_params;

//	ft_list_functions.c
int		ft_list_size(t_cub_list *begin_list);
void	ft_list_clear(t_cub_list *begin_list, void (*free_fct)(void *));
void	ft_list_push_back(t_params *params, int fd, t_cub_list **begin_list,
			void *data);

//	error_checking.c
bool	if_empty_line_skip(t_params *params, char *str);
void	check_errors_in_str(t_params *params, char *str, int fd);

//	init_xpm_and_colours.c
int		init_floor_and_ceil_colours(t_params *params, char *str, int identifer,
			int fd);
int		init_xpm_files(t_params *params, char *str, int direction, int fd);

//	exit_funcs.c
void	ft_exit(t_params *params, int exit_code);
void	ft_error(t_params *params, const char *msg);
void	ft_perror(t_params *params, const char *msg);
int		func_exit(t_params *params);

//	params.c
void	params_create(t_params *params, char *filename);
void	params_destroy(t_params *params);

//	keys_and_continuous_movement.c
int		keypress_func(int keycode, t_params *params);
int		keyrelease_func(int keycode, t_params *params);

//	main.c
void	img_pixel_put(t_image image, int x, int y, int colour);

//	shoot_win_width_nbr_of_rays.c
void	shoot_win_width_nbr_of_rays(t_params *params);

//	find_horizontal_intercept_dist_to_wall.c
void	find_horizontal_intercept_dist_to_wall(t_params *params);

//	find_initial_intercept_dists_and_coords.c
void	find_initial_intercept_dists_and_coords(t_params *params);

//	find_distances_and_intercept_coords.c
void	find_distances_and_intercept_coords(t_params *params);

//	find_real_wall_height.c
void	find_real_wall_height(t_params *params, int iterator);

//	find_texture_x_coord_and_dir.c
void	find_texture_x_coord_and_dir(t_params *params);

//	helper_funcs.c
int		ft_strncmp_last(char *s1, char *s2, size_t n);
int		strncmp_identifier(char *str);

void	*xmalloc(size_t bytes);

#endif
