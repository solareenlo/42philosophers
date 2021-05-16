# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/16 12:54:45 by tayamamo          #+#    #+#              #
#    Updated: 2021/05/16 12:54:45 by tayamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for philo_one, updated Sun May 16 12:54:45 JST 2021

SRC := ft_check_arg.c ft_check_int.c ft_init_func.c ft_time_func.c libft1.c libft2.c libft_ft_atoi.c main.c philo_utils.c thread_dining_philo.c thread_monitor_death.c thread_monitor_eat_cnt.c
OBJ := ft_check_arg.o ft_check_int.o ft_init_func.o ft_time_func.o libft1.o libft2.o libft_ft_atoi.o main.o philo_utils.o thread_dining_philo.o thread_monitor_death.o thread_monitor_eat_cnt.o

HDR := philo_one.h

# DO NOT ADD OR MODIFY ANY LINES ABOVE THIS -- run 'make source' to add files

NAME := philo_one

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
RM := rm -fr

SRC_DIR := ./
OBJ_DIR := obj
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

.PHONY:	all
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: thread
thread: CFLAGS += -g -fsanitize=thread
thread: re

.PHONY: leak
leak: CFLAGS += -g -fsanitize=leak
leak: re

.PHONY: address
address: CFLAGS += -g -fsanitize=address
address: re

.PHONY: clean
clean:
	$(RM) Makefile.bak $(NAME).dSYM $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: source
source:
	@mv Makefile Makefile.bak
	@echo "# **************************************************************************** #" > Makefile
	@echo "#                                                                              #" >> Makefile
	@echo "#                                                         :::      ::::::::    #" >> Makefile
	@echo "#    Makefile                                           :+:      :+:    :+:    #" >> Makefile
	@echo "#                                                     +:+ +:+         +:+      #" >> Makefile
	@echo "#    By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+         #" >> Makefile
	@echo "#                                                 +#+#+#+#+#+   +#+            #" >> Makefile
	@echo "#    Created: `date "+%Y/%m/%d %H:%M:%S"` by tayamamo          #+#    #+#              #" >> Makefile
	@echo "#    Updated: `date "+%Y/%m/%d %H:%M:%S"` by tayamamo         ###   ########.fr        #" >> Makefile
	@echo "#                                                                              #" >> Makefile
	@echo "# **************************************************************************** #" >> Makefile
	@echo '' >> Makefile
	@echo "# Makefile for philo_one, updated `date`" >> Makefile
	@echo '' >> Makefile
	@echo SRC := `ls *.c` >> Makefile
	@echo OBJ := `ls *.c | sed s/c$$/o/` >> Makefile
	@echo '' >> Makefile
	@echo HDR := `ls *.h` >> Makefile
	@echo '' >> Makefile
	@sed -n -e '/^# DO NOT ADD OR MODIFY/,$$p' < Makefile.bak >> Makefile

