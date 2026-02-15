# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucho <lucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/18 11:17:27 by luimarti          #+#    #+#              #
#    Updated: 2026/02/15 16:44:40 by lucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

MANDATORY_SRC = main.c \
				parsing.c \
				box_of_tools.c \
				init_of_structs.c \
				philo_routine.c \
				timing_and_death_monitor.c \
				general_cleaning.c
				
OBJ_DIR = o_files
MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))

RM = rm -f

all: $(NAME)


$(NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "🧹 Object files removed"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "🗑️  Full clean done"

re: fclean all

.PHONY: all clean fclean re

