proj2.x: test_list.cpp
	g++ -Wall -pedantic -std=c++11 -g -o proj2.x test_list.cpp

clean:
	rm -f *.o *.x core.*

