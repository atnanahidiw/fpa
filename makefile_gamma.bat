@echo off
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c gamma_test.cpp -o gamma.o
g++ objective.o fpa.o gamma.o -o gamma.exe
pause
