ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME 	=	libft_malloc_$(HOSTTYPE).so
CC		=	clang
CFLAGS 	=	-Wall -Werror -Wextra
INC		=	-I includes/ -I ./libft/includes/
SRCS 	=	malloc.c\
			utils.c\
			realloc.c\
			show_alloc_mem.c\
			free.c

OBJ		=	$(SRCS:.c=.o)
HDRS	=	malloc.h

SDIR	=	$(addprefix srcs/, $(SRCS))
ODIR	=	$(addprefix objs/, $(OBJ))
HDIR	=	$(addprefix includes/, $(HDRS))
LIBPATH =	./libft
RED = \033[31;1m
GRN = \033[32;1m
YEL = \033[33;1m
BLU = \033[34;1m
MAG = \033[35;1m
CYN = \033[36;1m
WHT = \033[37;1m
EOC = \033[0m
BEER = \xF0\x9F\x8D\xBA

asan: CFLAGS += -fsanitize=address


all: $(NAME)

$(NAME): $(ODIR)
	@make -C $(LIBPATH)
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(ODIR) -L$(LIBPATH) -lft
	@/bin/rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo "$(GRN)$(BEER) $(NAME) created successfully!$(EOC)"

objs/%.o: srcs/%.c $(HDIR)
	@mkdir -p objs
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(GRN)$< =>$(EOC) $(YEL)$@$(EOC) $(GRN)✓$(EOC)"

clean:
	@/bin/rm -rf objs

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(RED)$(NAME) removed!$(EOC)"

reli:
	@make -C $(LIBPATH) re

re: fclean all

asan: all


.PHONY: re all clean fclean
