CXX = clang++
CC = clang

main:
	clang++ -o main main.cpp
test: main
	./main
clean:
	rm -f *.o main	