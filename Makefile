a.out: main.o validate.o add.o sub.o mul.o div.o functions.o
	gcc -o a.out main.o validate.o add.o sub.o mul.o div.o functions.o

main.o: main.c APC.h
	gcc -c main.c

validate.o: validate.c APC.h
	gcc -c validate.c

add.o: add.c APC.h
	gcc -c add.c

sub.o: sub.c APC.h
	gcc -c sub.c

mul.o: mul.c APC.h
	gcc -c mul.c

div.o: div.c APC.h
	gcc -c div.c

functions.o: functions.c APC.h
	gcc -c functions.c

clean:
	rm -f *.o a.out
