/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:12:19 by achak             #+#    #+#             */
/*   Updated: 2024/06/14 12:22:37 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	ft_exit(t_params *params, int exit_code)
{
	params_destroy(params);
	exit(exit_code);
}

void	ft_error(t_params *params, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	ft_dprintf(STDERR_FILENO, msg);
	ft_exit(params, EXIT_FAILURE);
}

void	ft_perror(t_params *params, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	perror(msg);
	ft_exit(params, EXIT_FAILURE);
}

int	func_exit(t_params *params)
{
	ft_exit(params, EXIT_SUCCESS);
	return (0);
}
