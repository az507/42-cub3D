/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_texture_x_coord_and_dir.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:19:45 by achak             #+#    #+#             */
/*   Updated: 2024/07/09 16:18:21 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	find_texture_x_coord_and_dir4(t_params *params,
		float texture_to_wall_ratio_x)
{
	if (params->wall_side == VERTICAL)
	{
		texture_to_wall_ratio_x = MAP_GRID - ((((int)(params
							->y_intercept / MAP_GRID) + 1) * MAP_GRID)
				- params->y_intercept);
		params->texture_dir = WEST;
		texture_to_wall_ratio_x = MAP_GRID - texture_to_wall_ratio_x;
	}
	else if (params->wall_side == HORIZONTAL)
	{
		texture_to_wall_ratio_x = MAP_GRID - ((((int)(params
							->x_intercept / MAP_GRID) + 1) * MAP_GRID)
				- params->x_intercept);
		params->texture_dir = NORTH;
	}
	texture_to_wall_ratio_x /= MAP_GRID;
	params->texture_x = texture_to_wall_ratio_x
		* params->textures[params->texture_dir].width;
}

static void	find_texture_x_coord_and_dir3(t_params *params,
		float texture_to_wall_ratio_x)
{
	if (params->player_angle < (3 * M_PI_2))
	{
		if (params->wall_side == VERTICAL)
		{
			texture_to_wall_ratio_x = params->y_intercept - ((int)(
						params->y_intercept / MAP_GRID) * MAP_GRID);
			texture_to_wall_ratio_x = MAP_GRID - texture_to_wall_ratio_x;
			params->texture_dir = WEST;
		}
		else if (params->wall_side == HORIZONTAL)
		{
			texture_to_wall_ratio_x = MAP_GRID - ((((int)(params
								->x_intercept / MAP_GRID) + 1) * MAP_GRID)
					- params->x_intercept);
			texture_to_wall_ratio_x = MAP_GRID - texture_to_wall_ratio_x;
			params->texture_dir = SOUTH;
		}
		texture_to_wall_ratio_x /= MAP_GRID;
		params->texture_x = texture_to_wall_ratio_x
			* params->textures[params->texture_dir].width;
	}
	else
		find_texture_x_coord_and_dir4(params, texture_to_wall_ratio_x);
}

static void	find_texture_x_coord_and_dir2(t_params *params,
		float texture_to_wall_ratio_x)
{
	if (params->player_angle < M_PI)
	{
		if (params->wall_side == VERTICAL)
		{
			texture_to_wall_ratio_x = params->y_intercept
				- ((int)(params->y_intercept / MAP_GRID) * MAP_GRID);
			params->texture_dir = EAST;
		}
		else if (params->wall_side == HORIZONTAL)
		{
			texture_to_wall_ratio_x = params->x_intercept - ((int)(
						params->x_intercept / MAP_GRID) * MAP_GRID);
			params->texture_dir = SOUTH;
			texture_to_wall_ratio_x = MAP_GRID - texture_to_wall_ratio_x;
		}
		texture_to_wall_ratio_x /= MAP_GRID;
		params->texture_x = texture_to_wall_ratio_x
			* params->textures[params->texture_dir].width;
	}
	else
		find_texture_x_coord_and_dir3(params, texture_to_wall_ratio_x);
}

void	find_texture_x_coord_and_dir(t_params *params)
{
	float	texture_to_wall_ratio_x;

	texture_to_wall_ratio_x = 0;
	if (params->player_angle < (M_PI_2))
	{
		if (params->wall_side == VERTICAL)
		{
			texture_to_wall_ratio_x = MAP_GRID - ((((int)(params
								->y_intercept / MAP_GRID) + 1) * MAP_GRID)
					- params->y_intercept);
			params->texture_dir = EAST;
		}
		else if (params->wall_side == HORIZONTAL)
		{
			texture_to_wall_ratio_x = params->x_intercept
				- ((int)(params->x_intercept / MAP_GRID) * MAP_GRID);
			params->texture_dir = NORTH;
		}
		texture_to_wall_ratio_x /= MAP_GRID;
		params->texture_x = texture_to_wall_ratio_x
			* params->textures[params->texture_dir].width;
	}
	else
		find_texture_x_coord_and_dir2(params, texture_to_wall_ratio_x);
}
