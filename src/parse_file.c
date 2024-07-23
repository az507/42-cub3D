/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:35 by achak             #+#    #+#             */
/*   Updated: 2024/07/04 12:40:11 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*	parse_map_arr.c 	*/
void	flood_fill(t_params *params, int current_x, int current_y,
			char to_fill[]);
void	replace_map_arr(t_params *params);
void	parse_map_arr_for_player(t_params *params);

/*	error_checking.c	*/
bool	if_empty_line_skip(t_params *params, char *str);
void	check_errors_in_str(t_params *params, char *str, int fd);

/*	helper_funcs.c		*/
void	*modified_realloc(void *ptr, size_t size, int filler_byte);

/*	replace all newline chars with null bytes	*/
static void	find_max_len_for_map_str(t_params *params)
{
	int	i;
	int	max_len;

	i = 0;
	while (++i < params->map_y + 1)
	{
		max_len = ft_strlen(params->map_arr[i]);
		params->map_arr[i][max_len - 1] = '\0';
		if (params->map_x < max_len)
			params->map_x = max_len;
	}
}

static void	resize_map_arr_with_fillers(t_params *params)
{
	int			i;
	int			str_len;
	t_cub_list	*temp_ptr;

	i = -1;
	temp_ptr = params->begin_list;
	while (++i < params->map_y + 2)
	{
		str_len = ft_strlen(params->map_arr[i]);
		if (str_len < params->map_x + 1)
		{
			params->map_arr[i] = modified_realloc(params->map_arr[i],
					params->map_x + 2, 'A');
			if (!params->map_arr[i])
				ft_error(params, "modified realloc error\n");
			params->map_arr[i][params->map_x + 1] = '\0';
		}
		if (i > 0 && i <= params->map_y && temp_ptr)
			temp_ptr->data = (void *)params->map_arr[i];
		if (temp_ptr && i > 0)
			temp_ptr = temp_ptr->next;
	}
}

static void	fill_map_arr_whitespace(t_params *params)
{
	int	i;
	int	j;

	i = -1;
	while (params->map_arr[++i])
	{
		j = -1;
		while (params->map_arr[i][++j])
		{
			if (params->map_arr[i][j] == ' ')
				params->map_arr[i][j] = '0';
			if (params->map_arr[i][j] != '0'
				&& params->map_arr[i][j] != '1'
				&& params->map_arr[i][j] != '\n'
				&& params->map_arr[i][j] != 'F'
				&& params->map_arr[i][j] != 'N'
				&& params->map_arr[i][j] != 'S'
				&& params->map_arr[i][j] != 'E'
				&& params->map_arr[i][j] != 'W'
				&& params->map_arr[i][j] != ' ')
				ft_error(params, "Unrecognized character in map\n");
		}
	}
}

static void	init_map_arr(t_params *params)
{
	int			i;
	t_cub_list	*temp_ptr;

	i = 0;
	params->map_y = ft_list_size(params->begin_list);
	params->map_arr = malloc((params->map_y + 3) * sizeof(char *));
	temp_ptr = params->begin_list;
	if (!params->map_arr)
		ft_perror(params, "malloc");
	while (++i < params->map_y + 1 && temp_ptr)
	{
		params->map_arr[i] = (char *)temp_ptr->data;
		temp_ptr = temp_ptr->next;
	}
	params->map_arr[0] = NULL;
	params->map_arr[params->map_y + 1] = NULL;
	params->map_arr[params->map_y + 2] = NULL;
	find_max_len_for_map_str(params);
	resize_map_arr_with_fillers(params);
	flood_fill(params, 0, 0, "A ");
	fill_map_arr_whitespace(params);
	replace_map_arr(params);
	parse_map_arr_for_player(params);
}

void	parse_file(t_params *params, char *filename)
{
	int		fd;
	char	*str;

	if (ft_strncmp_last(filename, ".cub", 4) == ERROR)
		ft_error(params, "Invalid file extension (cub)\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_perror(params, filename);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		else if (if_empty_line_skip(params, str) == true)
			continue ;
		check_errors_in_str(params, str, fd);
		if (init_xpm_files(params, str, strncmp_identifier(str), fd)
			>= MAP_COMPONENT && init_floor_and_ceil_colours(params,
				str, strncmp_identifier(str), fd) == MAP_COMPONENT)
			ft_list_push_back(params, fd, &params->begin_list, (void *)str);
	}
	close(fd);
	init_map_arr(params);
}
