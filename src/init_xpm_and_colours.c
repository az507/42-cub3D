/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm_and_colours.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:01 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 19:52:09 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*	helper_funcs.c	*/
int		modified_atoi(const char *nptr, bool *error_flag);

/*	error_checking.c	*/
void	search_for_invalid_chars_in_colour(t_params *params, char *str,
			char *new_str, int fd);

static bool	find_commas_and_nbr_start(char *str, char **nbr_start)
{
	int		count;
	char	*result;

	count = 0;
	while (1)
	{
		result = ft_strchr(str, ',');
		if (!result || count == 2)
			break ;
		nbr_start[count++] = result + 1;
		str = result + 1;
	}
	if (result || count < 2)
		return (false);
	return (true);
}

static int	get_rgb_colours(t_params *params, char *str, int fd)
{
	char	*nbr_start[2];
	char	*new_str;
	bool	error_flag[3];
	int		rgb[3];

	new_str = ft_strtrim(str, " \n");
	if (!new_str)
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_perror(params, "malloc"), ERROR);
	if (!find_commas_and_nbr_start(new_str, nbr_start))
		return (free(str), free(new_str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Wrong nbr of commas\n"), ERROR);
	search_for_invalid_chars_in_colour(params, str, new_str, fd);
	ft_memset(error_flag, true, sizeof(error_flag));
	rgb[0] = modified_atoi(new_str + 1, &error_flag[0]);
	rgb[1] = modified_atoi(nbr_start[0], &error_flag[1]);
	rgb[2] = modified_atoi(nbr_start[1], &error_flag[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255
		|| error_flag[0] || error_flag[1] || error_flag[2])
		return (free(str), free(new_str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Invalid number for rgb\n"), ERROR);
	return (free(new_str), rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	init_floor_and_ceil_colours(t_params *params, char *str, int identifier,
		int fd)
{
	int	i;
	int	len;
	int	rgb_colour;

	i = 1;
	len = 0;
	if (identifier <= MAP_COMPONENT)
		return (identifier);
	if ((identifier == FLOOR && params->floor_colour != -1)
		|| (identifier == CEILING && params->ceiling_colour != -1))
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Repeated colour identifier\n"), ERROR);
	rgb_colour = get_rgb_colours(params, str, fd);
	if (identifier == FLOOR)
		params->floor_colour = rgb_colour;
	else
		params->ceiling_colour = rgb_colour;
	return (free(str), identifier);
}

static char	*get_xpm_file(char *str, int direction)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if ((!ft_strncmp(str + i, "NO", 2) && direction == NORTH)
		|| (!ft_strncmp(str + i, "SO", 2) && direction == SOUTH)
		|| (!ft_strncmp(str + i, "EA", 2) && direction == EAST)
		|| (!ft_strncmp(str + i, "WE", 2) && direction == WEST))
		i += 2;
	str[ft_strlen(str) - 1] = '\0';
	return (ft_strtrim(str + i, " "));
}

int	init_xpm_files(t_params *params, char *str, int direction, int fd)
{
	char	*xpm_file;

	if (direction >= MAP_COMPONENT)
		return (direction);
	else if (params->xpm_files[direction])
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Repeated direction\n"), ERROR);
	xpm_file = get_xpm_file(str, direction);
	if (!xpm_file)
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_perror(params, "malloc"), ERROR);
	if (ft_strncmp_last(xpm_file, ".xpm", 4) == ERROR)
		return (free(str), free(xpm_file), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Invalid file extension (xpm)\n"), ERROR);
	params->xpm_files[direction] = xpm_file;
	return (free(str), direction);
}
