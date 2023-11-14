#include "monty.h"

/**
 * open_and_process_file - Opens a file and processes its content.
 * @file_name: The file name/path to be opened.
 * Return: void
 */
void open_and_process_file(char *file_name)
{
	FILE *file_descriptor = fopen(file_name, "r");

	if (file_name == NULL || file_descriptor == NULL)
		custom_err_handler(2, file_name);

	read_file(file_descriptor);
	fclose(file_descriptor);
}

/**
 * read_file - Reads a file and processes each line.
 * @file_descriptor: Pointer to the file descriptor.
 * Return: void
 */
void read_file(FILE *file_descriptor)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, file_descriptor) != -1; line_number++)
	{
		format = parse_line(buffer, line_number, format);
	}
	free(buffer);
}

/**
 * parse_line - Separates each line into tokens to determine
 * which function to call.
 * @buffer: Line from the file.
 * @line_number: Line number.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 *           If 1, nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is "stack", 1 if "queue".
 */
int parse_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		custom_err_handler(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_function(opcode, value, line_number, format);
	return (format);
}

/**
 * find_function - Finds the appropriate function for the opcode.
 * @opcode: Opcode.
 * @value: Argument of the opcode.
 * @line_number: Line number.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 *           If 1, nodes will be entered as a queue.
 * Return: void
 */
void find_function(char *opcode, char *value, int line_number, int format)
{
	int i;
	int flag;

	instruction_t function_list[] = {
		{"push", push_to_stack},
		{"pall", print_stack_nodes},
		{"pint", print_top_of_stack},
		{"pop", pop_from_stack},
		{"nop", do_nothing},
		{"swap", swap_stack_nodes},
		{"add", add_stack_nodes},
		{"sub", sub_stack_nodes},
		{"div", div_stack_nodes},
		{"mul", multiply_stack_nodes},
		{"mod", modulo_stack_nodes},
		{"pchar", print_character},
		{"pstr", print_string},
		{"rotl", rotate_left},
		{"rotr", rotate_right},
		{NULL, NULL}};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; function_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, function_list[i].opcode) == 0)
		{
			call_function(function_list[i].f, opcode, value, line_number, format);
			flag = 0;
		}
	}
	if (flag == 1)
		custom_err_handler(3, line_number, opcode);
}

/**
 * call_function - Calls the required function.
 * @function: Pointer to the function that is about to be called.
 * @opcode: String representing the opcode.
 * @value: String representing a numeric value.
 * @line_number: Line number for the instruction.
 * @format: Format specifier. If 0, nodes will be entered as a stack.
 *          If 1, nodes will be entered as a queue.
 * Return: void
 */
void call_function(op_func function, char *opcode, char *value, int line_number, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(opcode, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value = value + 1;
			flag = -1;
		}
		if (value == NULL)
			custom_err_handler(5, line_number);
		for (i = 0; value[i] != '\0'; i++)
		{
			if (isdigit(value[i]) == 0)
				custom_err_handler(5, line_number);
		}
		node = create_stack_node(atoi(value) * flag);
		if (format == 0)
			function(&node, line_number);
		if (format == 1)
			add_node_to_queue(&node, line_number);
	}
	else
		function(&head, line_number);
}

