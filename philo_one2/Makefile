# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/08 10:49:44 by tayamamo          #+#    #+#              #
#    Updated: 2021/05/08 10:49:44 by tayamamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for philo_one, updated Sat May  8 10:49:44 JST 2021

SRC := ft_check_arg.c ft_check_int.c ft_dining_philo.c ft_free_.c ft_monitor_philo.c ft_put_args.c ft_put_message.c ft_set_.c ft_time_.c libft_ft_atoi.c libft_ft_bzero.c libft_ft_calloc.c libft_ft_isdigit.c libft_ft_isspace.c libft_ft_memset.c libft_ft_putchar_fd.c libft_ft_puterr_malloc.c libft_ft_putnbr_fd.c libft_ft_putstr_fd.c libft_ft_strlen.c main.c
OBJ := ft_check_arg.o ft_check_int.o ft_dining_philo.o ft_free_.o ft_monitor_philo.o ft_put_args.o ft_put_message.o ft_set_.o ft_time_.o libft_ft_atoi.o libft_ft_bzero.o libft_ft_calloc.o libft_ft_isdigit.o libft_ft_isspace.o libft_ft_memset.o libft_ft_putchar_fd.o libft_ft_puterr_malloc.o libft_ft_putnbr_fd.o libft_ft_putstr_fd.o libft_ft_strlen.o main.o

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

