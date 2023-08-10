NAME1	= client
NAME2	= server
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror #-g3 -fsanitize=address
LIBFT	= libft
OBJDIR	= Miniobjs

SRC1	= client.c
SRC2	= server.c

OBJS1	= $(SRC1:%.c=$(OBJDIR)/%.o)
OBJS2	= $(SRC2:%.c=$(OBJDIR)/%.o)

all: build_lib $(NAME1) $(NAME2)

build_lib: $(LIBFT)/Makefile
	$(MAKE) -C $(LIBFT)

$(LIBFT)/Makefile:
	git submodule init
	git submodule update

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME1): $(OBJDIR) $(OBJS1)
	$(CC) $(CFLAGS) $(LIBFT)/$(LIBFT).a $(OBJS1) -o $(NAME1)

$(NAME2): $(OBJDIR) $(OBJS2)
	$(CC) $(CFLAGS) $(LIBFT)/$(LIBFT).a $(OBJS2) -o $(NAME2)

clean:
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re, build_lib