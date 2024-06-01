#CXXFLAGS = -Wall -Wextra -pedantic-errors -g -std=c++17
CXXFLAGS = -Wall -Wextra -pedantic-errors -O3 -std=c++17

all:
	g++ $(CXXFLAGS) main.cpp -o main -lproj -lX11
#	g++ $(CXXFLAGS) -c -S main.cpp -lproj

clean:
	rm -f main
	rm -f *.o
