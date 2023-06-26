NAME		= miniRT
BONUS		= miniRT_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= sources/

SRC			= main.c paint.c key_hook.c vector_func.c ray.c raytracing.c \
			  hit_obj.c light.c vector_func2.c vector_func3.c\
			  get_next_line.c get_next_line_utils.c ft_split.c \
			  args.c args_objs.c args_saving.c \
			  utils.c utils_2.c ft_atoi.c ft_atof.c ft_atovec.c \
			  cy.c pl.c sp.c co.c utils_3.c utils_4.c texture.c cy_uv.c

SRC_BONUS	= main_bonus.c paint.c key_hook.c vector_func.c ray.c raytracing.c \
			  hit_obj.c light.c co.c vector_func2.c vector_func3.c\
			  get_next_line.c get_next_line_utils.c ft_split.c \
			  args_bonus.c args_objs_bonus.c args_saving_bonus.c args_utils_bonus.c args_surface_bonus.c \
			  utils.c utils_2.c ft_atoi.c ft_atof.c ft_atovec.c \
			  cy.c pl.c sp.c utils_3.c utils_4.c texture.c cy_uv.c

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
SRCS_BONUS	= $(addprefix $(SRC_DIR), $(SRC_BONUS))

OBJS_MAND	= $(SRCS:c=o)
OBJS_BONUS	= $(SRCS_BONUS:c=o)

INC			= -I./headers -I./mlx
MLX			= -L./mlx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

bonus : $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INC) $(MLX) $^ -o $@

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
