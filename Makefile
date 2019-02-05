default: 
	clang++ -c -std=c++11 main.cpp
	clang++ -o ShapeFinder main.o

fuzzer:
	clang++ -g -fsanitize=address -c main.cpp
	clang++ -g -fsanitize=address -o ShapeFinder main.o
	cp fuzz.sh fuzz
	chmod +x fuzz

cover:
	./coverage.sh

test:
	./test.sh