/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:31:15 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 11:29:08 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	put_fps_counter(t_game *game, time_t time)
{
	void	*background;
	int		fps;
	char	*str_time;
	char	*str_fps;

	fps = T_MICROSEC / (time - game->screen.last_frame_time);
	str_time = ft_itoa(fps);
	if (str_time == NULL)
		clean_exit(game, "malloc", EXIT_FAILURE);
	str_fps = ft_strjoin("FPS: ", str_time);
	free(str_time);
	if (str_fps == NULL)
		clean_exit(game, "malloc", EXIT_FAILURE);
	background = mlx_new_image(game->mlx, 50, 20);
	mlx_put_image_to_window(game->mlx, game->win,
		background, WIN_WIDTH - 55, 15);
	mlx_string_put(game->mlx, game->win, WIN_WIDTH - 50, 30,
		C_PURE_WHITE, str_fps);
	free(str_fps);
	mlx_destroy_image(game->mlx, background);
}
