refactor:
	clang++ -c -std=c++17 main.cpp bank.cpp market.cpp
	clang++ -o RefactoredDES main.o bank.cpp market.cpp

simulate: simulate.o main.o
	clang++ -c main.cpp
	clang++ -c simulate.cpp
	clang++ -o simulate simulate.o main.o
clean:
	rm -f main.o bank.o market.o RefactoredDES




