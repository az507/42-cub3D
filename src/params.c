/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:17 by achak             #+#    #+#             */
/*   Updated: 2024/07/09 15:08:57 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*	parse_file.c	*/
void	parse_file(t_params *params, char *filename);

static void	params_mlx_destroy(t_params *params)
{
	int	i;

	i = -1;
	if (params->image.img_ptr)
		mlx_destroy_image(params->mlx_ptr, params->image.img_ptr);
	while (++i < TEXTURES_NBR)
		if (params->textures[i].img_ptr)
			mlx_destroy_image(params->mlx_ptr, params->textures[i].img_ptr);
	if (params->win_ptr)
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	if (params->mlx_ptr)
	{
		mlx_destroy_display(params->mlx_ptr);
		free(params->mlx_ptr);
	}
}

void	params_destroy(t_params *params)
{
	int	i;

	i = -1;
	if (params)
	{
		params_mlx_destroy(params);
		while (++i < TEXTURES_NBR)
			if (params->xpm_files[i])
				free(params->xpm_files[i]);
		if (params->map_arr)
			free(params->map_arr);
		ft_list_clear(params->begin_list, &free);
	}
	ft_memset(params, 0, sizeof(*params));
}

static void	img_get_data_addr(t_params *params)
{
	params->image.data_addr = mlx_get_data_addr(params->image.img_ptr,
			&params->image.bits_per_pixel, &params->image.size_line,
			&params->image.endian);
	params->textures[0].data_addr = mlx_get_data_addr(
			params->textures[0].img_ptr,
			&params->textures[0].bits_per_pixel,
			&params->textures[0].size_line,
			&params->image.endian);
	params->textures[1].data_addr = mlx_get_data_addr(
			params->textures[1].img_ptr,
			&params->textures[1].bits_per_pixel,
			&params->textures[1].size_line,
			&params->image.endian);
	params->textures[2].data_addr = mlx_get_data_addr(
			params->textures[2].img_ptr,
			&params->textures[2].bits_per_pixel,
			&params->textures[2].size_line,
			&params->image.endian);
	params->textures[3].data_addr = mlx_get_data_addr(
			params->textures[3].img_ptr,
			&params->textures[3].bits_per_pixel,
			&params->textures[3].size_line,
			&params->image.endian);
}

static void	get_texture_img_ptr(t_params *params)
{
	params->textures[NORTH].img_ptr = mlx_xpm_file_to_image(params->mlx_ptr,
			params->xpm_files[NORTH], &params->textures[NORTH].width,
			&params->textures[NORTH].height);
	params->textures[SOUTH].img_ptr = mlx_xpm_file_to_image(params->mlx_ptr,
			params->xpm_files[SOUTH], &params->textures[SOUTH].width,
			&params->textures[SOUTH].height);
	params->textures[EAST].img_ptr = mlx_xpm_file_to_image(params->mlx_ptr,
			params->xpm_files[EAST], &params->textures[EAST].width,
			&params->textures[EAST].height);
	params->textures[WEST].img_ptr = mlx_xpm_file_to_image(params->mlx_ptr,
			params->xpm_files[WEST], &params->textures[WEST].width,
			&params->textures[WEST].height);
}

void	params_create(t_params *params, char *filename)
{
	ft_memset(params, 0, sizeof(*params));
	params->floor_colour = -1;
	params->ceiling_colour = -1;
	parse_file(params, filename);
	params->mlx_ptr = mlx_init();
	if (!params->mlx_ptr)
		ft_perror(params, "mlx_init");
	params->win_ptr = mlx_new_window(params->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "Abc");
	if (!params->win_ptr)
		ft_perror(params, "mlx_new_window");
	params->image.img_ptr = mlx_new_image(
			params->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!params->image.img_ptr)
		ft_perror(params, "mlx_new_image");
	get_texture_img_ptr(params);
	if (!params->textures[0].img_ptr || !params->textures[1].img_ptr
		|| !params->textures[2].img_ptr || !params->textures[3].img_ptr)
		ft_perror(params, "mlx_xpm_file_to_image");
	img_get_data_addr(params);
}
