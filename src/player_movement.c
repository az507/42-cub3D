/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:35:14 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 19:04:35 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	fill_in_needed_floats(t_params *params, float *acute_angle,
		float *dy, float *dx)
{
	if (params->player_angle < (M_PI_2))
	{
		*acute_angle = params->player_angle;
		*dy = -(MOVE_SPEED * cosf(*acute_angle));
		*dx = MOVE_SPEED * sinf(*acute_angle);
	}
	else if (params->player_angle < M_PI)
	{
		*acute_angle = M_PI - params->player_angle;
		*dy = MOVE_SPEED * cosf(*acute_angle);
		*dx = MOVE_SPEED * sinf(*acute_angle);
	}
	else if (params->player_angle < (3 * M_PI_2))
	{
		*acute_angle = params->player_angle - M_PI;
		*dy = MOVE_SPEED * cosf(*acute_angle);
		*dx = -(MOVE_SPEED * sinf(*acute_angle));
	}
	else
	{
		*acute_angle = (2 * M_PI) - params->player_angle;
		*dy = -(MOVE_SPEED * cosf(*acute_angle));
		*dx = -(MOVE_SPEED * sinf(*acute_angle));
	}
}

/*
static bool	is_player_movement_into_wall(t_params *params, float new_x,
		float new_y)
{
	int	new_map_x;
	int	new_map_y;

	new_map_x = new_x / MAP_GRID;
	new_map_y = new_y / MAP_GRID;
	if (new_map_x < 0 || new_map_x >= params->map_x
		|| new_map_y < 0 || new_map_y >= params->map_y)
		return (true);
	if (params->map_arr[new_map_y][new_map_x] != '0')
		return (true);
	return (false);
}
*/

static bool	is_player_movement_into_wall(t_params *params, float new_x,
		float new_y)
{
	int		new_map_x;
	int		new_map_y;
	float	i;
	float	dy;
	float	dx;

	i = 0;
	while (i < 2 * M_PI)
	{
		dx = cosf(i) * MOVE_SPEED;
		dy = -sinf(i) * MOVE_SPEED;
		new_map_x = (new_x + dx * 20) / MAP_GRID;
		new_map_y = (new_y + dy * 20) / MAP_GRID;
		if (new_map_x < 0 || new_map_y < 0 || new_map_x >= params->map_x
			|| new_map_y >= params->map_y
			|| params->map_arr[new_map_y][new_map_x] == '1'
			|| params->map_arr[new_map_y][new_map_x] == 'F')
			return (true);
		i += ONE_DEGREE;
	}
	return (false);
}

static float	return_change_in_new_player_coord(t_params *params,
		bool x_or_y_flag, float new_player_coords[], float new_value)
{
	bool	into_wall;

	if (x_or_y_flag == X)
		new_player_coords[0] += new_value;
	else
		new_player_coords[1] += new_value;
	into_wall = is_player_movement_into_wall(params, new_player_coords[0],
			new_player_coords[1]);
	if (!into_wall)
		return (new_value);
	if (x_or_y_flag == X)
		new_player_coords[0] -= new_value;
	else
		new_player_coords[1] -= new_value;
	return (0);
}

static void	move_player_coords_horizontal(t_params *params, float dy,
		float dx, float new_player_coords[])
{
	new_player_coords[0] = params->player_x;
	new_player_coords[1] = params->player_y;
	if (params->key_flags.a_flag)
	{
		params->player_y += return_change_in_new_player_coord(params,
				Y, new_player_coords, -dx);
		params->player_x += return_change_in_new_player_coord(params,
				X, new_player_coords, dy);
	}
	if (params->key_flags.d_flag)
	{
		params->player_y += return_change_in_new_player_coord(params,
				Y, new_player_coords, dx);
		params->player_x += return_change_in_new_player_coord(params,
				X, new_player_coords, -dy);
	}
}

void	move_player_coords_vertical(t_params *params)
{
	float	acute_angle;
	float	dy;
	float	dx;
	float	new_player_coords[2];

	fill_in_needed_floats(params, &acute_angle, &dy, &dx);
	new_player_coords[0] = params->player_x;
	new_player_coords[1] = params->player_y;
	if (params->key_flags.w_flag)
	{
		params->player_y += return_change_in_new_player_coord(params,
				Y, new_player_coords, +dy);
		params->player_x += return_change_in_new_player_coord(params,
				X, new_player_coords, +dx);
	}
	if (params->key_flags.s_flag)
	{
		params->player_y += return_change_in_new_player_coord(params,
				Y, new_player_coords, -dy);
		params->player_x += return_change_in_new_player_coord(params,
				X, new_player_coords, -dx);
	}
	move_player_coords_horizontal(params, dy, dx, new_player_coords);
}
