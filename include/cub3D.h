/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:28:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/22 16:47:41 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
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
# define T_MICROSEC 1000000
# define P_MOVE_SPEED 500000
# define P_ROTATE_SPEED 500000
# define FIRST_HIT_X 1
# define FIRST_HIT_Y 0
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEXTURE_SIZE 64
# define P_POV 16 / 9.0f
# define W 119
# define A 97
# define S 115
# define D 100
# define C_RED "\001\x1B[31m\002"
# define C_GRN "\001\x1B[32m\002"
# define C_YELLOW "\001\x1B[33m\002"
# define C_BLU "\001\x1B[34m\002"
# define C_MAG "\001\x1B[35m\002"
# define C_RESET "\001\x1B[0m\002"
# define C_SKY_BLUE 0xa3e0e5
# define C_WALL_BROWN 0x47281b
# define C_FLOOR_SAND 0xeda85b

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
	char	moving;
	char	rotating;
}			t_player;

typedef struct s_ray_params
{
	t_pos	view;
	t_pos	start_x;
	t_pos	start_y;
	t_pos	step_x;
	t_pos	step_y;
}			t_ray;

typedef struct s_hit_parameters
{
	float	dist;
	char	type;
	float	column;
}			t_hit;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_textures
{
	t_img	wall_n;
	t_img	wall_s;
	t_img	wall_w;
	t_img	wall_e;
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
	time_t	last_frame_time;
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
void	clean_exit(t_game *map, char *error, int exit_code);
int		close_game(t_game *data);
void	initialize_data( t_game *data);
int		key_press(int key, t_game *data);
int		key_release(int key, t_game *game);
time_t	get_time(void);
void	clean_double_array(char **arr, int n);

//maths
t_pos	mult_scalar(t_pos vector, float mult);
t_pos	add_vectors(t_pos a, t_pos b);
t_pos	subtr_vectors(t_pos a, t_pos b);
t_pos	rotate_vector(t_pos vector, float angle);

//rendering

t_hit	cast_ray(t_game *data, float column);
int		render_frame(t_game *game);
void	create_screen(t_game *game);

//gaming
void	move_player(t_game *game, int key);
void	rotate_player(t_game *game, int key);

//debug
void	create_dummy_map(t_game *data);

//parse
int		parse_cub(t_game *game, char *path);
int		parse_rgb(t_game *game, char *str);
int		is_map_line(char *line);
void	set_player(t_player *p, char c, int x, int y);
void	load_texture(t_game *game, char *path, t_img *dest);

#endif
