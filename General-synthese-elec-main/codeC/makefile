cwire : main.o station.o csvfile.o avl.o
	gcc -o cwire main.o station.o csvfile.o avl.o
	
main.o : src/main.c
	gcc -c src/main.c -o main.o
	
station.o : src/station.c
	gcc -c src/station.c -o station.o

csvfile.o : src/csvfile.c
	gcc -c src/csvfile.c -o csvfile.o
	
avl.o : src/avl.c
	gcc -c src/avl.c -o avl.o