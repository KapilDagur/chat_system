CC=gcc
CFLAGS=-Wall -I./deps/sqlite3 -I./deps/openssl
LDFLAGS=-lsqlite3 -lssl -lcrypto -lpthread

SERVER_SRC=$(wildcard src/server/*.c)
CLIENT_SRC=$(wildcard src/client/*.c)

all: server client

server: $(SERVER_SRC)
	$(CC) $(CFLAGS) -o bin/server $^ $(LDFLAGS)

client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o bin/client $^ $(LDFLAGS)

clean:
	rm -f bin/server bin/client
