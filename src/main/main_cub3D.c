/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:17 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/30 14:26:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_arguments(int argc);

int	main(int argc, char **argv)
{
	t_game	game;
	int		dummy;

	check_arguments(argc);
	initialize_data(&game);
	game.mlx = mlx_init();
	if (parse_cub(&game, argv[1]))
		return (1);
	count_doors(&game);
	add_doors(&game);
	create_screen(&game);
	mlx_do_key_autorepeatoff(game.mlx);
	game.player.camera = mult_scalar(game.player.camera, P_POV);
	ft_bzero(&(game.test), sizeof(t_entity));
	game.test.anims[0].img.img = mlx_xpm_file_to_image(game.mlx, "./textures/boss_walk_front.xpm", &(game.test.anims[0].img.width), &(game.test.anims[0].img.height));
	game.test.anims[0].img.addr = (int *)mlx_get_data_addr(game.test.anims[0].img.img, &(game.test.anims[0].img.bpp), &(dummy), &(game.test.anims[0].img.endian));
	game.test.pos.x = 19;
	game.test.pos.y = 9;
	game.test.mode = ACTION;
	game.test.anims[0].active = 1;
	set_anim_frames(&game, &(game.test.anims[0]));
	game.test.anims[0].c_frame = 0;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0L, close_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}

static void	check_arguments(int argc)
{
	if (argc < 2)
	{
		printf("Error: no map file.\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf("Error: too many arguments.\n");
		exit(EXIT_FAILURE);
	}
	else
		return ;
}
