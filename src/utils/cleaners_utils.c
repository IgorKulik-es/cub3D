/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:37:31 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/01 12:39:56 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_double_array(char **arr, int n)
{
	int	index;

	index = 0;
	while (index < n)
	{
		if (arr[index] != NULL)
			free(arr[index]);
		index++;
	}
	free(arr);
}

void	free_texture(void *mlx, t_img *tex)
{
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

void	safe_free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
