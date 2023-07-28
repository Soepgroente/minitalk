NAME1	= client
NAME2	= server
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror -Ofast -flto #-fsanitize=address
LIBFT	= libft
OBJDIR	= Miniobjs

SRC1	= client.c
SRC2	= server.c

OBJS1	= $(SRC1:%.c=$(OBJDIR)/%.o)
OBJS2	= $(SRC2:%.c=$(OBJDIR)/%.o)

all: $(NAME1) $(NAME2)

$(LIBFT):
	git submodule init
	git submodule update

$(LIBFT)/$(LIBFT).a: $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME1): $(OBJDIR) $(OBJS1) $(LIBFT)/$(LIBFT).a 
	$(CC) $(CFLAGS) $(OBJS1) $(LIBFT)/$(LIBFT).a -o $(NAME1)

$(NAME2): $(OBJDIR) $(OBJS2) $(LIBFT)/$(LIBFT).a 
	$(CC) $(CFLAGS) $(OBJS2) $(LIBFT)/$(LIBFT).a -o $(NAME2)

clean:
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re