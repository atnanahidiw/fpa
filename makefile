all: clean fpa

fpa: main.o fpa.o
	g++ main.o fpa.o -o fpa

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

fpa.o: fpa.cpp
	g++ -std=c++11 -c fpa.cpp

clean:
	rm -rf *o fpa