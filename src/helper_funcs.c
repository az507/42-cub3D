/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:26:33 by achak             #+#    #+#             */
/*   Updated: 2024/07/05 20:16:46 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_strncmp_last(char *s1, char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < n || len2 < n)
		return (1);
	while (n >= 0 && s1[len1 - n] && s2[len2 - n])
	{
		if (s1[len1 - n] == s2[len2 - n])
			n--;
		else
			break ;
	}
	if (!n)
		return (0);
	return (1);
}

static bool	is_str_a_map_component(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '0' && str[i] != '1' && str[i] != '\n'
			&& str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W'
			&& str[i] != ' ')
			return (false);
	return (true);
}

/*
 * my strncmp_identifier should be able to take a string (from gnl) and be able
 * to tell what kind of string/identifier it is, e.g. whether its path to a
 * texture, colour for ceiling/floor, part of a map component, or just rubbish
 */
int	strncmp_identifier(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (!ft_strncmp(str, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(str, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(str, "EA ", 3))
		return (EAST);
	else if (!ft_strncmp(str, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(str, "F ", 2))
		return (FLOOR);
	else if (!ft_strncmp(str, "C ", 2))
		return (CEILING);
	else if (is_str_a_map_component(str) == true)
		return (MAP_COMPONENT);
	return (INVALID);
}

/*
 * This realloc implementation is simply a malloc, memcpy then free operation.
 * The pointer to the new memory block will definitely be different from the
 * void *ptr, so pointers that were previously pointing to void *ptr will now be
 * pointing to garbage after realloc finishes, so need to repoint previous
 * pointers back to the return value of realloc also, if realloc fails the
 * original void *ptr will still be a valid memory block, so check the return
 * value before doing anything with it
 */

void	*modified_realloc(void *ptr, size_t size, int filler_byte)
{
	unsigned char	*mem_block;
	unsigned char	*ptr1;
	size_t			i;

	if (size)
	{
		mem_block = malloc(size);
		if (!mem_block)
			return (perror("malloc"), NULL);
		if (!ptr)
			return (ft_memset(mem_block, filler_byte, size));
		i = 1;
		ptr1 = (unsigned char *)ptr;
		mem_block[0] = filler_byte;
		while (i < size && ptr1[i - 1])
		{
			mem_block[i] = ptr1[i - 1];
			i++;
		}
		ft_memset(mem_block + i, filler_byte, size - i);
		return (free(ptr), (void *)mem_block);
	}
	else if (!size && ptr)
		free(ptr);
	return (NULL);
}

int	modified_atoi(const char *nptr, bool *error_flag)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= '9' && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			sign = -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		*error_flag = false;
		result = result * 10 + *nptr++ - '0';
	}
	return ((int)result * sign);
}
