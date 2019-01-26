default: 
	clang++ -c main.cpp
	clang++ -o ShapeFinder main.o

test:
	./test.sh