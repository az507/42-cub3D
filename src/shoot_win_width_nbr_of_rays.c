/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_win_width_nbr_of_rays.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:54 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 19:05:56 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*
 * This if else statements are to determine the direction that
 * the walls, which our rays have intersected with, are facing in,
 * as well as which part (fraction) of the wall the ray has hit
 * - so that we can determine the x_coordinate of our
 * texture image that we will be using the colour of
 * Later on we will then be determining the y_coordinate of texture
 * image as well (in a loop, x_coord only once per ray) final_x_coord
 * and final_y_coord is either
 * x_intercept or y_intercept coord from above
*/

/*
 * texture_to_wall_ratio_x is what fraction of the MAP_GRID our ray is
 * at (always below 1), then texture_x is the
 * x_coord of the texture image that we will be taking the colour of
 * float	texture_to_wall_ratio_y = 
 * real_wall_height / params->textures[0].height;
 * texture_to_wall_ratio_y is how much we need to increment the y_coord
 * of the texture image for each iteration, and will
 * be iterating real_wall_height number of times
 */

/*	ray_utils.c	*/
void	reset_calculated_values_for_new_ray(t_params *params);

static void	draw_floor_and_ceiling_height(t_params *params,
		float half_win_height, int iterator)
{
	int		p;
	float	ceiling_height;
	float	floor_height;
	float	a;

	p = -1;
	a = params->real_wall_height / 2;
	ceiling_height = half_win_height - a;
	floor_height = half_win_height + a;
	while (++p < ceiling_height)
		img_pixel_put(params->image, iterator, p, params->ceiling_colour);
	while (floor_height < WIN_HEIGHT)
		img_pixel_put(params->image, iterator, floor_height++,
			params->floor_colour);
}
/*
 * texture_to_wall_ratio_x is what fraction of the MAP_GRID our ray is
 * at (always below 1), then texture_x is the
 * x_coord of the texture image that we will be taking the colour of
 * float        texture_to_wall_ratio_y = 
 * real_wall_height / params->textures[0].height;
 * texture_to_wall_ratio_y is how much we need to increment the y_coord
 * of the texture image for each iteration, and will
 * be iterating real_wall_height number of times
 */

static unsigned int	get_shaded_colour_value(t_params *params,
		unsigned int colour)
{
	float			ratio;
	unsigned int	rgb[3];

	ratio = params->real_wall_height / (float)SHADE_DIST_LIMIT;
	if (ratio > 1.0 || __fpclassify(ratio) == FP_ZERO)
		return (colour);
	rgb[0] = ((colour >> 16) & 0x000000FF) * ratio;
	rgb[1] = ((colour >> 8) & 0x000000FF) * ratio;
	rgb[2] = (colour & 0x000000FF) * ratio;
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

static void	draw_textured_height(t_params *params,
		float texture_to_wall_ratio_y, float half_win_height, int iterator)
{
	float			a;
	float			texture_y;
	int				b;
	char			*addr;

	a = -params->real_wall_height / 2;
	b = 0;
	while (a <= (params->real_wall_height / 2))
	{
		texture_y = texture_to_wall_ratio_y * b++;
		addr = params->textures[params->texture_dir].data_addr + (int)(((int)
					params->texture_x * (params->textures[params
						->texture_dir].bits_per_pixel / 8))
				+ ((params->textures [params->texture_dir].size_line)
					* (int)(texture_y)));
		if (a + half_win_height > 0 && a + half_win_height < WIN_HEIGHT)
			img_pixel_put(params->image, iterator, a + half_win_height,
				get_shaded_colour_value(params, *(unsigned int *)addr));
		a++;
	}
	if (params->exceed_win_height == false)
		draw_floor_and_ceiling_height(params, half_win_height, iterator);
}

static void	raycaster(t_params *params, int iterator)
{
	float	texture_to_wall_ratio_y;
	float	a;

	reset_calculated_values_for_new_ray(params);
	find_distances_and_intercept_coords(params);
	find_real_wall_height(params, iterator);
	find_texture_x_coord_and_dir(params);
	texture_to_wall_ratio_y
		= params->textures[params->texture_dir].height
		/ params->real_wall_height;
	a = 0;
	if (__fpclassify(params->real_wall_height) != FP_INFINITE)
		draw_textured_height(params, texture_to_wall_ratio_y,
			WIN_HEIGHT / 2, iterator);
	else
		while (a < WIN_HEIGHT)
			img_pixel_put(params->image, iterator, a++, RED_PIXEL);
}

void	shoot_win_width_nbr_of_rays(t_params *params)
{
	int		i;
	float	fov_increment;
	float	new_angle;
	float	placeholder_angle;

	i = -1;
	fov_increment = FOV / WIN_WIDTH;
	while (++i < WIN_WIDTH)
	{
		new_angle = (-FOV / 2) + (i * fov_increment) + params->player_angle;
		placeholder_angle = params->player_angle;
		params->player_angle = new_angle;
		if (params->player_angle < 0)
			params->player_angle = (2 * M_PI) + params->player_angle;
		else if (params->player_angle > (2 * M_PI))
			params->player_angle -= (2 * M_PI);
		raycaster(params, i);
		params->player_angle = placeholder_angle;
	}
}
