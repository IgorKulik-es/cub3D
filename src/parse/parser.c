/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:17:44 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/21 16:14:19 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void parse_map_lines(t_game *data, char **lines, int count)
{
	int width;
	int i;
	int x;
	int y;
	char c;

	width = 0;
	i = 0;
	while (i < count)
	{
		if ((int)ft_strlen(lines[i]) > width)
			width = ft_strlen(lines[i]);
		i++;
	}
	data->map.height = count;
	data->map.width = width;
	data->map.map = malloc(sizeof(char *) * count);
	if (!data->map.map)
		error("Malloc failed");
	y = 0;
	while (y < count)
	{
		data->map.map[y] = malloc(sizeof(char) * (width + 1));
		if (!data->map.map[y])
			error("Malloc failed");
		x = 0;
		while (x < width)
		{
			if (x < (int)ft_strlen(lines[y]))
				c = lines[y][x];
			else
				c = ' ';
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player(&data->player, c, x, y);
				c = '0';
			}
			data->map.map[y][x] = c;
			x++;
		}
		data->map.map[y][width] = '\0';
		y++;
	}
}

char *skip_spaces(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

int count_map_lines(char *path)
{
	int fd;
	int count = 0;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Cannot open .cub file");
	line = get_next_line(fd);
	while (line)
	{
		char *trimmed = ft_strtrim(line, " \n");
		free(line);
		line = trimmed;
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int parse_cub(t_game *data, char *path)
{
	int		fd;
	char	*line;
	char	**map_lines;
	int		map_count;
	int		total_map_lines;
	char	*trimmed;
	int		i;

	map_count = 0;
	total_map_lines = count_map_lines(path);
	map_lines = malloc(sizeof(char *) * (total_map_lines + 1));
	if (!map_lines)
		return (error("Malloc failed"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("Cannot open .cub file"), 1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		line = trimmed;
		if (ft_strncmp(line, "NO", 2) == 0)
			load_texture(data->mlx, skip_spaces(line + 2), &data->texts.wall_n);
		else if (ft_strncmp(line, "SO", 2) == 0)
			load_texture(data->mlx, skip_spaces(line + 2), &data->texts.wall_s);
		else if (ft_strncmp(line, "WE", 2) == 0)
			load_texture(data->mlx, skip_spaces(line + 2), &data->texts.wall_w);
		else if (ft_strncmp(line, "EA", 2) == 0)
			load_texture(data->mlx, skip_spaces(line + 2), &data->texts.wall_e);
		else if (ft_strncmp(line, "F", 1) == 0)
			data->texts.bot_color = parse_rgb(skip_spaces(line + 1));
		else if (ft_strncmp(line, "C", 1) == 0)
			data->texts.top_color = parse_rgb(skip_spaces(line + 1));
		else if (is_map_line(line))
			map_lines[map_count++] = line;
		else
		{
			free(line);
			return (error("Invalid line in .cub"), 1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	parse_map_lines(data, map_lines, map_count);
	i = 0;
	while (i < map_count)
	{
		free(map_lines[i]);
		i++;
	}
	free(map_lines);
	return (0);
}
