NAME=libtree.a
SRC=init.c insert.c compare_values.c
HEADER=tree.h
OBJ=$(SRC:.c=.o)

$(NAME):$(HEADER)
	gcc -c ${SRC}
	ar -rc ${NAME} ${OBJ}
	rm -f ${OBJ}
