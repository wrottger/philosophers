NAME	= philosophers

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -ofast

SRC_PATH	=	src/
SRC		=	actions.c \
			arguments.c \
			cleanup.c \
			ft_atoi.c \
			initialization.c \
			main.c \
			monitoring.c \
			mutexes.c \
			philosopher.c \
			philosophers.c \
			printing.c \
			time.c 

SRCS	= $(addprefix $(SRC_PATH), $(SRV_SRC))

OBJ_PATH	= obj/
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INCLUDES	= -I./includes

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread $(INCLUDES)
	@echo "$(NAME) ready"

bonus: all

clean:
	@rm -rf $(OBJS) $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean bonus