/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 12:30:45 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/cub3D.h"

int	close_game(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	clean_exit(&(data->map), "OK", 0);
	return (0);
}

void	clean_exit(t_map_data *map, char *error, int exit_code)
{
	(void)map;
	if (exit_code != 0)
	{
		if (exit_code == EXIT_FAILURE)
			write(2, "so_long: ", 9);
		if (exit_code == MAP_ERROR)
			write(2, "Error: ", 6);
		if (error)
			write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	exit(exit_code);
}
