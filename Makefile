# Executable
NAME = webserv

# Compilation
CC = c++
COMPL_FLAGS = -Wall -Wextra -Werror -std=c++98
LINK_FLAGS =
# -g3 -fsanitize=address

COMPILE = $(CC) $(COMPL_FLAGS)
LINK = $(CC) $(LINK_FLAGS)

# Directories
CGI = CGI
SERV = server
PARS = parsing
OBJ_DIR = obj

# obj dirs
OBJ_DIRS = $(OBJ_DIR)/$(SERV) \
			$(OBJ_DIR)/$(PARS) \
			$(OBJ_DIR)/$(CGI)

# INC
INC_DIR = inc
INC_FILES = Configs.hpp Server.hpp stdIncludes.hpp typedefs.hpp
INC = $(addprefix $(INC_DIR)/, $(INC_FILES))

# Source Files
SERV_FILES = Config.cpp Server.cpp test.cpp
PARS_FILES = test.cpp
CGI_FILES = test.cpp

# SRC
SRC = main.cpp \
		$(addprefix $(SERV)/, $(SERV_FILES)) \
		$(addprefix $(PARS)/, $(PARS_FILES)) \
		$(addprefix $(CGI)/, $(CGI_FILES))

# OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(LINK) $(OBJ) -o $@
	@echo "[CREATING the legendary executable $@...]"

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)
	@echo "[CREATING object directories...]"

$(OBJ_DIR)/%.o: %.cpp $(INC) | $(OBJ_DIRS)
	@$(COMPILE) -c $< -o $@
	@echo "[COMPILING $<...]"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[CLEANING object files...]"

fclean: clean
	@rm -f $(NAME)
	@echo "[CLEANING the executable...]"

re: fclean all
