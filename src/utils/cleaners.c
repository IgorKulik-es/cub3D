/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 14:54:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	close_game(t_game *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->screen.img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	clean_exit(data, "OK", 0);
	return (0);
}

void	clean_exit(t_game *game, char *error, int exit_code)
{
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
	clean_double_array(game->map.map, game->map.height);
	exit(exit_code);
}

void	clean_double_array(char **arr, int n)
{
	int	index;

	index = 0;
	while (index < n)
	{
		if (arr[index] != NULL)
			free(arr[index]);
		index++;
	}
	free(arr);
}
