NAME = fractol
FLAG = -Wall -Wextra -Werror

GL_DIR = ./minilibx_macos/
GL_FLAG = -lm -framework OpenGL -framework AppKit
GL = $(GL_DIR)libmlx.a $(GL_FLAG)

# LIBFT_DIR = ./libft/
# LIBFT = $(LIBFT_DIR)libft.a

HEADER_DIR = includes/
HEADER = -I $(HEADER_DIR)

SRC_DIR = src/
SRC_LIST = fractol.c\
			complex_actions.c\
			controls_main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
# 	@make re -C $(LIBFT_DIR)
# 	@gcc -o $(NAME) $(HEADER) $(OBJ) $(LIBFT) $(GL)
	@gcc -o $(NAME) $(HEADER) $(OBJ) $(GL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
# 	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
# 	@make fclean -C $(LlsIBFT_DIR)

re: fclean all
