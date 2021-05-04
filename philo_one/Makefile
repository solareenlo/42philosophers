# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/05 02:53:11 by tayamamo          #+#    #+#              #
#    Updated: 2021/05/05 02:53:11 by tayamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for philo_one, updated Wed May  5 02:53:11 JST 2021

SRC := ft_atoi.c ft_check_arg.c ft_check_int.c ft_free_philo.c ft_get_time_usec.c ft_isdigit.c ft_isspace.c ft_putargs.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_set_args.c ft_set_philo.c ft_strlen.c main.c
OBJ := ft_atoi.o ft_check_arg.o ft_check_int.o ft_free_philo.o ft_get_time_usec.o ft_isdigit.o ft_isspace.o ft_putargs.o ft_putchar_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_set_args.o ft_set_philo.o ft_strlen.o main.o

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

.PHONY: clean
clean:
	$(RM) Makefile.bak $(OBJ_DIR)

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

