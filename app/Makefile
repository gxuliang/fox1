#
#  "$Id: Makefile 17 2011-11-07 14:54:16Z xul $"
#
#  Copyright (c)1992-2007,  CO.LTD.
#  All Rights Reserved.
#
#	Description:	
#	Revisions:		Year-Month-Day  SVN-Author  Modification
#

GCC = g++

EXEC = app

SRC = ./src/
INC = ./inc/
COM_INC =
OBJ = ./obj/

LIBS =
		
		
OBJS = 	$(OBJ)webservice.o \
		$(OBJ)main.o	\
				
				
$(OBJ)%.o: $(SRC)/%.cpp
	$(GCC) -I$(INC) -c -o $(OBJ)$*.o $<
	
default:	$(OBJS)
	$(GCC) -O0 -o $(EXEC) $(OBJS) $(LIBS) -lpthread 
	
clean:
	rm -rf $(EXEC) $(OBJ)*.o