all: avva avva.100

avva: avva.c++
	g++ -Wall -Werror -O3 -march=native avva.c++ -o avva

avva.100: avva.c++
	g++ -Wall -Werror -O3 -march=native avva.c++ -DONLY_100 -o avva.100

clean:
	rm -f avva avva.100
