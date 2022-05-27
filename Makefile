SRC = start_pars.c special_characters.c main.c built_stuct.c redirection.c \
utils.c utils_two.c legible_struct.c last_legible_struct.c utils_three.c

CC = gcc

HEADER = mini_shell.h

OBJ = $(SRC:%.c=./.build/%.o)

NAME = mini_shell

RM = rm -rf

LIBC = ar -rc

PRINTF = cd ./libft && make

CFLAGS = -Wall -Wextra -Werror
CFLAGS = 

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) ${CFLAGS} -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :	
	@mkdir -p .build
	@make ${NAME}

${NAME} : $(OBJ)
	${PRINTF}
	${CC} -o ${NAME} ${OBJ} -lreadline ./libft/libft.a
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

clean :
	@${RM} .build
	@cd ./libft && make clean
	@printf "${B_RED}XX{${NAME}} CLEANED SUCCESFULLY XX${NONE}\n"

fclean :	clean
	@${RM} ${NAME}
	@cd ./libft && make fclean
	@printf "${B_RED}XX{${NAME}} FCLEAN SUCCESFULL XX${NONE}\n"

re :	fclean all
