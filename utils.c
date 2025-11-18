#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *buffer;
	size_t bufferLength;
	size_t inputLength;
} InputBuffer;

typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

typedef enum {
	PREPARE_SUCCESS,
	PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT
} StatementType;

typedef struct {
	StatementType type;
} Statement;

void execute_statement(Statement *statement) {
	switch(statement->type) {
		case (STATEMENT_INSERT):
			printf("Insert logic\n");
			break;
		case (STATEMENT_SELECT):
			printf("Select logic\n");
			break;
	}
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement) {
	if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		return PREPARE_SUCCESS;
	}
	if (strcmp(input_buffer->buffer, "select") == 0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}


MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
	if (strcmp(input_buffer->buffer, ".exit") == 0) {
		exit(EXIT_SUCCESS);
	} else {
		return META_COMMAND_UNRECOGNIZED;
	}
}



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


