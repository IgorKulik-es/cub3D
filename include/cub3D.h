/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:28:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 18:39:07 by ikulik           ###   ########.fr       */
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
# include <X11/X.h>

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
# define T_EXIT 'X'
# define T_ENEMY 'Q'
# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'
# define ESC XK_Escape
# define T_MICROSEC 1000000
# define P_ANIM_SPEED 1000000
# define P_MOVE_SPEED 300000
# define P_DOOR_SPEED 1000000
# define P_ENEMY_SPEED 800000
# define P_DOOR_CL_TIME 2000000
# define P_ROTATE_SPEED 300000
# define P_COLOR_SPEED 2000000.0f
# define P_BAN_SPEED 1200000
# define P_INTRO_TIME 300000
# define P_RED_SHIFT 1.4f
# define P_BASE_HP 3
# define P_POV 1.0f
# define P_ENEMY_TRANSP 0.5f
# define P_WALL_D 0.25f
# define E_STATE_CALM 1
# define E_STATE_ANGRY 2
# define E_DET_RADIUS 3
# define E_ATT_RANGE 1.3f
# define E_DAM_RADIUS 1.80f
# define FIRST_HIT_X 1
# define FIRST_HIT_Y 0
# define WIN_UPSC_FACTOR 3.0f
# define WIN_WIDTH 2560
# define WIN_HEIGHT 1440
# define WIN_DARK_FACTOR 0.7f
# define WIN_LIGHT_RADIUS 2.0f
# define WIN_UI_OFFSET 20
# define WIN_UI_SCALE 16
# define TEXTURE_SIZE 256
# define M_NO_TEXTURE 0
# define M_FL_TEXTURE 1
# define M_CEIL_TEXTURE 2
# define M_VISIBLE_HP 4
# define M_GAME_OVER_PL 8
# define M_VICTORY_PL 16
# define M_INTRO_PL 32
# define M_MINIMAP 1
# define M_FPS 2
# define M_HP 4
# define M_DARK 8
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
# define C_BLANK -0x1000000
# define C_SKY_BLUE 0xa3e0e5
# define C_WALL_BROWN 0x47281b
# define C_PURE_WHITE 0xffffff
# define C_FLOOR_SAND 0xeda85b
# define SENSITIVITY 0.002f
# define Q_PI 0.785398163f
# define THQ_PI 2.35619449f
# define D_PI 6.283185307f


typedef enum e_modes
{
	ACTION,
	WALK_FRONT,
	WALK_BACK,
	WALK_LEFT,
	WALK_RIGHT,
	NUM_ANIM
}			t_mode;

typedef enum e_game_states
{
	INTRO,
	WIN,
	LOSE,
	PLAY
}			t_g_state;

typedef struct s_float_coordinates
{
	float	x;
	float	y;
}		t_pos;

typedef struct s_color_shift
{
	float	r;
	float	g;
	float	b;
}			t_c_shift;

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
	t_pos		pos;
	t_pos		facing;
	t_pos		camera;
	t_coords	tile;
	int			hp;
	float		inv_det;
	char		moving;
	char		rotating;
}			t_player;

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

typedef struct s_banners
{
	t_img		img[PLAY];
	time_t		last_change;
	float		pos;
	int			move;
}			t_bans;

