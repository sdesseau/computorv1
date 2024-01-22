CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

NAME = computorv1
SRC = main.cpp EquationSolver.cpp utils.cpp process.cpp
OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[0;32mCompilation successful! 🚀\033[0m"
	
test:
	@$(CXX) $(CXXFLAGS)  -o test tests.cpp EquationSolver.cpp utils.cpp process.cpp && ./test
	@echo "\033[0;32mRunning tests... ✔\033[0m"

%.o: %.cpp EquationSolver.hpp
	@$(CXX) $(CXXFLAGS) -c $<
	@echo "\033[0;32mCompiling $<... ✔\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[0;33mCleaning object files... ✔\033[0m"

fclean: clean
	@rm -f $(NAME) test
	@echo "\033[0;31mCleaning executable... ✔\033[0m"

re: fclean all


.PHONY: all clean fclean re test
