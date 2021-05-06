# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 17:08:34 by tayamamo          #+#    #+#              #
#    Updated: 2021/05/06 17:08:34 by tayamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for philo_one, updated Thu May  6 17:08:34 JST 2021

SRC := ft_check_arg.c ft_check_int.c ft_free_.c ft_get_time_usec.c ft_init_mutex.c ft_putargs.c ft_set_args.c ft_set_forks.c ft_set_monitor.c ft_set_philos.c libft_ft_atoi.c libft_ft_bzero.c libft_ft_calloc.c libft_ft_isdigit.c libft_ft_isspace.c libft_ft_memset.c libft_ft_putchar_fd.c libft_ft_puterr_malloc.c libft_ft_putnbr_fd.c libft_ft_putstr_fd.c libft_ft_strlen.c main.c
OBJ := ft_check_arg.o ft_check_int.o ft_free_.o ft_get_time_usec.o ft_init_mutex.o ft_putargs.o ft_set_args.o ft_set_forks.o ft_set_monitor.o ft_set_philos.o libft_ft_atoi.o libft_ft_bzero.o libft_ft_calloc.o libft_ft_isdigit.o libft_ft_isspace.o libft_ft_memset.o libft_ft_putchar_fd.o libft_ft_puterr_malloc.o libft_ft_putnbr_fd.o libft_ft_putstr_fd.o libft_ft_strlen.o main.o

HDR := philo_one.h

# DO NOT ADD OR MODIFY ANY LINES ABOVE THIS -- run 'make source' to add files

NAME := philo_one

CC := gcc
CFLAGS := -Wall -Wextra -Werror
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

