# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikulik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/08/18 19:31:30 by ikulik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RED = \033[31;2m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

NAME		= cub3D

MAIN		= main_cub3D.c

UTIL		= cleaners.c get_next_line.c get_next_line_utils.c

PARSE		=

CONTROLS	= gaming.c

PARSEDIR	= src/parse
UTILDIR		= src/utils
MAINDIR		= src/main
CONTROLSDIR	= src/controls
MAINSRC		= $(addprefix $(MAINDIR)/, $(MAIN))
UTILSRC		= $(addprefix $(UTILDIR)/, $(UTIL))
PARSESRC	= $(addprefix $(PARSEDIR)/, $(PARSE))
CONTROLSSRC	= $(addprefix $(CONTROLSDIR)/, $(CONTROLS))
SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

LIBRARY = minilibx-linux/libmlx_Linux.a
LIBGIT = https://github.com/42paris/minilibx-linux.git

SRCS		= $(MAINSRC) $(PARSESRC) $(UTILSRC) $(CONTROLSSRC)

OBJS		= $(SRCS:src/%.c=obj/%.o)

CFLAGS		= -Wall -Wextra -Werror -g3
MFLAGS		= -L libft -lft -L./minilibx-linux -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm -lz
INCLUDES	= -I$(INCLUDE)
TOTAL_SRCS	= $(words $(MAINSRC) $(PARSESRC) $(UTILSRC) $(CONTROLSSRC))
SRC_NUM		= 0
MINLIBX_NUM	= 0
TOTAL_MLBX	= 41

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJDIR) $(OBJS)
	@$(MAKE) -C libft > /dev/null 2>&1
	@cc $(OBJS) $(LIBRARY) $(INCLUDES) $(MFLAGS) -o $(NAME)
	@echo

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d%% $(RESET)" $(PERCENT)
	@cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBRARY):
	@git clone $(LIBGIT) minilibx-linux > /dev/null 2>&1
	@cd minilibx-linux && ./configure
	@cd ..
	@echo

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@$(MAKE) -C libft clean > /dev/null 2>&1
	@$(RM) $(OBJDIR)

fclean: clean
	@$(MAKE) -C libft fclean > /dev/null 2>&1
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
