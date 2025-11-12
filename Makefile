CC = gcc
CFLAGS = -Wall -Werror -g

database:
	$(CC) $(CFLAGS) database.c  utils.c -o database 

clean:
	rm database	

