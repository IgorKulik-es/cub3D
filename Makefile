# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikulik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/09/11 21:26:09 by ikulik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RED = \033[31;2m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

NAME		= cub3D

MAIN		= main_cub3D.c

UTIL		= cleaners.c get_next_line.c get_next_line_utils.c initialize.c basics.c\
			cleaners_utils.c frames_init.c texture_scaling.c

PARSE		= parser.c parse_utils.c map_parser.c map_utils.c parse_special.c\
			parse_textures.c

CONTROLS	= gaming.c colliders.c enemy_moves.c effects.c player_moves.c mouse_move.c

RENDER		= raycast.c raycast_utils.c vector_basics.c render_frame.c\
			render_utils.c render_floors.c post_processing.c render_walls.c\
			vector_advanced.c

ANIMATION	= door.c animation.c enemies_init.c animation_utils.c banners.c\
			render_enemies.c

INTERFACE	= draw_minimap.c minimap_utils.c fps_counter.c hit_points.c

PARSEDIR	= src/parse
UTILDIR		= src/utils
MAINDIR		= src/main
CONTROLSDIR	= src/controls
RENDERDIR	= src/render
ANIMDIR		= src/animation
INTERFDIR	= src/interface
MAINSRC		= $(addprefix $(MAINDIR)/, $(MAIN))
UTILSRC		= $(addprefix $(UTILDIR)/, $(UTIL))
PARSESRC	= $(addprefix $(PARSEDIR)/, $(PARSE))
CONTROLSSRC	= $(addprefix $(CONTROLSDIR)/, $(CONTROLS))
RENDERSRC	= $(addprefix $(RENDERDIR)/, $(RENDER))
ANIMSRC		= $(addprefix $(ANIMDIR)/, $(ANIMATION))
INTERFSRC	= $(addprefix $(INTERFDIR)/, $(INTERFACE))
SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

LIBRARY = minilibx-linux/libmlx_Linux.a
LIBGIT = https://github.com/42paris/minilibx-linux.git

SRCS		= $(MAINSRC) $(PARSESRC) $(UTILSRC) $(CONTROLSSRC) $(RENDERSRC) $(ANIMSRC) $(INTERFSRC)

OBJS		= $(SRCS:src/%.c=obj/%.o)

CFLAGS		= -Wall -Wextra -Werror -g3
MFLAGS		= -L libft -lft -L./minilibx-linux -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm
INCLUDES	= -I$(INCLUDE)
TOTAL_SRCS	= $(words $(MAINSRC) $(PARSESRC) $(UTILSRC) $(CONTROLSSRC) $(RENDERSRC) $(ANIMSRC) $(INTERFSRC))
SRC_NUM		= 0

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
	@rm -rf minilibx-linux/.git minilibx-linux/.github
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
