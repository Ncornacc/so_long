#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ncornacc <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/16 14:29:04 by ncornacc      #+#    #+#                  #
#    Updated: 2023/03/16 14:29:05 by ncornacc      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME	:=	so_long

LIBFT_D	:=	lib/libft
LIBMLX_D:=	lib/MLX42

LIBFT	:=	${LIBFT_D}/libft.a
LIBMLX	:=	${LIBMLX_D}/build/libmlx42.a

CC		:=	gcc
HEADER	:=	includes/so_long.h
HEAD	:= -I includes -I ${LIBFT_D}/include -I ${LIBMLX_D}/include
FLAGS	:=	-Wall -Werror -Wextra #-fsanitize=address -g

LFLAGS := -L${LIBMLX_D}/build -lmlx42 -L${LIBFT_D} -lft
ifeq ($(shell uname -s),Darwin)			# Mac
	LFLAGS := $(LFLAGS) -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(shell uname -s),Linux)		# Linux
	LFLAGS := $(LFLAGS) -lglfw -ldl -pthread -lm
endif

RM		:=	rm	-rf

##############################################################
#############################SOURCES##########################

OBJ_DIR	:=	obj/
SRC_DIR	:=	src/

FILE	:=	main free input initialization map_check map_drawing map_reading move

SRC		:=	${addprefix ${SRC_DIR}, ${addsuffix .c, ${FILE}}}
OBJ		:=	${addprefix ${OBJ_DIR}, ${addsuffix .o, ${FILE}}}

##############################################################
#############################COLORS###########################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m

##############################################################
#############################RULES############################

all: ${LIBMLX} ${LIBFT} ${NAME}

${LIBMLX}:
	cmake ${LIBMLX_D} -B ${LIBMLX_D}/build
	cmake --build ${LIBMLX_D}/build -j4

${LIBFT}:
	make -C ${LIBFT_D}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	@mkdir -p ${OBJ_DIR}
	@${CC} ${FLAGS} ${HEAD} -o $@ -c $< && printf "${YELLOW} Compiling: $(notdir $<) ${DEF_COLOR}"

${NAME}: ${OBJ}
	@${CC} ${FLAGS} ${HEAD} ${OBJ} ${LFLAGS} -o ${NAME}
	@echo "${GREEN} so_long compiled!${DEF_COLOR}"

clean:
	@make clean -C ${LIBFT_D}
	${RM} ${OBJ_DIR}
	${RM} ${LIBMLX_D}/build
	@echo "${MAGENTA} Object files cleaned!${DEF_COLOR}"

fclean: clean
	@make	fclean -C ${LIBFT_D}
	${RM}	${NAME} libft.a
	@echo  "${MAGENTA} executable/archive files cleaned!${DEF_COLOR}"

re:	fclean all
	@echo	"${GREEN} Cleaned and rebuild everything for so_long!${DEF_COLOR}:"

mem:
	memdetect.sh ${SRC} ${FLAGS} ${HEAD} ${LFLAGS} ${1}

.PHONY:	re, all, clean, fclean, libs, mem

##############################################################