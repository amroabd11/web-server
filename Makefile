# Executable
NAME = btc

# Compilation
CC = c++
COMPL_FLAGS = -Wall -Wextra -Werror -std=c++98
LINK_FLAGS = 
# -g -fsanitize=address

COMPILE = $(CC) $(COMPL_FLAGS)
LINK = $(CC) $(LINK_FLAGS)

# obj dirs
OBJ_DIR = obj
OBJ_DIRS = $(OBJ_DIR)

# INC
INC = std_includes.hpp  typedefs.hpp  webserv.hpp

# SRC
SRC = test.cpp

# OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(LINK) $(OBJ) -o $@
	@echo "[✅ BUILT $@]"

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)
	@echo "[📁 CREATING object directories]"

$(OBJ_DIR)/%.o: %.cpp $(INC) | $(OBJ_DIRS)
	@$(COMPILE) -c $< -o $@
	@echo "[🔧 COMPILING $<]"

clean:
	@rm -fr $(OBJ_DIR)
	@echo "[🧼 CLEANING the obj files]"

fclean: clean
	@rm -f $(NAME)
	@echo "[🧼 CLEANING the executable]"

re: fclean all
