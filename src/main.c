/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:39:23 by achak             #+#    #+#             */
/*   Updated: 2024/07/04 16:15:52 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*	keys_and_continuous_movement.c		*/
void	continuous_player_movement(t_params *params);

void	img_pixel_put(t_image image, int x, int y, int colour)
{
	char	*addr;

	if (!image.img_ptr)
		return ;
	addr = image.data_addr + ((image.bits_per_pixel / 8) * x)
		+ (image.size_line * y);
	*(unsigned int *)addr = colour;
}

int	render_func(t_params *params)
{
	continuous_player_movement(params);
	shoot_win_width_nbr_of_rays(params);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr,
		params->image.img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc == 1)
	{
		ft_dprintf(STDERR_FILENO, "Usage: %s <*.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	params_create(&params, argv[1]);
	mlx_put_image_to_window(params.mlx_ptr, params.win_ptr,
		params.image.img_ptr, 0, 0);
	mlx_hook(params.win_ptr, KeyPress, KeyPressMask, &keypress_func, &params);
	mlx_hook(params.win_ptr, KeyRelease, KeyReleaseMask, &keyrelease_func,
		&params);
	mlx_hook(params.win_ptr, DestroyNotify, StructureNotifyMask,
		&func_exit, &params);
	mlx_loop_hook(params.mlx_ptr, &render_func, &params);
	mlx_loop(params.mlx_ptr);
}
