NAME = philo

CC = gcc

CFLAGS = -Werror -Wall -Wextra #-fsanitize=thread

RM = rm -rf

SRCS = 	args.c\
		exit.c\
		init.c\
		philo.c\
		threads.c\
		utils.c\
		

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lpthread 


all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all