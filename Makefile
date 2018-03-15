# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 11:09:29 by amathias          #+#    #+#              #
#    Updated: 2018/03/15 16:29:25 by apaget           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /

SRC =	start_nm.c	\
		get_what_i_need.c	\
		dd.c	\
		read_header.c \
		read_header2.c \
		endianr.c \
		endianr2.c \
		print.c \
		get_symbol.c \
		get_symb_list.c \
		read_lib2.c \
		read_lib3.c \
		read_lib.c


SRCO =	start_otool.c	\
		oread_header.c	\
		oread_lib.c \
		endianr.c \
		endianr2.c \
		oread_header2.c	\
		dd.c	\
		oread_header3.c	\
		get_what_i_need.c	\

OBJ = $(SRCI:.c=.o)
SRCI = $(SRC)

OBJO = $(SRCIO:.c=.o)
SRCIO = $(SRCO)

NAME = ft_nm
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -g 

LIB_PATH = ./libft/
LIB_NAME = -lft 
LIB = $(addprefix -L,$(LIB_PATH)) 
LFLAGS = $(LIB) $(LIB_NAME)

INC_PATH = ./libft/ /usr/local/include/ /usr/X11/lib ./
INC = $(addprefix -I,$(INC_PATH))

all: lib $(NAME) ft_otool

lib:
	@make -C ./libft


ft_otool: $(OBJO)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJO) -o $@
	@ echo "otool: \033[36mCreating\033[0m  binary"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $@
	@ echo "$(NAME): \033[36mCreating\033[0m  binary"

%.o: %.c
	@$(CC) $(INC) -o $@ -c $^ $(CFLAGS)
	@ echo "$(NAME): \033[34mCompiling\033[0m $<"

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJO)
	@make clean -C ./libft
	@ echo "$(NAME): \033[33mRemoving\033[0m  objects"

fclean: clean
	$(RM) $(NAME)
	$(RM) ft_otool
	@make fclean -C ./libft
	@ echo "$(NAME): \033[33mRemoving\033[0m  binary"

re: fclean all

