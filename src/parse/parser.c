/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:17:44 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/21 12:19:14 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// ---------------------- Утилиты ----------------------
void	error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int	parse_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		error("Invalid RGB format");
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("RGB out of range");
	for (int i = 0; i < 3; i++)
		free(split[i]);
	free(split);
	return ((r << 16) | (g << 8) | b);
}

int is_map_line(char *line)
{
	int i = 0, has = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
			return 0;
		if (line[i] != ' ')
			has = 1;
		i++;
	}
	return has;
}

void set_player(t_player *p, char c, int x, int y)
{
	p->pos.x = x + 0.5f;
	p->pos.y = y + 0.5f;
	if (c == 'N')
	{
		p->facing = (t_pos){0, -1};
		p->camera = (t_pos){0.66, 0};
	}
	else if (c == 'S')
	{
		p->facing = (t_pos){0, 1};
		p->camera = (t_pos){-0.66, 0};
	}
	else if (c == 'E')
	{
		p->facing = (t_pos){1, 0};
		p->camera = (t_pos){0, 0.66};
	}
	else if (c == 'W')
	{
		p->facing = (t_pos){-1, 0};
		p->camera = (t_pos){0, -0.66};
	}
}

// ---------------------- Загрузка текстур ----------------------
void load_texture(void *mlx, char *path, void **dest)
{
	int w, h;
	*dest = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!*dest)
		error("Texture load failed");
}

// ---------------------- Парсинг карты ----------------------
void parse_map_lines(t_mlx_data *mlx, char **lines, int count)
{
	int width = 0;
	for (int i = 0; i < count; i++)
		if ((int)ft_strlen(lines[i]) > width)
			width = ft_strlen(lines[i]);

	mlx->map.height = count;
	mlx->map.width = width;

	mlx->map.map = malloc(sizeof(char *) * count);
	if (!mlx->map.map)
		error("Malloc failed");

	for (int y = 0; y < count; y++)
	{
		mlx->map.map[y] = malloc(sizeof(char) * (width + 1));
		if (!mlx->map.map[y])
			error("Malloc failed");
		for (int x = 0; x < width; x++)
		{
			char c = (x < (int)ft_strlen(lines[y])) ? lines[y][x] : ' ';
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player(&mlx->player, c, x, y);
				c = '0';
			}
			mlx->map.map[y][x] = c;
		}
		mlx->map.map[y][width] = '\0';
	}
}

// ---------------------- Основной парсер ----------------------
void parse_cub(t_mlx_data *mlx, char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Cannot open .cub file");

	char *line;
	char *map_lines[1024]; // Максимум строк карты
	int map_count = 0;

	while ((line = get_next_line(fd)))
	{
		line = ft_strtrim(line, " \n");
	int	got_no;
		else if (ft_strncmp(line, "SO ", 3) == 0)
			load_texture(mlx->mlx, line + 3, &mlx->texts.wall_s);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			load_texture(mlx->mlx, line + 3, &mlx->texts.wall_w);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			load_texture(mlx->mlx, line + 3, &mlx->texts.wall_e);
		else if (ft_strncmp(line, "F ", 2) == 0)
			mlx->texts.bot_color = parse_rgb(line + 2);
		else if (ft_strncmp(line, "C ", 2) == 0)
			mlx->texts.top_color = parse_rgb(line + 2);
		else if (is_map_line(line))
			map_lines[map_count++] = line;
		else
		{
			free(line);
			error("Invalid line in .cub");
		}
	}

	parse_map_lines(mlx, map_lines, map_count);
	close(fd);
}
