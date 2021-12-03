all : sort.o main.o
	gcc -o main sort.o main.o

sort.o : sort.c
	gcc -c -o sort.o sort.c
  
main.o : main.c
	gcc -c -o main.o main.c
  
clean : 
	rm *.o main

