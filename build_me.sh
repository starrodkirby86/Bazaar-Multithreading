#!/bin/bash
echo "Building the program..."
g++ -c bazaar.cpp -std=c++11
g++ -c person.cpp -std=c++11
g++ -c rng.cpp -std=c++11
g++ -c main.cpp -std=c++11 -lpthread
g++ -o bazaarTest bazaar.o person.o rng.o main.o -lpthread
./bazaarTest