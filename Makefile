all: rshell

rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o bin/$@
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o bin/$@
clean:
	rm -rf ./bin
