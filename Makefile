# コンパイラ設定
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# ターゲット: all, clean, fclean, re
NAME = get_next_line.a

# ソースファイルとオブジェクトファイル
SRC = main.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJ): get_next_line.h

.PHONY: all clean fclean re

$(MAIN): $(NAME) main.c
	$(CC) main.c -L. -lftprintf -o $(MAIN)
