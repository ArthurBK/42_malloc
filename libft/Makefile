# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonneca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 09:59:58 by abonneca          #+#    #+#              #
#    Updated: 2017/04/26 19:21:32 by abonneca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang -g

FLAGS=-Wall -Wextra -Werror

NAME=libft.a

SOURCES=	ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strlen.c\
		ft_strdup.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strcat.c\
		ft_strncat.c\
		ft_strlcat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strstr.c\
		ft_strnstr.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_memalloc.c\
		ft_memdel.c\
		ft_strnew.c\
		ft_strdel.c\
		ft_strclr.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strequ.c\
		ft_strnequ.c\
		ft_strsub.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_strsplit.c\
		ft_itoa.c\
		ft_putchar.c\
		ft_putstr.c\
		ft_putendl.c\
		ft_putnbr.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_lstnew.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstadd.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_count_words.c\
		ft_print_words_tables.c\
		ft_is_prime.c\
		ft_swap.c\
		ft_strrev.c\
		ft_sort_int_tab.c\
		ft_pgcd.c\
		ft_list_size.c\
		get_next_line.c\

INCLUDES = ./includes/libft.h

OBJECTS = $(notdir $(SOURCES:.c=.o))

vpath %.c ./srcs

all: $(NAME)
	@echo > /dev/null

$(NAME): $(OBJECTS)
	@ printf "\33[2K"
	@ printf "Creating library => "
	@ if ar rc $(NAME) $(OBJECTS) ; \
		then printf "✅\n"; \
		else printf "❌\n"; fi
	@ ranlib $(NAME)
	@ echo "Finished"

%.o: %.c $(INCLUDES)
	@ printf "\x1B[35m"
	@ printf "Compiling: $< ..."
	@ $(CC) -o $@ -c $(CFLAGS) $< $(addprefix -I ,$(sort $(dir $(INCLUDES))))
	@ printf "\r"

clean:
	@ echo "Deleting object files"
	@ rm -f $(OBJECTS)

fclean: clean
	@ echo "Deleting $(NAME)"
	@ rm -f $(NAME)

re: fclean all
