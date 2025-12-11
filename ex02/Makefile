CPPFLAGS = c++ -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp \
	  PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)

NAME = PmergeMe
all: $(NAME)

$(NAME): $(OBJS)
	$(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CPPFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	rm -f $(NAME)
	
fclean: clean

re : fclean all
.PHONY: all clean fclean re