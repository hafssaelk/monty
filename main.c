#include "monty.h"
stack_t *head = NULL;

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	open_and_process_file(argv[1]);
	free_stack_nodes();
	return (0);
}

/**
 * create_stack_node - Creates a node for the stack.
 * @n: Number to be stored in the node.
 * Return: Upon success, returns a pointer to the new node. Otherwise, NULL.
 */
stack_t *create_stack_node(int n)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		custom_err_handler(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}

/**
 * free_stack_nodes - Frees nodes in the stack.
 */
void free_stack_nodes(void)
{
	stack_t *tmp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/**
 * add_node_to_queue - Adds a node to the queue.
 * @new_node: Pointer to the new node.
 * @ln: Line number of the opcode (unused).
 */
void add_node_to_queue(stack_t **new_node, __attribute__((unused)) unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *new_node;
	(*new_node)->prev = tmp;
}

