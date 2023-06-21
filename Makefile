NAME		= miniRT
BONUS		= miniRT_bonus

CC			= cc
CFLAGS		= #-Wall -Wextra -Werror

SRC_DIR		= sources/

SRC			= main.c paint.c key_hook.c vector_func.c ray.c raytracing.c \
				hit_obj.c light.c co.c vector_func2.c vector_func3.c\
				get_next_line.c get_next_line_utils.c ft_split.c \
				args.c utils.c utils_2.c ft_atoi.c ft_atof.c ft_atovec.c \
				cy.c pl.c sp.c

SRC_BONUS	= #bonus files

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
SRCS_BONUS	= $(addprefix $(SRC_DIR), $(SRC_BONUS))

OBJS_MAND	= $(SRCS:c=o)
OBJS_BONUS	= $(SRCS_BONUS:c=o)

INC			= -I./headers -Imlx
MLX			= -L./mlx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

bonus : $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INC) $(MXL) $^ -o $@

$(NAME): $(OBJS_MAND)
	$(CC) $(CFLAGS) $(INC) $(MLX) $^ -o $@

clean:
	rm -rf $(OBJS_MAND) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re
