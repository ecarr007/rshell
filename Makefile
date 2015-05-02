all: rshell ls

rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o bin/$@

ls:
	g++ -Wall -Werror -ansi -pedantic ./src/ls.cpp -o bin/$@

clean:
	rm -rf ./bin
