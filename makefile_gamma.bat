@echo off
g++ -std=c++11 -c acak.cpp
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c gamma_test.cpp -o gamma_test.o
g++ acak.o objective.o fpa.o gamma_test.o -o gamma_test.exe
pause
