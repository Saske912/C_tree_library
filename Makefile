NAME=libtree.a
SRC=init.c insert.c error.c
HEADER=tree.h
OBJ=$(SRC:.c=.o)

$(NAME):$(HEADER)
	gcc -c ${SRC}
	ar -rc ${NAME} ${OBJ}
	rm -f ${OBJ}

all:$(NAME)

clean:
	rm -f $(NAME)

re: clean all
