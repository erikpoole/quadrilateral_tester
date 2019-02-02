default: 
	clang++ -c main.cpp
	clang++ -o ShapeFinder main.o

fuzzer:
	cp fuzz.sh fuzz
	chmod +x fuzz

cover:
	./coverage.sh

test:
	./test.sh