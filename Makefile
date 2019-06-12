NAME = ft_ls

CFILES = main.c flags.c directory.c dir.c sort_files.c printfiles.c freefiles.c extra.c help_files.c

FLAGS = -Wall -Werror -Wextra 

GCC = gcc

LIBFT = final-libft

all: $(NAME)

$(NAME):
	@echo "\033[32mCompiling files . . .\033[0m"
	@make -C $(LIBFT)
	$(GCC) $(FLAGS) $(CFILES) -L $(LIBFT) -lft -o $(NAME)

clean:
	@echo "\033[32mCleaning .\033[0m"
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@echo "\033[32mClean more . .\033[0m"
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re
