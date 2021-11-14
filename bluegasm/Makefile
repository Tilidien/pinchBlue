CC		= gcc
#CFLAGS	= -Wall -Wextra
NAME	= simplescan
FLAGS	= 
INCLUDE	= -lbluetooth
SRC		= bluegasm.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
