all: server client

server:
	gcc -o server log.c server.c

client:
	gcc -o client log.c client.c

clean:
	rm -rf server client
