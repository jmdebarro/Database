typedef struct {
	char *buffer;
	size_t bufferLength;
	size_t inputLength;
} InputBuffer;

typedef enum{
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

InputBuffer *init_input_buffer(); 
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement); 
InputBuffer *init_input_buffer(); 
void print_prompt(); 
void read_input(InputBuffer *input_buffer); 
void execute_statement(Statement *statement); 
MetaCommandResult do_meta_command(InputBuffer *input_buffer); 