typedef struct s_textures
{
	t_img	wall_n;
	t_img	wall_s;
	t_img	wall_w;
	t_img	wall_e;
	t_img	door;
	t_img	door_w;
	t_img	floor;
	t_img	ceiling;
	t_img	hp;
	t_bans	bans;
	int		bot_color;
	int		top_color;
	int		draw_mode;
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

typedef struct s_anim_prototype
{
	t_img	img;
	t_img	*frames;
	int		num_fr;
}				t_anim_p;

typedef struct s_anim_prots
{
	t_anim_p	walk_front;
	t_anim_p	walk_back;
	t_anim_p	walk_left;
	t_anim_p	walk_right;
	t_anim_p	action;
	t_anim_p	exit;
}			t_anim_en;

typedef struct s_anim_data
{
	t_img	**frames;
	time_t	last_frame;
	time_t	time_per_frame;
	int		c_frame;
	int		num_fr;
	bool	active;
}			t_anim;

typedef struct s_entity_data
{
	t_anim	anims[NUM_ANIM];
	t_pos	pos;
	int		state;
	t_pos	trans;
	t_pos	view;
	float	dist;
	t_pos	face;
	t_mode	mode;
	t_mode	turn;
	bool	is_pl_visible;
	bool	is_ent_visible;
	int		left_edge;
	int		right_edge;
	int		height;
}				t_entity;

typedef struct s_minimap
{
	int	scale;
	int	offset_x;
	int	offset_y;
}	t_minimap;

typedef struct s_screen_data
{
	void	*img;
	int		*pixels;
	int		win_w;
	float	half_w;
	int		win_h;
	float	half_h;
	time_t	last_frame_time;
	int		minimap_scale;
}			t_screen;

typedef struct s_game_data
{
	void		*mlx;
	void		*win;
	t_g_state	game_stage;
	int			debug_printed;
	int			num_doors;
	int			num_enemies;
	int			num_exits;
	int			last_mouse_x;
	float		d_max;
	float		darkness;
	int			mode;
	t_hit		hits[WIN_WIDTH];
	t_img		scr_upscaled;
	t_screen	screen;
	t_map_data	map;
	t_player	player;
	t_textures	texts;
	t_anim_en	anim_prot;
	t_c_shift	tint;
	t_entity	*enemies;
	t_door		*doors;
	t_anim		exit;
}			t_game;

typedef struct s_parse_ctx
{
	char	*line;
	char	**map_lines;
	int		map_count;
}	t_parse_ctx;

typedef struct s_line
{
	t_coords	d;
	t_coords	s;
	int			err;
}	t_line;

//utils
void		clean_exit(t_game *game, char *error, int exit_code);
int			close_game(t_game *game);
void		initialize_data( t_game *game);
time_t		get_time(void);
void		clean_double_array(char **arr, int n);
void		safe_free(void **ptr);
void		error_message(char *error, int exit_code);
void		free_texture(void *mlx, t_img *tex);
bool		correct_pixel(t_game *game, int	*pixel);
void		resize_texture(t_game *game, t_img *img, int new_width,
				int new_height);
void		setup_textures(t_game *game);
void		stretch_to_screen_width(t_game *game, t_img *img);
int			rgb_shift(int color, float r_mult, float g_mult, float b_mult);

//maths
t_pos		mult_scalar(t_pos vector, float mult);
t_pos		add_vectors(t_pos a, t_pos b);
t_pos		subtr_vectors(t_pos a, t_pos b);
t_pos		rotate_vector(t_pos vector, float angle);
float		vector_length(t_pos vector);
float		cross_product(t_pos a, t_pos b);
float		vectors_angle(t_pos a, t_pos b);
t_mode		determine_facing(t_entity *guy);

//raycasting
t_hit		cast_ray(t_game *game, float column);
void		calculate_steps(t_ray *ray);
void		find_intersects(t_game *game, t_pos player, t_ray *ray);
t_pos		find_collision_neg_x(t_game *game, t_ray *ray, t_hit *hit);
t_pos		find_collision_pos_x(t_game *game, t_ray *ray, t_hit *hit);
t_door		*find_door(t_game *game, int x, int y);
t_pos		dist_to_entity(t_game *game, t_entity *guy);

//rendering
int			render_frame(t_game *game);
void		create_screen(t_game *game);
void		draw_walls(t_game *game);
void		draw_floors(t_game *game, t_player *player);
void		upscale_screen(t_game *game);
void		put_img_to_srceen(t_game *game, t_img *img, int x, int y);
void		tint_screen(t_game *game);
void		blood_effect(t_game *game, float red);
void		mix_colors(int *old_px, int new_px, float weight);
void		restore_color(t_game *game, float target_tint);

//gaming
int			key_press(int key, t_game *game);
int			key_release(int key, t_game *game);
void		move_player(t_game *game, int key);
void		rotate_player(t_game *game, int key);
void		move_door(t_game *game, t_door *door);
void		move_enemy(t_game *game, t_entity *guy);
t_pos		smooth_collision(t_game *game, t_pos old, t_pos new);
void		open_door(t_game *game);
void		damage_player(t_game *game, t_entity *guy);
void		calm_down_enemy(t_entity *guy);
void		game_over(t_game *game);
int			mouse_move(int x, int y, t_game *game);
void		check_exit(t_game *game);

//user interface
void		draw_minimap(t_game *game);
void		put_pixel(t_screen *screen, int x, int y, int color);
void		draw_line(t_screen *screen, t_coords p, t_coords h, int color);
void		draw_square(t_screen *screen, int x, int y, int color);
t_minimap	get_minimap_params(t_game *game);
void		put_fps_counter(t_game *game, time_t time);
void		put_hp_on_screen(t_game *game);

//animation
void		load_animations(t_game *game);
void		update_all_positions(t_game *game);
void		update_enem_frame(t_game *game, t_entity *guy, t_anim *anim);
void		update_exit_frame(t_anim *exit);
void		set_anim_frames(t_game *game, t_anim_p *anim);
void		copy_anim(t_game *game, t_anim_p *proto, t_anim *copy);
bool		check_entity_visibility(t_game *game, t_entity *guy);
void		put_entity(t_game *game, t_entity *guy);
void		determine_animation(t_entity *guy);
void		animate_banners(t_game *game, t_bans *banners);

//debug
void		create_dummy_map(t_game *game);

//parse
int			parse_cub(t_game *game, char *path);
int			parse_rgb(t_game *game, t_parse_ctx *ctx);
int			is_map_start(char *line);
void		set_player(t_player *p, char c, int x, int y);
void		load_texture(t_game *game, char *path, t_img *dest,
				t_parse_ctx *ctx);
void		handle_color_line(t_game *game, t_parse_ctx *ctx);
void		parser_error(t_game *game, t_parse_ctx *ctx, char *msg);
void		parse_map_lines(t_game *game, t_parse_ctx *ctx);
int			count_map_lines(t_game *game, char *path);
char		*skip_spaces(char *str);
void		validate_map(t_game *game, t_parse_ctx *ctx);
int			count_items(t_game *game, char item);
void		load_doors(t_game *game);

#endif
