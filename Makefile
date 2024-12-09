all: server2

server2: main.o HTTP_Server.o Response.o
	gcc main.o HTTP_Server.o Response.o -o server2

main.o: main.c HTTP_Server.h Response.h
	gcc -c main.c

HTTP_Server.o: HTTP_Server.c HTTP_Server.h
	gcc -c HTTP_Server.c

Response.o: Response.c Response.h
	gcc -c Response.c

clean:
	rm -f *.o server2
