
CROSS = arm-none-linux-gnueabi-
G++ = $(CROSS)g++
AR = $(CROSS)ar

SRC = ./src/
OBJ = ./obj/
INC = -I./../jsoncpp-src-0.5.0/include/
OBJS	=		\
		$(OBJ)jsonrpc_client.o			\
		$(OBJ)jsonrpc_server.o			\
		$(OBJ)jsonrpc_udpclient.o		\
		$(OBJ)networking.o		\
		$(OBJ)jsonrpc_handler.o		\
		$(OBJ)jsonrpc_tcpserver.o		\
		$(OBJ)netstring.o		\
		$(OBJ)jsonrpc_tcpclient.o		\
		$(OBJ)jsonrpc_udpserver.o		\
		$(OBJ)system.o		\

$(OBJ)%.o: $(SRC)%.cpp
	$(G++) $(INC) -c -o $(OBJ)$*.o $<

default:	$(OBJS)
	$(AR) rc libjsonrpc.a $(OBJS)

clean:
	rm -rf ./obj/*
