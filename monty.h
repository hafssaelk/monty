#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;

typedef void (*op_func)(stack_t **, unsigned int);

/* File operations */
void open_and_process_file(char *file_name);
int parse_line(char *buffer, int line_number, int format);
void read_file(FILE *file);
int len_chars(FILE *file);
void find_function(char *opcode, char *value, int line_number, int format);

/* Stack operations */
stack_t *create_stack_node(int value);
void free_stack_nodes(void);
void print_stack_nodes(stack_t **stack, unsigned int line_number);
void push_to_stack(stack_t **stack, unsigned int line_number);
void add_node_to_queue(stack_t **stack, unsigned int line_number);

void call_function(op_func function, char *opcode, char *value, int line_number, int format);

void print_top_of_stack(stack_t **stack, unsigned int line_number);
void pop_from_stack(stack_t **stack, unsigned int line_number);
void do_nothing(stack_t **stack, unsigned int line_number);
void swap_stack_nodes(stack_t **stack, unsigned int line_number);

/* Math operations with nodes */
void add_stack_nodes(stack_t **stack, unsigned int line_number);
void sub_stack_nodes(stack_t **stack, unsigned int line_number);
void div_stack_nodes(stack_t **stack, unsigned int line_number);
void multiply_stack_nodes(stack_t **stack, unsigned int line_number);
void modulo_stack_nodes(stack_t **stack, unsigned int line_number);

/* String operations */
void print_character(stack_t **stack, unsigned int line_number);
void print_string(stack_t **stack, unsigned int line_number);
void rotate_left(stack_t **stack, unsigned int line_number);

/* Error handling */
void custom_err_handler(int error_code, ...);
void custom_more_err_handler(int error_code, ...);
void custom_string_err_handler(int error_code, ...);
void rotate_right(stack_t **stack, unsigned int line_number);

#endif /* MONTY_H */
