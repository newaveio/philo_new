# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mathieu <mathieu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 15:33:52 by mbest             #+#    #+#              #
#    Updated: 2024/09/19 15:59:20 by mathieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END = \033[0m
_BOLD = \033[1m
_UNDER = \033[4m
_REV = \033[7m
_RED = \033[31m
_FOREST_GREEN = \033[32m
_DARK_BLUE = \033[34m
_YELLOW = \033[33m
_ORANGE = \033[38;5;208m
_PURPLE = \033[38;5;129m
_PINK = \033[38;5;218m
_CYAN = \033[36m
_GREY = \033[30m
_BROWN = \033[38;5;137m
_KAKI = \033[38;5;136m
_GOLD = \033[38;5;220m
_SILVER = \033[38;6;7m
_MAGENTA = \033[35;5m
_EMMERALD = \033[38;5;118m
_LILAC = \033[38;5;127m
_LAGOON = \033[38;5;120m
_AQUAMARINE = \033[38;5;122m
_CORAL = \033[38;5;201m
_RIVIERA = \033[38;5;32m
_SALMON = \033[38;5;209m

SRC_DIR = srcs/
OBJ_DIR = objs/

FILES = getter_setter.c \
		init.c \
		main.c \
		safe_functions.c \
		simulation.c \
		parsing.c \
		time_functions.c \
		utils.c

H_FILES = philo.h

SRCS = $(addprefix $(SRC_DIR),$(FILES))
OBJS = $(addprefix $(OBJ_DIR),$(FILES:.c=.o))

NAME = philo

CC = cc

# CFLAGS = -Wall -Wextra -Werror -pthread -g3
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g3

TOTAL_FILES := $(words $(SRCS))

COMPILED_FILES := 0

define compile_file
@printf "\e[?25l"
@mkdir -p $(OBJ_DIR)
@${CC} ${CFLAGS} -c $1 -o $2
@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
@for i in `seq 1 $$(( $(COMPILED_FILES)*20/$(TOTAL_FILES) ))`; do printf "⬜"; done
@for i in `seq $$(( $(COMPILED_FILES)*20/$(TOTAL_FILES)+1 )) 20`; do printf "⬛"; done
@printf "  Compiling %s... \r" $1
endef

$(OBJ_DIR)%.o : $(SRC_DIR)%.c srcs/philo.h
	$(call compile_file,$<,$@)

all: $(NAME)

$(NAME): $(OBJS) srcs/philo.h
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@echo "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ ✅$(BOLD) Philo successfully built!$(END)\n"
	@printf "\e[?25h"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "\n$(GREY)cleaning..\n$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREY)and cleaning again..\n$(END)"

push: fclean
	@git add .
	@git commit -m make
	@git push > /dev/null 2>&1
	@if [ $$? -eq 0 ]; then \
		echo "\n$(_FOREST_GREEN)$(_BOLD)          ,~-.\n         (  ' )-.          ,~'\`-.\n      ,~' \`  ' ) )       _(   _) )\n     ( ( .--.===.--.    (  \`    ' )\n      \`.%%.;::|888.#\`.   \`-'\`~~=~'\n      /%%/::::|8888\##\\n     |%%/:::::|88888\##|\n     |%%|:::::|88888|##|.,-.\n     \%%|:::::|88888|##/    )_\n      \%\:::::|88888/#/ ( \`'  )\n       \%\::::|8888/#/(  ,  -'\`-.\n   ,~-. \`%\:::|888/#'(  (     ') )\n  (  ) )_ \`\__|__/'   \`~-~=--~~='\n ( \` ')  ) [VVVVV]\n(_(_.~~~'   \|_|/      \n            [XXX]"; \
        echo "$(_FOREST_GREEN)$(_BOLD)\n  Travail terminé !  \n$(_END)"; \
    else \
        echo "$(_RED)$(_BOLD)\n  Git push failed!  \n$(_END)"; \
    fi

re: fclean all