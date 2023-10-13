# Project compilation files and directories

NAME            =			program.run

C_HG        =  	main.c \
				utils.c

SRCSFD          =    
OBJSFD          =    obj/
HDR_INC         =    utils.h

OBJS_PHILOSOPHERS     =    $(addprefix $(OBJSFD), $(C_HG:.c=.o))
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Compilation
CFLAGS			=    -O3 -Wall -Wextra -Werror
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Colors
RED             = \033[0;31m
GREEN           = \033[0;32m
NONE            = \033[0m
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

all: project $(NAME)
	@echo "... project ready"

project:
	@echo "Checking project ..."

projectb:
	@echo "Checking project bonus ..."

$(OBJSFD):
	@mkdir $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(NAME): $(OBJSFD) $(OBJS_PHILOSOPHERS) $(OBJS_CLIENT)
	@gcc $(CFLAGS) $(OBJS_PHILOSOPHERS) -o $(NAME)
	@echo "\t[ $(GREEN)✔$(NONE) ] $(NAME) executable"

$(OBJSFD)%.o: $(SRCSFD)%.c
	@gcc $(CFLAGS) -c $< -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"


clean:
	@echo "Cleaning project ..."
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] Objects directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: project all clean fclean re
