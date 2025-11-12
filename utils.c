#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *buffer;
	size_t bufferLength;
	size_t inputLength;
} InputBuffer;


InputBuffer *init_input_buffer() {
	InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));

	input_buffer->buffer = NULL;
	input_buffer->bufferLength = 0; 
	input_buffer->inputLength = 0; 

	return input_buffer;
}


void print_prompt() { printf("db > "); }


// Command line program
void read_input(InputBuffer *input_buffer) {
	ssize_t bytes_read;
	print_prompt();
	bytes_read = getline(
		&(input_buffer->buffer),
		&(input_buffer->inputLength),
		stdin
	);

	if (bytes_read < 0) {
		printf("Unable to read from cmd line\n");
		perror("Error message: ");	
		exit(EXIT_FAILURE);
	}

	// To ignore the newline entered
	input_buffer->inputLength = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}

// Frees the input buffer memory
void close_input_buffer(InputBuffer *input_buffer) {
	free(input_buffer->buffer);
	free(input_buffer);
}


// Parse command
int parse_command(InputBuffer *input_buffer) {
	const char *command = ".exit";
	if (strcmp(input_buffer->buffer, command) == 0) {
		close_input_buffer(input_buffer);
		exit(EXIT_SUCCESS);
	} else {
		printf("Unrecognized command: %s\n", input_buffer->buffer);
	}	
	return 0;
}



