@echo off
g++ -c .\fraction.cpp -o .\Output\fraction.o
g++ -c .\test.cpp -o .\Output\test.o

g++ .\Output\fraction.o .\Output\test.o -o .\Output\test.exe

.\Output\test.exe