@echo off
g++ -std=c++11 -c acak.cpp
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c main.cpp -o main.o
g++ acak.o objective.o fpa.o main.o -o fpa.exe
pause
