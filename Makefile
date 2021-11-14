CC		= gcc
#CFLAGS	= -Wall -Wextra
NAME	= pinchBlue
FLAGS	= 
INCLUDE	= -lbluetooth
SRC		= pinchBlue_main.c pinchBlue_adapter.c pinchBlue_plist.c pinchBlue_sniffer
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
