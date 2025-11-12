typedef struct {
	char *buffer;
	size_t bufferLength;
	size_t inputLength;
} InputBuffer;

InputBuffer *init_input_buffer(); 
void print_prompt(); 
void read_input(InputBuffer *input_buffer); 
int parse_command(InputBuffer *input_buffer); 
