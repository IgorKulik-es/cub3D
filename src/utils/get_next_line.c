/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:53:13 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/18 18:53:58 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	record_last(char *b_s, t_list_g **lst, t_gnl_ctrl *ctrl, size_t i)
{
	if (ctrl->nwl < BUFFER_SIZE)
	{
		ft_strlcpy(&(ctrl->result[i]), (*lst)->str, ctrl->nwl + 2);
		ft_strlcpy(b_s, &((*lst)->str[ctrl->nwl + 1]),
			ctrl->read_bytes - ctrl->nwl);
	}
	else
	{
		ft_strlcpy(&(ctrl->result[i]), (*lst)->str, ctrl->read_bytes + 1);
		clean_buffer(b_s, 0);
	}
}

static void	asign_memory(char *buffer_static, t_list_g **lst, t_gnl_ctrl *ctrl)
{
	size_t	i;

	i = 0;
	if (ctrl->type_guide < BUFFER_SIZE)
	{
		i = ft_strlcpy(ctrl->result, buffer_static, ctrl->type_guide + 2);
		clean_buffer(buffer_static, 0);
	}
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	while ((*lst)->prev)
	{
		i += ft_strlcpy(&(ctrl->result[i]), (*lst)->str, BUFFER_SIZE + 1);
		*lst = (*lst)->prev;
	}
	if (ctrl->read_bytes > 0)
		record_last(buffer_static, lst, ctrl, i);
	ctrl->nwl = 0;
}

static char	*create_output(char *b_s, t_list_g **lst, t_gnl_ctrl *ctrl)
{
	size_t	size;

	if (lst != NULL)
	{
		size = BUFFER_SIZE * ((*lst)->len - 1) + 1;
		if (ctrl->type_guide < BUFFER_SIZE)
			size += ctrl->type_guide + 1;
		if (ctrl->nwl < BUFFER_SIZE)
			size += ctrl->nwl + 1;
	}
	else
		size = ctrl->nwl + 2;
	ctrl->result = (char *)malloc(size);
	if (ctrl->result == NULL)
		return (NULL);
	if (lst == NULL)
	{
		ft_strlcpy(ctrl->result, b_s, ctrl->nwl + 2);
		ft_strlcpy(b_s, &(b_s[ctrl->nwl + 1]), BUFFER_SIZE - ctrl->nwl);
		if (ctrl->nwl == BUFFER_SIZE)
			clean_buffer(b_s, 0);
	}
	else
		asign_memory(b_s, lst, ctrl);
	return (ctrl->result);
}

static char	*process_read_results(char *b_s, t_list_g **lst, t_gnl_ctrl *ctrl)
{
	if (ctrl->read_bytes == 0 && ctrl->type_guide == BUFFER_SIZE
		&& (*lst)->len == 1)
		return (ft_lstclear_g(lst));
	find_position((*lst)->str, ctrl, 1);
	if (!(ctrl->read_bytes == BUFFER_SIZE && ctrl->nwl == BUFFER_SIZE))
	{
		if (ctrl->read_bytes < BUFFER_SIZE && ctrl->nwl == BUFFER_SIZE)
			ctrl->nwl = ctrl->read_bytes - 1;
		if (!create_output(b_s, lst, ctrl))
			return (ft_lstclear_g(lst));
		ctrl->nwl = 0;
		ft_lstclear_g(lst);
		return (ctrl->result);
	}
	return (b_s);
}

char	*get_next_line(int fd)
{
	static char	buffer_static[BUFFER_SIZE + 1];
	t_list_g	*lst_read;
	t_gnl_ctrl	ctrl;

	if (fd < 0)
		return (NULL);
	ctrl.read_bytes = BUFFER_SIZE;
	lst_read = find_position(buffer_static, &ctrl, 3);
	if (ctrl.nwl < BUFFER_SIZE && buffer_static[ctrl.nwl] == '\n')
		return (create_output(buffer_static, NULL, &ctrl));
	ctrl.nwl = BUFFER_SIZE;
	while (ctrl.nwl == BUFFER_SIZE)
	{
		if (ft_lstadd_front_g(&lst_read) == NULL)
			return ((char *)ft_lstclear_g(&lst_read));
		ctrl.read_bytes = read(fd, lst_read->str, BUFFER_SIZE);
		if (ctrl.read_bytes < 0)
		{
			clean_buffer(buffer_static, 0);
			return ((char *)ft_lstclear_g(&lst_read));
		}
		if (process_read_results(buffer_static, &lst_read, &ctrl) == NULL)
			return ((char *)ft_lstclear_g(&lst_read));
	}
	return (ctrl.result);
}
