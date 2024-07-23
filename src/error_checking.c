/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:06:51 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 20:02:12 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

bool	if_empty_line_skip(t_params *params, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (false);
	free(str);
	if (params->xpm_files[NORTH] && params->xpm_files[SOUTH]
		&& params->xpm_files[EAST] && params->xpm_files[WEST]
		&& params->floor_colour != -1 && params->ceiling_colour != -1
		&& params->begin_list)
		params->done_parsing_map = true;
	return (true);
}

static bool	is_map_component_last_in_config_file(t_params *params)
{
	if (!params->xpm_files[NORTH] || !params->xpm_files[SOUTH]
		|| !params->xpm_files[EAST] || !params->xpm_files[WEST]
		|| params->floor_colour == -1 || params->ceiling_colour == -1)
		return (false);
	return (true);
}

/*
 * If we detect a map component but other identifiers have not been
 * initialized yet - ie they could be further down in the map and
 * thus the map is not the last component in the .cub config file
 * we can only do ft_list_push_back for our map once all other
 * identifiers have been settled already - map content is to be last
 * identifiers also can't be repeated more than once
 */
void	check_errors_in_str(t_params *params, char *str, int fd)
{
	int	identifier;

	identifier = strncmp_identifier(str);
	if ((identifier == NORTH && params->xpm_files[NORTH])
		|| (identifier == SOUTH && params->xpm_files[SOUTH])
		|| (identifier == EAST && params->xpm_files[EAST])
		|| (identifier == WEST && params->xpm_files[WEST]))
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Repeated direction identifier\n"));
	else if (identifier == INVALID)
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Invalid identifier\n"));
	else if (identifier == MAP_COMPONENT
		&& !is_map_component_last_in_config_file(params))
		return (free(str), get_next_line(CLEANUP), close(fd),
			ft_error(params, "Map component not last in config file\n"));
}

void	search_for_invalid_chars_in_colour(t_params *params, char *str,
		char *new_str, int fd)
{
	int	i;

	i = 0;
	if (new_str[i] == 'F' || new_str[i] == 'C')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (new_str[i] && (ft_isdigit(new_str[i]) || new_str[i] == ','))
		i++;
	if (new_str[i])
		return (free(str), free(new_str), get_next_line(CLEANUP),
			close(fd), ft_error(params, "Invalid colour in config\n"));
}
