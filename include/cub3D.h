/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:28:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 12:49:37 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include "get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define TOTAL 1
# define PARTIAL 0
# define MAP_ERROR 2
# define WALL '1'
# define EMPTY '0'
# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'
# define ESC XK_Escape
# define FIRST_HIT_X 1
# define FIRST_HIT_Y 0
# define WIN_WIDTH 2560
# define WIN_HEIGHT 1440
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_float_coordinates
{
	float	x;
	float	y;
}		t_pos;

typedef struct d_list
{
	char			*line;
	t_pos			pos;
	struct s_list	*next;
	struct s_list	*prev;
}			t_dlist;

typedef struct s_map_data
{
	int		width;
	int		height;
	int		num_empty;
	int		num_enem;
	char	**map;
	char	**map_copy;
}			t_map_data;

typedef struct s_player
{
	t_pos	pos;
	t_pos	facing;
	t_pos	camera;
}			t_player;

typedef struct s_ray_params
{
	t_pos	view;
	t_pos	start_x;
	t_pos	start_y;
	t_pos	step_x;
	t_pos	step_y;
	int		x_dir;
}			t_ray;

typedef struct s_textures
{
	void	*wall_n;
	void	*wall_s;
	void	*wall_e;
	void	*wall_w;
	int		bot_color;
	int		top_color;
	int		wall_color;
}			t_textures;

typedef struct s_screen_data
{
	void	*img;
	int		*pixels;
	int		win_w;
	float	half_w;
	int		win_h;
}			t_screen;

typedef struct s_game_data
{
	void		*mlx;
	void		*win;
	int			game_over;
	t_screen	screen;
	t_map_data	map;
	t_player	player;
	t_textures	texts;
}			t_game;

//utils
void	clean_exit(t_map_data *map, char *error, int exit_code);
int		close_game(t_game *data);
void	initialize_data( t_game *data);
int		key_manager(int key, t_game *data);

//maths
t_pos	mult_scalar(t_pos vector, float mult);
t_pos	add_vectors(t_pos a, t_pos b);
t_pos	subtr_vectors(t_pos a, t_pos b);
t_pos	rotate_vector(t_pos vector, float angle);

//raycasting

void	cast_ray(t_game *data, t_screen *screen, float x);

//debug
void	create_dummy_map(t_game *data);

#endif
