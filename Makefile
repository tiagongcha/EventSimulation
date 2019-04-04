simulate: simulate.o main.o
	clang++ -c main.cpp
	clang++ -c simulate.cpp
	clang++ -o simulate simulate.o main.o





