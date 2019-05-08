NAME = ft_ls

CFILES = main.c

FLAGS = -Wall -Werror -Wextra 

OBJS = *.o

all: $(NAME)

$(NAME):
	@echo "\033[32mCompiling files . . .\033[0m"
	@gcc $(FLAGS) -c $(CFILES) 
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@echo "\033[32mCleaning .\033[0m"
	@rm -rf $(OBJS)

fclean: clean
	@echo "\033[32mClean more . .\033[0m"
	@rm -rf $(NAME)
	@rm -rf $(EX)

re: fclean all