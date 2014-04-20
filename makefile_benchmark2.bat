@echo off
g++ -c objective.cpp -o objective.o
g++ -std=c++11 -c fpa.cpp -o fpa.o
g++ -std=c++11 -c benchmark.cpp -o benchmark.o
g++ objective.o fpa.o benchmark.o -o benchmark2.exe
pause
