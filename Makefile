default: 
	clang++ -c main.cpp
	clang++ -o ShapeFinder main.o

cover:
	./coverage.sh

test:
	./test.sh