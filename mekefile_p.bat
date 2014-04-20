@echo off
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c p_test.cpp -o p_test.o
g++ objective.o fpa.o p_test.o -o p_test.exe
pause
