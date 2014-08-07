CROSS=arm-none-linux-gnueabi-
G++ = $(CROSS)g++
AR = $(CROSS)ar

SRC = src/lib_json/
OBJ = ./obj/
INC = -I./include
OBJS	=		\
		$(OBJ)json_reader.o			\
		$(OBJ)json_value.o			\
		$(OBJ)json_writer.o		\

$(OBJ)%.o: $(SRC)%.cpp
	$(G++) $(INC) -c -o $(OBJ)$*.o $<

default:	$(OBJS)
	$(AR) rc libjson.a $(OBJS)

clean:
	rm -rf ./obj/*
