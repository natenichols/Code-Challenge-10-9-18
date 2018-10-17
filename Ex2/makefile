Ex: main.o 
	g++ -g -std=c++11 -Wall main.o -lpthread -o Ex

main.o: main.cpp lock_guard.h
	g++ -g -std=c++11 -Wall -c -lpthread main.cpp 

clean:
	rm *.o Ex1
