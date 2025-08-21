/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 16:14:50 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	data;

	(void)argv;
	(void)argc;
	if (argc != 2)
		return(error("Add only one argument ended in .cub"), 1);
	if (parse_cub(&data, argv[1]))
		return (1);
	initialize_data(&data);
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
