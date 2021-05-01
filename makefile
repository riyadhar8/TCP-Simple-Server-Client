all: server client

server: ./Server/server.c 
		gcc ./Server/server.c -o server

client: ./Client/client.c
		gcc ./Client/client.c -o client

clean:
		rm -rf server client