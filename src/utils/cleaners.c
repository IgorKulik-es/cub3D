/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 23:48:45 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	free_texture(void *mlx, t_img *tex);
static void	free_textures(t_game *game);

int	close_game(t_game *data)
{
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	clean_exit(data, "OK", 0);
	return (0);
}

void	clean_exit(t_game *game, char *error, int exit_code)
{
	if (exit_code != 0)
	{
		if (exit_code == EXIT_FAILURE)
			write(2, "cube3D: ", 7);
		if (exit_code == MAP_ERROR)
			write(2, "Error: ", 6);
		if (error)
			write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	if (game->map.map)
		clean_double_array(game->map.map, game->map.height);
	free_textures(game);
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

static void	free_texture(void *mlx, t_img *tex)
{
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

static void	free_textures(t_game *game)
{
	free_texture(game->mlx, &game->texts.wall_n);
	free_texture(game->mlx, &game->texts.wall_s);
	free_texture(game->mlx, &game->texts.wall_w);
	free_texture(game->mlx, &game->texts.wall_e);
}
