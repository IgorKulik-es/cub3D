/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:33:27 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/05 14:33:43 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_texture(t_game *game, char *path, t_img *dest, t_parse_ctx *ctx)
{
	dest->img = mlx_xpm_file_to_image(game->mlx, path,
			&dest->width, &dest->height);
	if (!dest->img)
		parser_error(game, ctx, "Texture load failed");
	dest->addr = (int *)mlx_get_data_addr(dest->img, &(dest->bpp),
			&(dest->line_length), &(dest->endian));
}

void	handle_color_line(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "F", 1) == 0)
		game->texts.bot_color = parse_rgb(game, ctx);
	else if (ft_strncmp(ctx->line, "C", 1) == 0)
		game->texts.top_color = parse_rgb(game, ctx);
}
