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
SERV = server
PARS = parsing
OBJ_DIR = obj

# obj dirs
OBJ_DIRS = $(OBJ_DIR)/$(SERV) \
			$(OBJ_DIR)/$(PARS) \

# INC
INC_DIR = inc
INC_FILES = Configs.hpp Server.hpp stdIncludes.hpp typedefs.hpp   SyntaxError.hpp Parser.hpp ReqTokenizer.hpp
INC = $(addprefix $(INC_DIR)/, $(INC_FILES))

# Source Files
SERV_FILES =  HTTP_Req.cpp Server.cpp VirtualServer.cpp  CGI.cpp
PARS_FILES =  SyntaxError.cpp Config.cpp Parser.cpp ReqTokenizer.cpp   

# SRC
SRC = main.cpp \
		$(addprefix $(SERV)/, $(SERV_FILES)) \
		$(addprefix $(PARS)/, $(PARS_FILES)) \

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
