/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:54:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/18 18:52:21 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# else
#  if BUFFER_SIZE < 1
#   error BUFFER SIZE INVALID
#  endif
# endif

typedef struct s_list_g
{
	char			*str;
	int				len;
	struct s_list_g	*next;
	struct s_list_g	*prev;
}				t_list_g;

typedef struct s_gnl_ctrl
{
	int			type_guide;
	int			read_bytes;
	int			nwl;
	char		*result;
}				t_gnl_ctrl;

void		*ft_lstclear_g(t_list_g **lst);
void		*ft_lstadd_front_g(t_list_g **lst);
char		*get_next_line(int fd);
t_list_g	*find_position(char *buffer, t_gnl_ctrl *ctrl, int type);
void		clean_buffer(char *buffer, int start);
#endif
