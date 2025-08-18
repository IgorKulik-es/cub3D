/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:55:49 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/18 18:54:52 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	*ft_lstadd_front_g(t_list_g **lst)
{
	t_list_g	*new;

	new = (t_list_g *)malloc(sizeof(t_list_g));
	if (new == NULL)
		return (ft_lstclear_g(lst));
	new->str = (char *)malloc(BUFFER_SIZE + 1);
	if (new->str == NULL)
		return (ft_lstclear_g(lst));
	clean_buffer(new->str, 0);
	new->next = *lst;
	new->prev = NULL;
	if (*lst != NULL)
	{
		(*lst)->prev = new;
		new->len = (*lst)->len + 1;
	}
	else
		new->len = 1;
	*lst = new;
	return (*lst);
}

void	*ft_lstclear_g(t_list_g **lst)
{
	t_list_g	*iter;
	t_list_g	*cleaner;

	iter = *lst;
	while (iter)
	{
		cleaner = iter;
		iter = iter->next;
		free(cleaner->str);
		free(cleaner);
	}
	*lst = NULL;
	return (NULL);
}

t_list_g	*find_position(char *buffer, t_gnl_ctrl *ctrl, int type)
{
	int	index;

	index = 0;
	if (type & 1)
	{
		while (index < ctrl->read_bytes && buffer[index] != '\n'
			&& buffer[index] != '\0')
			index++;
		if (index == ctrl->read_bytes || buffer[index] == '\0')
			index = BUFFER_SIZE;
		ctrl->nwl = index;
	}
	if (type & 2)
	{
		ctrl->type_guide = 0;
		while (ctrl->type_guide < BUFFER_SIZE
			&& buffer[ctrl->type_guide] != '\0')
			ctrl->type_guide++;
		if (ctrl->type_guide < BUFFER_SIZE)
			ctrl->type_guide--;
		if (buffer[0] == '\0')
			ctrl->type_guide = BUFFER_SIZE;
	}
	return (NULL);
}

void	clean_buffer(char *buffer, int start)
{
	while (start < BUFFER_SIZE + 1)
	{
		buffer[start] = 0;
		start++;
	}
}
