default: 
	clang++ -c main.cpp
	clang++ -o ShapeFinder main.o

test:
	./ShapeFinder < input.txt > output.txt
	diff key.txt output.txt