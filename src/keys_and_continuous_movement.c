/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_continuous_movement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:26:09 by achak             #+#    #+#             */
/*   Updated: 2024/07/04 16:13:35 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*	player_movement.c	*/
void	move_player_coords_vertical(t_params *params);

/*
static void	offset_player_movement(t_params *params)
{
	if (params->player_x > (params->map_x * MAP_GRID))
		params->player_x -= params->map_x * MAP_GRID;
	else if (params->player_x < 0)
		params->player_x += params->map_x * MAP_GRID;
	if (params->player_y > params->map_y * MAP_GRID)
		params->player_y -= params->map_y * MAP_GRID;
	else if (params->player_y < 0)
		params->player_y += params->map_y * MAP_GRID;
}
*/

void	continuous_player_movement(t_params *params)
{
	if (params->key_flags.left_flag)
	{
		params->player_angle -= TURN_SPEED;
		if (params->player_angle < 0 && params->player_angle > -0.0025)
			params->player_angle = 0;
		else if (params->player_angle <= 0)
			params->player_angle = (2 * M_PI) - TURN_SPEED;
	}
	if (params->key_flags.right_flag)
	{
		params->player_angle += TURN_SPEED;
		if (params->player_angle >= (2 * M_PI) - 0.0025)
			params->player_angle = 0;
	}
	if (params->key_flags.w_flag || params->key_flags.s_flag
		|| params->key_flags.a_flag || params->key_flags.d_flag)
		move_player_coords_vertical(params);
}

int	keypress_func(int keycode, t_params *params)
{
	if (keycode == XK_Escape)
		ft_exit(params, EXIT_SUCCESS);
	else if (keycode == XK_w || keycode == XK_W)
		params->key_flags.w_flag = true;
	else if (keycode == XK_s || keycode == XK_S)
		params->key_flags.s_flag = true;
	else if (keycode == XK_a || keycode == XK_A)
		params->key_flags.a_flag = true;
	else if (keycode == XK_d || keycode == XK_D)
		params->key_flags.d_flag = true;
	else if (keycode == XK_Left)
		params->key_flags.left_flag = true;
	else if (keycode == XK_Right)
		params->key_flags.right_flag = true;
	return (0);
}

int	keyrelease_func(int keycode, t_params *params)
{
	if (keycode == XK_w || keycode == XK_W)
		params->key_flags.w_flag = false;
	else if (keycode == XK_s || keycode == XK_S)
		params->key_flags.s_flag = false;
	else if (keycode == XK_a || keycode == XK_A)
		params->key_flags.a_flag = false;
	else if (keycode == XK_d || keycode == XK_D)
		params->key_flags.d_flag = false;
	else if (keycode == XK_Left)
		params->key_flags.left_flag = false;
	else if (keycode == XK_Right)
		params->key_flags.right_flag = false;
	return (0);
}
