all: clean fpa

fpa: main.o fpa.o objective.o
	g++ main.o fpa.o objective.o -o fpa

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

fpa.o: fpa.cpp
	g++ -std=c++11 -c fpa.cpp

objective.o: objective.cpp
	g++ -c objective.cpp

clean:
	rm -rf *o fpa