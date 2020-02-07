

all: md5.o exo3.o
	g++ -std=c++17 -o exec exo3.o md5.o

md5.o:	md5.cpp
	g++ -std=c++17 -O3 -c md5.cpp

exo3.o:	exo3.cpp
	g++ -std=c++17 -O3 -c exo3.cpp