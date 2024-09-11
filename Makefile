# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 12:33:04 by luibarbo          #+#    #+#              #
#    Updated: 2024/07/19 15:12:47 by luibarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#	GENERAL                                                                    #
# ============================================================================ #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

NAME_SERVER	= server
NAME_CLIENT	= client

NAME_SERVER_BONUS	= server_bonus
NAME_CLIENT_BONUS	= client_bonus

# ============================================================================ #
#	MANDATORY                                                                  #
# ============================================================================ #

SRC_SERVER			= src/server.c
SRC_CLIENT			= src/client.c
SRC_BONUS_SERVER	= src_bonus/server_bonus.c
SRC_BONUS_CLIENT	= src_bonus/client_bonus.c

INCLUDES			= -Ilibft/include

LIBFT				= ./libft/libft.a
LIBFT_PATH			= ./libft

# ============================================================================ #
#	RULES                                                                      #
# ============================================================================ #

CLR_RMV	= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN 	= \033[1;36m

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT)
	@ echo "Compilation of ${YELLOW}$(NAME_SERVER) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDES) $(SRC_SERVER) $(LIBFT) -o $(NAME_SERVER)
	@ echo "$(GREEN)$(NAME_SERVER) created[0m"

$(NAME_CLIENT): $(LIBFT)
	@ echo "Compilation of ${YELLOW}$(NAME_CLIENT) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDES) $(SRC_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
	@ echo "$(GREEN)$(NAME_CLIENT) created[0m"

$(LIBFT): $(shell make -C $(LIBFT_PATH) -q libft.a)
	@ make -C $(LIBFT_PATH)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(LIBFT)
	@ echo "Compilation of ${YELLOW}$(NAME_SERVER_BONUS) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDES) $(SRC_BONUS_SERVER) $(LIBFT) -o $(NAME_SERVER_BONUS)
	@ echo "$(GREEN)$(NAME_SERVER_BONUS) created[0m"

$(NAME_CLIENT_BONUS): $(LIBFT)
	@ echo "Compilation of ${YELLOW}$(NAME_CLIENT_BONUS) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDES) $(SRC_BONUS_CLIENT) $(LIBFT) -o $(NAME_CLIENT_BONUS)
	@ echo "$(GREEN)$(NAME_CLIENT_BONUS) created[0m"

clean:
	@ make clean -C $(LIBFT_PATH)

fclean:
	@ make fclean -C $(LIBFT_PATH)
	@ $(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@ echo "$(RED)Deleting $(CLR_RMV)binary"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
