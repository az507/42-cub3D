/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_real_wall_height.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:50:06 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 18:59:44 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	find_nearest_dist_and_wall_side2(t_params *params, float *distance)
{
	if (params->distance_y == 0 && params->distance_x != 0)
	{
		*distance = params->distance_x;
		params->wall_side = HORIZONTAL;
	}
	else if (params->distance_x == 0 && params->distance_y != 0)
	{
		*distance = params->distance_y;
		params->wall_side = VERTICAL;
	}
	else
	{
		*distance = params->distance_x;
		params->wall_side = HORIZONTAL;
	}
}

static float	find_nearest_dist_and_wall_side(t_params *params)
{
	float	distance;

	distance = 0;
	if (params->distance_x > params->distance_y && params->distance_y != 0)
	{
		distance = params->distance_y;
		params->wall_side = VERTICAL;
	}
	else if (params->distance_y > params->distance_x && params->distance_x != 0)
	{
		distance = params->distance_x;
		params->wall_side = HORIZONTAL;
	}
	else
		find_nearest_dist_and_wall_side2(params, &distance);
	return (distance);
}

/* how much we draw for real wall height shold be equal to the width of 1 map
 * square, so that each map square will actually look like a square if real wall
 * height exceeds WIN_HEIGHT, that means we will only be showing a fraction of
 * the texture image height but it will take up the whole of real wall height
 * unit / distance * dist_to_projection_plane
*/
static void	calculate_real_wall_height(t_params *params, float distance,
		float half_win_width, float half_fov_angle)
{
	float	h1;
	float	h2;
	float	real_wall_height;

	h1 = distance;
	h2 = MAP_GRID * (half_win_width / tanf(half_fov_angle));
	real_wall_height = h2 / h1;
	params->real_wall_height = real_wall_height;
	params->exceed_win_height = false;
	if (real_wall_height > WIN_HEIGHT)
		params->exceed_win_height = true;
}

void	find_real_wall_height(t_params *params, int iterator)
{
	float	distance;
	float	respective_fov_angle;
	float	half_win_width;
	float	half_fov_angle;

	distance = find_nearest_dist_and_wall_side(params);
	half_win_width = WIN_WIDTH / 2;
	half_fov_angle = FOV / 2;
	if (iterator < half_win_width)
		respective_fov_angle = ((half_win_width - iterator)
				/ half_win_width) * half_fov_angle;
	else if (iterator > half_win_width)
		respective_fov_angle = ((iterator - half_win_width)
				/ half_win_width) * half_fov_angle;
	else if (iterator == half_win_width)
		respective_fov_angle = 0.0;
	else
		respective_fov_angle = FOV / 2;
	distance *= cosf(respective_fov_angle);
	calculate_real_wall_height(params, distance,
		half_win_width, half_fov_angle);
}
