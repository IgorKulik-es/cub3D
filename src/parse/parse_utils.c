/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:18:34 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/21 15:08:53 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error(char *str)
{
	printf(C_RED "Error:\n %s" C_RESET "\n", str);
}

int	parse_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (error("Invalid RGB format"), 1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error("RGB out of range"), 1);
	i = 0;
	while (i < 3)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return ((r << 16) | (g << 8) | b);
}

int	is_map_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			flag = 1;
		i++;
	}
	return (flag);
}

void	set_player(t_player *p, char c, int x, int y)
{
	p->pos.x = x + 0.5f;
	p->pos.y = y + 0.5f;
	if (c == 'N')
	{
		p->facing = (t_pos){0, -1};
		p->camera = (t_pos){1, 0};
	}
	else if (c == 'S')
	{
		p->facing = (t_pos){0, 1};
		p->camera = (t_pos){-1, 0};
	}
	else if (c == 'E')
	{
		p->facing = (t_pos){1, 0};
		p->camera = (t_pos){0, 1};
	}
	else if (c == 'W')
	{
		p->facing = (t_pos){-1, 0};
		p->camera = (t_pos){0, -1};
	}
}
void	load_texture(void *mlx, char *path, void **dest)
{
	int	w;
	int	h;

	*dest = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!*dest)
		error("Texture load failed");
}
