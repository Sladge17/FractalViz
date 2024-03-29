NAME = fractol
FLAG = -Wall -Wextra -Werror

GL_DIR = minilibx_macos/
GL_FLAG = -lm -framework OpenGL -framework AppKit
GL = $(GL_DIR)libmlx.a $(GL_FLAG)

CL = -framework OpenCL

LIBFT_DIR = LibFT/
LIBFT = $(LIBFT_DIR)libft.a

HEADER_DIR = includes/
HEADER = -I $(HEADER_DIR)

SRC_DIR = src/
SRC_LIST = fractol.c\
			set_system.c\
			set_fractsett.c\
			calc_fractal.c\
			rgb_triangle.c\
			clearing.c\
			drawing.c\
			complex_axis.c\
			complex_actions1.c\
			complex_actions2.c\
			fractals1.c\
			fractals2.c\
			controls_main.c\
			controls_keyb_1.c\
			controls_keyb_2.c\
			controls_keyb_3.c\
			controls_mouse.c\
			shift_fractal.c\
			scale_fractal.c\
			write_stats.c\
			double_to_str.c\
			cl.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C $(LIBFT_DIR)
	@make re -C $(GL_DIR)
	@gcc -o $(NAME) $(HEADER) $(OBJ) $(LIBFT) $(GL) $(CL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(GL_DIR)

re: fclean all

.PHONY: all clean fclean re
