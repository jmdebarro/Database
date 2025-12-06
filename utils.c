#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Definitions for row data type
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct)*0)->Attribute)
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE =  size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

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
	EXECUTE_SUCCESS,
	EXECUTE_FAILURE
} ExecuteResult;

typedef enum {
	PREPARE_SUCCESS,
	PREPARE_UNRECOGNIZED_STATEMENT,
	PREPARE_SYNTAX_ERROR
} PrepareResult;

typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT
} StatementType;

typedef struct {
	uint32_t id;
	char username[COLUMN_USERNAME_SIZE]; 
	char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
	StatementType type;
	Row row_to_insert;
} Statement;

// Init table to store data
#define MAX_TABLE_PAGES 100
const uint32_t PAGE_SIZE = 4096;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t MAX_TABLE_ROWS = MAX_TABLE_PAGES / ROWS_PER_TABLE;

typedef struct {
	uint32_t num_rows;
	void *pages[TABLE_MAX_PAGES];	
} Table;

void *access_row(Table *table, uint32_t row_num) {
	if (row_num > num_rows) {
		printf("Requesting row # greater than number of rows");
		exit(EXIT_FAILURE);
	uint32_t page_num = row_num / ROW_PER_PAGE;
	void *page = table->pages[page_num];
	if (page == NULL) {
		page = table->pages[row_num] = malloc(PAGE_SIZE); 
	}
	uint32_t page_offset = row_num % ROWS_PER_PAGE;
	uint32_t byte_offset = page_offset * ROW_SIZE;
	return page + byte_offset;
}

void serialize_row(Row *source, void *destination) {
	memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
	memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
	memcpy(desintation + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination) {
	memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
	memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_OFFSET);
	memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}


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
		int args_assigned = sscanf(
			input_buffer->buffer,
			"insert %d %s %s",
			statement.row_to_insert.id,
			statement.row_to_insert.username,
			statement.row_to_inster.email
			)
		if (args_assigned < 3) {
			return PREPARE_SYNTAX_ERROR;
		}
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


