#include "monty.h"

/**
 * custom_err_handler - Prints custom error messages based on the error code.
 * @error_code: The error codes are as follows:
 * (1) => The user does not provide a file or provides more than one file to the program.
 * (2) => The provided file cannot be opened or read.
 * (3) => The file contains an unknown instruction.
 * (4) => Memory allocation (malloc) failure.
 * (5) => The parameter passed to the "push" instruction is not an integer.
 * (6) => The stack is empty for the "pint" operation.
 * (7) => The stack is empty for the "pop" operation.
 * (8) => The stack is too short for the specified operation.
 */
void custom_err_handler(int error_code, ...)
{
	va_list args;
	char *instruction;
	int line_number;

	va_start(args, error_code);
	switch (error_code)
	{
	case 1:
		fprintf(stderr, "USAGE: monty file\n");
		break;
	case 2:
		fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
		break;
	case 3:
		line_number = va_arg(args, int);
		instruction = va_arg(args, char *);
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, instruction);
		break;
	case 4:
		fprintf(stderr, "Error: Memory allocation (malloc) failed\n");
		break;
	case 5:
		fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
		break;
	default:
		break;
	}
	free_stack_nodes();
	exit(EXIT_FAILURE);
}

/**
 * custom_more_err_handler - Handles additional custom errors.
 * @error_code: The error codes are as follows:
 * (6) => The stack is empty for the "pint" operation.
 * (7) => The stack is empty for the "pop" operation.
 * (8) => The stack is too short for the specified operation.
 * (9) => Division by zero.
 */
void custom_more_err_handler(int error_code, ...)
{
	va_list args;
	char *operation;
	int line_number;

	va_start(args, error_code);
	switch (error_code)
	{
	case 6:
		fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
		break;
	case 7:
		fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
		break;
	case 8:
		line_number = va_arg(args, unsigned int);
		operation = va_arg(args, char *);
		fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, operation);
		break;
	case 9:
		fprintf(stderr, "Division by zero\n");
		break;
	default:
		break;
	}
	free_stack_nodes();
	exit(EXIT_FAILURE);
}

/**
 * custom_string_err_handler - Handles string-related custom errors.
 * @error_code: The error codes are as follows:
 * (10) ~> The number inside a node is outside ASCII bounds.
 * (11) ~> The stack is empty.
 */
void custom_string_err_handler(int error_code, ...)
{
	va_list args;
	int line_number;

	va_start(args, error_code);
	line_number = va_arg(args, int);
	switch (error_code)
	{
	case 10:
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		break;
	case 11:
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		break;
	default:
		break;
	}
	free_stack_nodes();
	exit(EXIT_FAILURE);
}

