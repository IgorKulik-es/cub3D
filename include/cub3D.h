/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:28:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/28 12:43:23 by vtrofyme         ###   ########.fr       */
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
# define HIT 1
# define MISS 0
# define D_TYPE_VERT 1
# define D_TYPE_HOR 0
# define D_STATE_CLOSED 1
# define D_STATE_OPEN 0
# define DOOR_WALL 'F'
# define MAP_ERROR 2
# define WALL '1'
# define EMPTY '0'
# define MAX_DOORS 10
# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'
# define ESC XK_Escape
# define T_MICROSEC 1000000
# define P_MOVE_SPEED 500000
# define P_DOOR_SPEED 2000000
# define P_DOOR_CL_TIME 2000000
# define P_ROTATE_SPEED 500000
# define FIRST_HIT_X 1
# define FIRST_HIT_Y 0
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEXTURE_SIZE 64
# define P_POV 1.7777777f
# define P_WALL_D 0.25f
# define W 119
# define A 97
# define S 115
# define D 100
# define SPACE 32
# define C_RED "\001\x1B[31m\002"
# define C_GRN "\001\x1B[32m\002"
# define C_YELLOW "\001\x1B[33m\002"
# define C_BLU "\001\x1B[34m\002"
# define C_MAG "\001\x1B[35m\002"
# define C_RESET "\001\x1B[0m\002"
# define C_SKY_BLUE 0xa3e0e5
# define C_WALL_BROWN 0x47281b
# define C_FLOOR_SAND 0xeda85b
# define MINIMAP_SCALE 15
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

typedef struct s_float_coordinates
{
	float	x;
	float	y;
}		t_pos;

typedef struct s_int_coordinates
{
	int	x;
	int	y;
}			t_coords;

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

typedef struct s_trapezoid
{
	int		left_height;
	int		right_height;
	int		width;
	int		last_pxl_right;
	int		x;
	int		y;
	float	top_pixel;
	float	bot_pixel;
	float	step_screen;
	float	step_width;
	float	step_height;
	int		i_screen;
	float	x_texture;
	float	y_texture;
	float	edge_left;
	float	hor_portion;
	float	edge_top;
	float	vert_portion;
}			t_trapz;

typedef struct s_ray_params
{
	t_pos	view;
	t_pos	start_x;
	t_pos	start_y;
	t_pos	step_x;
	t_pos	step_y;
	char	obst;
}			t_ray;

typedef struct s_hit_parameters
{
	float		dist;
	char		type;
	float		column;
	t_pos		point;
	t_coords	tile;
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
	t_img	door;
	int		bot_color;
	int		top_color;
	int		wall_color;
}			t_textures;

typedef struct s_door_anim
{
	int		x;
	int		y;
	float	width;
	bool	state;
	int		moving;
	int		type;
	time_t	last_open;
}			t_door;


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
	int			debug_printed;
	int			num_doors;
	int			dist[WIN_WIDTH];
	t_screen	screen;
	t_map_data	map;
	t_player	player;
	t_textures	texts;
	t_door		*doors;
}			t_game;

typedef struct s_parse_ctx
{
	char	*line;
	char	**map_lines;
	int		map_count;
}	t_parse_ctx;

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
float	vector_length(t_pos vector);
float	tangent_known_length(t_pos a, t_pos b, float len_a, float len_b);

//raycasting

t_hit	cast_ray(t_game *data, float column);
void	find_intersects(t_game *data, t_pos player, t_ray *ray);
t_pos	find_collision_neg_x(t_game *data, t_ray *ray, t_hit *hit);
t_pos	find_collision_pos_x(t_game *data, t_ray *ray, t_hit *hit);
t_hit	check_visibility(t_game *game, t_pos start, t_pos end);
t_door	*find_door(t_game *game, int x, int y);

//rendering

int		render_frame(t_game *game);
void	create_screen(t_game *game);
void	put_tapezoid_to_img(t_screen *screen, t_img *texture, t_trapz trpz);
void	draw_minimap(t_game *game);

//gaming
void	move_player(t_game *game, int key);
void	rotate_player(t_game *game, int key);
void	move_door(t_game *game, t_door *door);
bool	check_collision(t_game *game, t_pos *new);
void	open_door(t_game *game);

//debug
void	create_dummy_map(t_game *data);

//parse
int		parse_cub(t_game *game, char *path);
int		parse_rgb(t_game *game, t_parse_ctx *ctx);
int		is_map_start(char *line);
void	set_player(t_player *p, char c, int x, int y);
void	load_texture(t_game *game, char *path, t_img *dest, t_parse_ctx *ctx);
void	handle_color_line(t_game *game, t_parse_ctx *ctx);
void	parser_error(t_game *game, t_parse_ctx *ctx, char *msg);
void	parse_map_lines(t_game *game, t_parse_ctx *ctx);
int		count_map_lines(t_game *game, char *path);
char	*skip_spaces(char *str);
void	validate_map(t_game *game, t_parse_ctx *ctx);
void	count_doors(t_game *game);
void	add_doors(t_game *game);

#endif
