/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_distances_and_intercept_coords.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:44:50 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 18:58:58 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*
 * looking for horizontal intersections
 * looking for vertical intersections
 * calculate vertical then horizontal distances between wall intercepts,
 * then compare the 2, then draw that much for a vertical slice
 */
static bool	found_vert_dist_to_wall(t_params *params, int map_index_x,
		int map_index_y)
{
	if (map_index_x < 0 || map_index_y < 0
		|| map_index_x >= params->map_x || map_index_y >= params->map_y)
	{
		params->distance_y = 0;
		return (true);
	}
	if (params->map_arr[map_index_y][map_index_x] == '1'
		|| params->map_arr[map_index_y][map_index_x] == 'F')
	{
		params->distance_y = sqrtf(powf(
					params->corresponding_x_coord - params->player_x, 2)
				+ powf(params->y_intercept - params->player_y, 2));
		return (true);
	}
	return (false);
}

static void	find_next_vert_intercept_coords_and_dist_to_wall(t_params *params,
		int map_index_x, int map_index_y)
{
	while (1)
	{
		params->y_intercept += params->diff_y;
		params->corresponding_x_coord += (params->sign_x * MAP_GRID);
		if (params->y_intercept < 0
			|| params->y_intercept > (MAP_GRID * params->map_y)
			|| params->corresponding_x_coord < 0
			|| params->corresponding_x_coord > (MAP_GRID * params->map_x))
			return (params->distance_y = 0, (void)0);
		map_index_x = params->corresponding_x_coord / MAP_GRID;
		if (params->player_angle > M_PI)
			map_index_x -= 1;
		map_index_y = (params->y_intercept / MAP_GRID);
		if (found_vert_dist_to_wall(params, map_index_x, map_index_y))
			break ;
	}
}

static void	find_initial_vertical_intercept_dist(t_params *params)
{
	if (!(params->y_intercept < 0
			|| params->y_intercept > (MAP_GRID * params->map_y)
			|| params->corresponding_x_coord < 0
			|| params->corresponding_x_coord > (MAP_GRID * params->map_x)))
		params->distance_y = sqrtf(powf(
					params->corresponding_x_coord - params->player_x, 2)
				+ powf(params->y_intercept - params->player_y, 2));
}

static void	find_vertical_intercept_dist_to_wall(t_params *params)
{
	int	vert_map_index_x;
	int	vert_map_index_y;
	int	map_index_x;
	int	map_index_y;

	map_index_x = 0;
	map_index_y = 0;
	vert_map_index_x = params->corresponding_x_coord / MAP_GRID;
	vert_map_index_y = params->y_intercept / MAP_GRID;
	if (params->player_angle > M_PI)
		vert_map_index_x -= 1;
	find_initial_vertical_intercept_dist(params);
	if (vert_map_index_x >= 0 && vert_map_index_y >= 0 && (vert_map_index_x
			< params->map_x) && vert_map_index_y < params->map_y
		&& params->map_arr[vert_map_index_y][vert_map_index_x] == '0'
		&& !(params->y_intercept < 0
			|| params->y_intercept > (MAP_GRID * params->map_y)
			|| params->corresponding_x_coord < 0
			|| params->corresponding_x_coord > (MAP_GRID * params->map_x)))
		find_next_vert_intercept_coords_and_dist_to_wall(
			params, map_index_x, map_index_y);
}

/*
 * dont check for vertical
 * intercepts if angle is a straight vertical line pointing
 * upwards/downwards(inf/ negative
 * infinity gradient) -- skip if statement if player angle is 0, M_PI or 2M_PI
 * only care about finding x/horizontal intercepts if angle is not pointing
 * rightwards or leftwards completely (a flat line, gradient = 0)
 * if (params->player_angle != (M_PI / 2) && params->player_angle
 * != ((3 * M_PI) / 2))
 * continue to calculate horizontal intercepts
 * 
 * only care about finding y/vertical intercepts if angle is not pointing
 * vertically upwards or downwards (infinity or negative infinity gradient)
 * if (params->player_angle != 0 && params->player_angle != M_PI)
 * Need to check within the current map square that our player is in,
 * whether we hit the vertical or horizontal side
 * of the our map square first, comparing initial distance_x and
 * initial distance_y. Whichever is smaller (or non-zero
 * if another one >= 0) will be the side that we hit first within our
 * current square, so we dont need to subtract
 * either map_index_x (for vertical intersections) or map_index_y
 * (for horizontal intersections) by 1. The distance
 * that is bigger will still need to subtract its relevant
 * map_index (x or y) by 1.
 *
 * initial vertical intersect first
 * initial distance_x is distance between player coords and first
 * intersection with horizontal grid line
 * initial distance_y is distance between player coords and first
 * intersection with vertical grid line
 *
 * hori_map_index_x and y are the map coords of the very first intercept
 * with the horizontal side of map grid line(doesnt have to hit a wall yet)
 * while vert_map_index_x and y are for the very first intercept
 * with the vertical side of map grid line
 */
void	find_distances_and_intercept_coords(t_params *params)
{
	find_initial_intercept_dists_and_coords(params);
	find_vertical_intercept_dist_to_wall(params);
	find_horizontal_intercept_dist_to_wall(params);
}
