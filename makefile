all: clean fpa

fpa: ziggurat.o acak.o objective.o fpa.o main.o
	g++ ziggurat.o acak.o objective.o fpa.o main.o -o fpa

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

fpa.o: fpa.cpp
	g++ -std=c++11 -c fpa.cpp

objective.o: objective.cpp
	g++ -c objective.cpp

acak.o: acak.cpp
	g++ -std=c++11 -c acak.cpp

ziggurat.o: ziggurat.cpp
	g++ -c ziggurat.cpp

clean:
	rm -rf *o fpa