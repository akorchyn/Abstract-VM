.PHONY: all re fcleam clean create_dir

NAME = corewar

CC = $(HOME)/.brew/opt/llvm/bin/clang++

FLAGS = -Wall -Wextra -Werror -Ofast -std=c++17 -c

LIBFT = -lc++fs

Operations = Assert BinaryAnd BinaryOr BinaryXor Division Dump Exit Minus Modulo Multiply Plus Pop Print Push
Classes = AbstractRuntimeException IOperandGenerator Parser
FILE = $(addsuffix .cpp, $(addprefix src/, $(addprefix Classes/, $(Classes)) $(addprefix Operations/, $(Operations)) main))

OBJ_LIST = $(FILE:.cpp=.o)

all: create_dir $(NAME)

$(NAME): $(OBJ_LIST) $(LIBFT)
	@echo "\x1b[33mCorewar linking\x1b[0m"
	@$(CC) $(OBJ_LIST) $(LIBFT) -o $(NAME)
	@echo "\x1b[32mSuccessful\x1b[0m"

%.o: %.cpp
	@printf "\x1b[33mCompiling %s. \x1b[0m" $<
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ $<
	@echo "\x1b[32mDone.\x1b[0m"

clean:
	@make clean -C libft
	@/bin/rm -rf $(OBJ_LIST)

fclean: clean
	@/bin/rm -rf $(NAME) $(LIBFT)

re: fclean all
