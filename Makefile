all: rshell

rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o bin/$@
cp:
	g++ -Wall -Werror -ansi -pedantic ./src/cp.cpp -o bin/$@

rm:
	g++ -Wall -Werror -ansi -pedantic ./src/rm.cpp -o bin/$@
mv:
	g++ -Wall -Werror -ansi -pedantic ./src/mv.cpp -o bin/$@
clean:
	rm -rf ./bin
