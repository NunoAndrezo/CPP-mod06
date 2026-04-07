#Name of the executable
NAME = Bureaucrat

#Compiler to use
CC = c++

#Flags the compiler will use
CFLAGS = -Wall -Wextra -Werror -std=c++98

#Directories for source, object and include files
SRC_DIR	=	src/
INC_DIR	=	inc/
OBJ_DIR	=	obj/

#Color codes for terminal output
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

#source and object files
SRC_FILES = main.cpp Bureaucrat.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

#full paths for source and object files
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

#Rule for building the executable
all: $(NAME)

#Compile the executable
$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#Building object files
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects...$(RESET)"; else \
	echo "No objects to remove."; \
	fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "$(BLUE)Deleting $(NAME)...$(RESET)"; else \
	echo "No Executable to remove."; \
	fi;

#re rule
re: fclean all
