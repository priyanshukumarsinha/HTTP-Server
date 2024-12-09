all: server2

server2: main.o HTTP_Server.o Response.o Routes.o
	gcc main.o HTTP_Server.o Response.o Routes.o -o server2

main.o: main.c HTTP_Server.h Response.h Routes.h
	gcc -c main.c

HTTP_Server.o: HTTP_Server.c HTTP_Server.h Routes.h
	gcc -c HTTP_Server.c

Response.o: Response.c Response.h Routes.h
	gcc -c Response.c

Routes.o: Routes.c Routes.h
	gcc -c Routes.c

clean:
	rm -f *.o server2
