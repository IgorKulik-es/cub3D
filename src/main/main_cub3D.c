/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 20:06:05 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_mlx_data	data;

	(void)argv;
	(void)argc;
	create_dummy_map(&data);
	cast_ray(&data, &(data.screen), (float)WIN_WIDTH / 2.0f);
	//data.mlx = mlx_init();
	//data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	//mlx_hook(data.win, 2, 1L << 0, key_manager, &data);
	//mlx_hook(data.win, 17, 0L, close_game, &data);
	//mlx_loop(data.mlx);
}
//for map viewing and debug purposes
//
/* void	print_map(char **arr, int height)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < height)
	{
		write(1, arr[index], ft_strlen(arr[index]));
		write(1, "\n", 1);
		index++;
	}
} */
