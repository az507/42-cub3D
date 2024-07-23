/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_horizontal_intercept_dist_to_wall.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:28:10 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 18:59:12 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	found_hori_dist_to_wall(t_params *params, int map_index_x,
		int map_index_y)
{
	if (map_index_x < 0 || map_index_y < 0
		|| map_index_x >= params->map_x || map_index_y >= params->map_y)
	{
		params->distance_x = 0;
		return (true);
	}
	if (params->map_arr[map_index_y][map_index_x] == '1'
		|| params->map_arr[map_index_y][map_index_x] == 'F')
	{
		params->distance_x = sqrtf(powf(
					params->x_intercept - params->player_x, 2)
				+ powf(params->corresponding_y_coord - params->player_y, 2));
		return (true);
	}
	return (false);
}

static void	find_next_hori_intercept_coords_and_dist_to_wall(t_params *params,
		int map_index_x, int map_index_y)
{
	while (1)
	{
		params->x_intercept += params->diff_x;
		params->corresponding_y_coord += (params->sign_y * MAP_GRID);
		if (params->x_intercept < 0
			|| params->x_intercept > (MAP_GRID * params->map_x)
			|| params->corresponding_y_coord < 0
			|| params->corresponding_y_coord > (MAP_GRID * params->map_y))
		{
			params->distance_x = 0;
			break ;
		}
		map_index_x = params->x_intercept / MAP_GRID;
		map_index_y = params->corresponding_y_coord / MAP_GRID;
		if (params->player_angle < (M_PI_2)
			|| params->player_angle > ((3 * M_PI_2)))
			map_index_y -= 1;
		if (found_hori_dist_to_wall(params, map_index_x, map_index_y))
			break ;
	}
}

static void	find_initial_horizontal_intercept_dist(t_params *params)
{
	if (!(params->x_intercept < 0
			|| params->x_intercept > (MAP_GRID * params->map_x)
			|| params->corresponding_y_coord < 0
			|| params->corresponding_y_coord > (MAP_GRID * params->map_y)))
		params->distance_x = sqrtf(powf(
					params->x_intercept - params->player_x, 2)
				+ powf(params->corresponding_y_coord - params->player_y, 2));
}

void	find_horizontal_intercept_dist_to_wall(t_params *params)
{
	int	hori_map_index_x;
	int	hori_map_index_y;
	int	map_index_x;
	int	map_index_y;

	map_index_x = 0;
	map_index_y = 0;
	hori_map_index_x = params->x_intercept / MAP_GRID;
	hori_map_index_y = params->corresponding_y_coord / MAP_GRID;
	if (params->player_angle < (M_PI_2)
		|| params->player_angle > ((3 * M_PI_2)))
		hori_map_index_y -= 1;
	find_initial_horizontal_intercept_dist(params);
	if (hori_map_index_x >= 0 && hori_map_index_y >= 0 && hori_map_index_x
		< params->map_x && hori_map_index_y < params->map_y
		&& params->map_arr[hori_map_index_y][hori_map_index_x] == '0'
		&& (!(params->x_intercept < 0
			|| params->x_intercept > (MAP_GRID * params->map_x)
			|| params->corresponding_y_coord < 0
			|| params->corresponding_y_coord > (MAP_GRID * params->map_y))))
		find_next_hori_intercept_coords_and_dist_to_wall(
			params, map_index_x, map_index_y);
}
