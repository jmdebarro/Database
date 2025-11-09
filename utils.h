#include <stdio.h>
#include <errno.h>

#define EXIT_FAILURE 1

typedef struct {
	char *buffer;
	size_t bufferLength;
	size_t inputLength;
} InputBuffer;


InputBuffer *init_input_buffer() {
	InputBuffer *input_buffer = (InputBuffer *)malloc(size_of(InputBuffer));

	input_buffer->buffer = NULL;
	input_buffer->bufferLength = 0; 
	input_buffer->inputLength = 0; 

	return input_buffer;
}


void print_prompt() { printf("db > "); }


void read_input(InputBuffer *input_buffer) {
	ssize_t bytes_read;
	bytes_read = getline(
		&(input_buffer->buffer),
		&(input_buffer->bufferSize),
		stdin
	);

	if (bytes_read < 0) {
		printf("Unable to read from cmd line\n");
		perror("Error message: ");	
		exit(EXIT_FAILURE);
	}


	// To ignore the newline entered
	input_buffer->input_size = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}
