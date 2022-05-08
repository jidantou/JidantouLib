::@echo off
g++ -c .\fraction.cpp -o .\Output\fraction.o
g++ -c .\test.cpp -o .\Output\test.o

g++ -o .\Output\test.exe .\Output\test.o .\Output\fraction.o

.\Output\test.exe