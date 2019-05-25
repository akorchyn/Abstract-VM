.PHONY: all re fcleam clean

NAME = avm

CC = $(HOME)/.brew/opt/llvm/bin/clang++

INCLUDES = -I $(HOME)/.brew/include

FLAGS = -Wall -Wextra -Werror -Ofast -std=c++17 -c

LIBS = -l c++fs 

Operations = Assert BinaryAnd BinaryOr BinaryXor Division Dump Exit Minus Modulo Multiply Plus Pop Print Push
Classes = AbstractRuntimeException IOperandGenerator Parser
FILE = $(addsuffix .cpp, $(addprefix src/, $(addprefix Classes/, $(Classes)) $(addprefix Operations/, $(Operations)) main))

OBJ_LIST = $(FILE:.cpp=.o)

all:$(NAME)

$(NAME): $(OBJ_LIST)
	@echo "\x1b[33mAVM linking\x1b[0m"
	@$(CC) $(OBJ_LIST) $(LIBS) -o $(NAME)
	@echo "\x1b[32mSuccessful\x1b[0m"

%.o: %.cpp
	@printf "\x1b[33mCompiling %s. \x1b[0m" $<
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ $<
	@echo "\x1b[32mDone.\x1b[0m"

clean:
	@/bin/rm -rf $(OBJ_LIST)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
