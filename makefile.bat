@echo off
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c main.cpp -o main.o
g++ main.o fpa.o objective.o -o fpa.exe
pause
