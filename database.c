#include <stdio.h>
#include "utils.h"


int main(void) {
	InputBuffer *input_buffer;
	input_buffer = init_input_buffer();

	while(1) {
		read_input(input_buffer);
		parse_command(input_buffer);	
	}		
	return 0;
}
