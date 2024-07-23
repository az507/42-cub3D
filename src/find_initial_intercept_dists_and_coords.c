/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_initial_intercept_dists_and_coords.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:24:44 by achak             #+#    #+#             */
/*   Updated: 2024/06/22 11:26:29 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	find_acute_angles_for_intercepts(t_params *params,
		float *acute_angle_x, float *acute_angle_y)
{
	if (params->player_angle < (M_PI_2))
	{
		*acute_angle_x = params->player_angle;
		*acute_angle_y = (M_PI_2) - params->player_angle;
		params->sign_y = -1;
	}
	else if ((M_PI_2) <= params->player_angle && params->player_angle < M_PI)
	{
		*acute_angle_x = M_PI - params->player_angle;
		*acute_angle_y = params->player_angle - (M_PI_2);
	}
	else if (M_PI <= params->player_angle
		&& params->player_angle < (3 * M_PI_2))
	{
		*acute_angle_x = params->player_angle - M_PI;
		*acute_angle_y = (3 * M_PI_2) - params->player_angle;
		params->sign_x = -1;
	}
	else
	{
		*acute_angle_x = (2 * M_PI) - params->player_angle;
		*acute_angle_y = params->player_angle - (3 * M_PI_2);
		params->sign_x = -1;
		params->sign_y = -1;
	}
}

static void	calculate_initial_intercept_dists_and_coords(t_params *params,
		float acute_angle_x, float acute_angle_y)
{
	float	initial_diff_x;
	float	initial_diff_y;

	initial_diff_y = params->sign_y * (params->x_nearest * tanf(acute_angle_y));
	initial_diff_x = params->sign_x * (params->y_nearest * tanf(acute_angle_x));
	params->diff_y = params->sign_y * (MAP_GRID * tanf(acute_angle_y));
	params->diff_x = params->sign_x * (MAP_GRID * tanf(acute_angle_x));
	params->corresponding_x_coord = params->player_x
		+ (params->sign_x * params->x_nearest);
	params->y_intercept = params->player_y + initial_diff_y;
	params->x_intercept = params->player_x + initial_diff_x;
	params->corresponding_y_coord = params->player_y
		+ (params->sign_y * params->y_nearest);
}

void	find_initial_intercept_dists_and_coords(t_params *params)
{
	float	acute_angle_x;
	float	acute_angle_y;

	params->sign_x = 1;
	params->sign_y = 1;
	if (params->player_angle < (M_PI_2)
		|| params->player_angle > (3 * M_PI_2))
		params->y_nearest = params->player_y - ((int)
				(params->player_y / MAP_GRID) * MAP_GRID);
	else
		params->y_nearest = (((int)(params->player_y
						/ MAP_GRID) + 1) * MAP_GRID) - params->player_y;
	if (params->player_angle < M_PI)
		params->x_nearest = (((int)(params->player_x
						/ MAP_GRID) + 1) * MAP_GRID) - params->player_x;
	else
		params->x_nearest = params->player_x - ((int)
				(params->player_x / MAP_GRID) * MAP_GRID);
	find_acute_angles_for_intercepts(params, &acute_angle_x, &acute_angle_y);
	calculate_initial_intercept_dists_and_coords(
		params, acute_angle_x, acute_angle_y);
}
