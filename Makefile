build-run:
	gcc database.c -o database -Wextra -Wall && ./database

build:
	gcc database.c -o database -Wextra -Wall

run:
	./database	


