# Variables
CC = clang
CFLAGS = -Wall -Wextra -g
CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_OBJ = client.o
SERVER_OBJ = server.o
CLIENT_EXEC = client
SERVER_EXEC = server

# Default target
all: $(CLIENT_EXEC) $(SERVER_EXEC)

# Compile the client executable
$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC)

# Compile the server executable
$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC)

# Clean up object files and executables
clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT_EXEC) $(SERVER_EXEC)

# Phony targets
.PHONY: all clean
