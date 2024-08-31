# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 09:38:27 by rapcampo          #+#    #+#              #
#    Updated: 2024/08/31 17:54:46 by rapcampo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Files ======================================

NAME	= Philo
SOURCE	= srcs/*.c
OBJS	= objs/*.o
DEPFLG	= -MP -MD

# ============================ Folder Structures ===============================

HEADERS		= includes
SOURCE_DIR	= srcs
OBJS_DIR	= objs

# ============================ Commands & Flags ===============================

CC			= cc
RM			= rm -rf
AR			= ar -rcs
FLAGS		= -Wall -Werror -Wextra -I$(HEADERS) -pthread -O3 #$(DEPFLG)
DEBUG		= -g -fsanitize=thread
MAKE_FLAG	= --no-print-directory

# =========================== Ansi Escape Codes ================================

ULINE	= \e[4m
BLINK	= \e[5m
BLACK 	= \e[1;30m
RED 	= \e[1;31m
GREEN 	= \e[1;32m
YELLOW 	= \e[1;33m
BLUE	= \e[1;34m
PURPLE 	= \e[1;35m
CYAN 	= \e[1;36m
WHITE 	= \e[1;37m
RESET	= \e[0m

# ================================ Rules =======================================

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) -o $@ $^ 
	echo "\n*************************$(GREEN)$(BLINK)    [Compilation Sucessfull!]    $(RESET)*************************\n"

$(OBJS): 
	echo "[$(PURPLE)$(BLINK)Compiling...$(RESET)] $(YELLOW)sources$(RESET)"
	mkdir -p objs
	$(CC) $(FLAGS) -c $(SOURCE)
	mv *.o $(OBJS_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_DIR)
	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Philosophers Objects have been removed sucessfully$(RESET)    +++++++++++++++\n\n"

fclean: clean
	$(RM) $(NAME)
	echo "\n\n++++++++++++++    $(ULINE)$(GREEN)Philosophers components and program removed successfully$(RESET)    +++++++++++++++\n\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
