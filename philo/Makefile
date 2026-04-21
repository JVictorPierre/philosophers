#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
NAME        	= philo
OBJS_PATH		= ./objs

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -pthread
INCLUDES    = -I ./includes
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~LIBRARY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
SRCS        = srcs/utils.c \
				srcs/init.c \
				srcs/exit.c \
				srcs/parsing.c \
				srcs/philo_routine.c \
				srcs/supervisor_routine.c \
				srcs/time_handling.c \
				srcs/main.c 

OBJS        = $(SRCS:srcs/%.c=$(OBJS_PATH)/%.o)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~DIRECTIVES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
all: $(NAME)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ philo successfully compiled!"

$(OBJS_PATH)/%.o: srcs/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<..."

$(OBJS_PATH)/%.o: srcs_bonus/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<..."
	
$(OBJS_PATH)/.bonus: $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
	@touch $@
	@echo "✅ philo bonus successfully compiled!"

clean:
	@rm -rf $(OBJS_PATH)
	@echo "✅ Object files successfully removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "✅ Executable and librairies successfuly removed!"

re: fclean all

.PHONY: all clean fclean re
