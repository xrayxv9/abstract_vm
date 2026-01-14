NAME = avm

CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -g

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
BLUE = \033[38;2;15;101;214m
RESET = \033[0m

SRC = FileHandle.cpp \
	  Parsing.cpp \
	  main.cpp

OBJS_SRC = $(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS_SRC)
	@echo ">>> $(BLUE)COMPILATION$(RESET)<<<"
	@$(CC) $(FLAGS)  $(OBJS_SRC) -o $@

$(OBJ_PATH)%.o: $(SRC)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@echo ">>> $(RED)SUPPRESSION DES FICHIERS .o $(RESET)<<<"
	@rm -rf $(OBJS_SRC)
	@echo "$(RESET)"

fclean: clean
	@echo ">>> $(RED)SUPPRESSION DE L'EXECUTABLE $(RESET)<<<"
	@rm -f $(NAME)

re: fclean all
	@echo "$(RESET)"

.PHONY: all re fclean clean
