all: clean fpa

fpa: acak.o objective.o fpa.o main.o
	g++ acak.o objective.o fpa.o main.o -o fpa

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

fpa.o: fpa.cpp
	g++ -std=c++11 -c fpa.cpp

objective.o: objective.cpp
	g++ -c objective.cpp

acak.o: acak.cpp
	g++ -std=c++11 -c acak.cpp

clean:
	rm -rf *o fpa