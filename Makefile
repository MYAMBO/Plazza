##
## EPITECH PROJECT, 2025
## B-ASM-400-LIL-4-1-asmminilibc-martin.bonte
## File description:
## Makefile
##

NAME        	= 	plazza
TEST        	= 	unit_tests
CC          	= 	g++

CFLAGS      	= 	-Wall -Wextra -Werror -Iinclude -std=c++20
DEBUG_FLAGS 	= 	-g
TEST_CFLAGS 	= 	--coverage -lcriterion

INCLUDE_FLAGS 	= 	-Isrc/Core									\
					-Isrc/Utils 								\
					-Isrc/Pizza 								\
					-Isrc/Kitchen 								\

SRC_TEST        = 												\

SRC		 		=	src/main.cpp 								\
																\
					src/Core/Core.cpp 							\
																\
					src/Utils/Utils.cpp 						\
																\
					src/Kitchen/Stock.cpp 						\
					src/Kitchen/Kitchen.cpp 					\
																\
					src/Pizza/APizza.cpp 						\
					src/Pizza/Regina/ReginaPizza.cpp 			\
					src/Pizza/Fantasia/FantasiaPizza.cpp 		\
					src/Pizza/Margarita/MargaritaPizza.cpp 		\
					src/Pizza/Americana/AmericanaPizza.cpp 		\

OBJ 			=	$(SRC:src/%.cpp=obj/%.o)

OBJ_TEST        = 	$(SRC_TEST:src/%.cpp=obj/%.o)

TEST_SRC    	= 	tests/test.cpp 								\

TEST_OBJ    	= 	$(TEST_SRC:test/%.cpp=obj/test/%.o)

RED         	= 	\033[1;31m
GREEN       	= 	\033[1;32m
BLUE        	= 	\033[1;34m
NC          	= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ_TEST) $(OBJ)
	@echo -e "$(BLUE)Linking binary...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(OBJ_TEST) $(OBJ) -o $(NAME)

obj/%.o: src/%.cpp | obj
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p `dirname $@`
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_FLAGS)

obj/test/%.o: test/%.cpp | obj/test
	@echo -e "$(GREEN)Compiling test $<...$(NC)"
	@$(CC) $(TEST_CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj obj/test obj/Components

unit_test: CFLAGS += --coverage
unit_test: $(OBJ_TEST) $(TEST_OBJ)
	@echo -e "$(BLUE)Compiling unit tests...$(NC)"
	@$(CC) $(TEST_CFLAGS) $(OBJ_TEST) $(TEST_OBJ) -o $(TEST) $(INCLUDE_FLAGS)

tests_run: unit_test
	@echo -e "$(BLUE)Running unit tests...$(NC)"
	@./$(TEST)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

clean:
	@if [ -d obj ]; then echo -e "$(RED)Cleaning objects.$(NC)"; fi
	@rm -rf obj
	@rm -f *.gcda *.gcno

fclean: clean
	@if [ -e "$(NAME)" ]; then echo -e "$(RED)Cleaning binary.$(NC)"; fi
	@rm -f $(NAME)
	@if [ -e "$(TEST)" ]; then echo -e "$(RED)Cleaning tests.$(NC)"; fi
	@rm -f $(TEST)

re: fclean all
