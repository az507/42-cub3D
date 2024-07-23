/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:19:10 by achak             #+#    #+#             */
/*   Updated: 2024/07/04 12:53:05 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	is_flood_fill_condition_met(t_params *params, int current_x,
		int current_y, char to_fill[])
{
	if (params->map_arr[current_y][current_x] != to_fill[0]
		&& params->map_arr[current_y][current_x] != to_fill[1])
	{
		if (params->map_arr[current_y][current_x] == '0'
			|| params->map_arr[current_y][current_x] == 'N'
			|| params->map_arr[current_y][current_x] == 'S'
			|| params->map_arr[current_y][current_x] == 'E'
			|| params->map_arr[current_y][current_x] == 'W')
			return (free(params->map_arr[0]),
				free(params->map_arr[params->map_y + 1]),
				free(params->map_arr[params->map_y + 2]),
				ft_error(params, "Map not surrounded by walls\n"),
				ERROR);
		return (true);
	}
	return (false);
}

void	flood_fill(t_params *params, int current_x, int current_y,
		char to_fill[])
{
	static int	counter = -1;

	if (++counter > RECURSION_LIMIT)
		return (free(params->map_arr[0]),
			free(params->map_arr[params->map_y + 1]),
			free(params->map_arr[params->map_y + 2]),
			ft_error(params, "Map too big\n"));
	if (current_x < 0 || current_x >= params->map_x + 1
		|| current_y < 0 || current_y >= params->map_y + 2)
		return ;
	if (is_flood_fill_condition_met(params, current_x, current_y, to_fill))
		return ;
	params->map_arr[current_y][current_x] = 'F';
	flood_fill(params, current_x - 1, current_y, to_fill);
	flood_fill(params, current_x + 1, current_y, to_fill);
	flood_fill(params, current_x, current_y - 1, to_fill);
	flood_fill(params, current_x, current_y + 1, to_fill);
}

void	replace_map_arr(t_params *params)
{
	int		i;
	char	**new_map_arr;

	i = -1;
	new_map_arr = malloc(sizeof(char *) * (params->map_y + 1));
	if (!new_map_arr)
		ft_perror(params, "malloc");
	while (++i < params->map_y)
		new_map_arr[i] = params->map_arr[i + 1];
	new_map_arr[i] = NULL;
	free(params->map_arr[0]);
	free(params->map_arr[params->map_y + 1]);
	free(params->map_arr[params->map_y + 2]);
	free(params->map_arr);
	params->map_arr = new_map_arr;
}

/*
 * Player coords must be calculated after flood fill
 */
static void	find_player_start_and_angle(t_params *params,
		bool *player_flag, int i, int j)
{
	if (*player_flag)
		ft_error(params, "Player start position declared more than once\n");
	params->player_x = ((j + 1) * MAP_GRID) - (MAP_GRID / 2);
	params->player_y = ((i + 1) * MAP_GRID) - (MAP_GRID / 2);
	if (params->map_arr[i][j] == 'N')
		params->player_angle = 0;
	else if (params->map_arr[i][j] == 'S')
		params->player_angle = M_PI;
	else if (params->map_arr[i][j] == 'E')
		params->player_angle = M_PI_2;
	else
		params->player_angle = 3 * M_PI_2;
	params->map_arr[i][j] = '0';
	*player_flag = true;
}

void	parse_map_arr_for_player(t_params *params)
{
	int		i;
	int		j;
	bool	player_flag;

	i = -1;
	player_flag = false;
	while (params->map_arr[++i])
	{
		j = -1;
		while (params->map_arr[i][++j])
		{
			if (params->map_arr[i][j] == 'N' || params->map_arr[i][j] == 'S'
				|| params->map_arr[i][j] == 'E'
				|| params->map_arr[i][j] == 'W')
				find_player_start_and_angle(params, &player_flag, i, j);
		}
	}
	if (!player_flag)
		ft_error(params, "Start position not declared in map\n");
}
