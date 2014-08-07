

GCC = $(CROSS)gcc
EXEC = dbgmsg
INC	=./inc/
SRC = ./src/

LIBS = 
OBJS	=						\
		$(OBJ)main.o			\



$(OBJ)%.o: $(SRC)%.c
	$(GCC) -I$(INC) -g -c -o $(OBJ)$*.o $<

default:	$(OBJS)
	$(GCC) -O0 -o $(EXEC) $(OBJS) $(LIBS) -lpthread
	#cp $(EXEC) ../../../lion/cgi-bin/
clean:
	rm -rf $(EXEC) 
	rm -rf $(OBJ)*.o
