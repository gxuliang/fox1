#include ../CONFIG

GCC = $(CROSS)gcc
EXEC = post.cgi
SRC = ./src/
OBJ = ./obj/
INC	=./include/

LIBS = ./libs/libcgic.a
OBJS	=						\
		$(OBJ)main.o			\



$(OBJ)%.o: $(SRC)%.c
	$(GCC) -I$(INC) -g -c -o $(OBJ)$*.o $<

default:	$(OBJS)
	$(GCC) -O0 -o $(EXEC) $(OBJS) $(LIBS) -lpthread -lcrypt
	cp $(EXEC) ../web/cgi-bin/
clean:
	rm -rf $(EXEC) 
	rm -rf $(OBJ)*.o
