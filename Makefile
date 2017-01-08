CC=g++
CFLAGS="-std=c++11"

convertor: main.cpp
	$(CC) $(CFLAGS) main.cpp -o convertor
run: convertor
	./convertor
