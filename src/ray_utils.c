/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:56 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 19:02:34 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	reset_calculated_values_for_new_ray(t_params *params)
{
	params->x_nearest = 0;
	params->y_nearest = 0;
	params->diff_x = 0;
	params->diff_y = 0;
	params->x_intercept = 0;
	params->corresponding_y_coord = 0;
	params->corresponding_x_coord = 0;
	params->y_intercept = 0;
	params->distance_x = 0;
	params->distance_y = 0;
	params->real_wall_height = 0;
	params->exceed_win_height = false;
	params->texture_x = 0;
	params->texture_dir = 0;
	params->wall_side = 0;
	params->sign_x = 1;
	params->sign_y = 1;
}
