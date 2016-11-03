flag = -Wall -Werror -ansi -pedantic

rshell:
	g++ $(flag) src/main.cpp -o bin/rshell
