all: shell

shell: tarea4-201673070-2.o functions.o
	gcc -Wall -o shell tarea4-201673070-2.o functions.o

tarea4-201673070-2.o: tarea4-201673070-2.c functions.h
	gcc -Wall -c tarea4-201673070-2.c

functions.o: functions.c
	gcc -Wall -c functions.c

clean:
	rm *.o shell