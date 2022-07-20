/* Modify the singly linked list to be a doubly linked list. 
Now write a routine that removes all duplicate data in the doubly linked list. 
The data will be integers generated at random from [0,49]. Initially have a list of 200 elements.  
Now do this in one of two ways.  
Sort the list by its data field. Remove adjacent elements of the sorted list with the same value. Or 
take the first element—search the remainder of the list for elements with the same data and remove them. 
Then take the second element and do the same. Repeat until only one element is left.*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_ELEMENTS 200       // Before removing duplicates, the list has 200 elements.
#define RAND_RANGE 50

// A helper enum mainly used for the verification functions (verify_is_sorted, verify_no_duplicates).
typedef enum { FALSE, TRUE } bool;

// Define the doubly-linked list ADT 
struct List 
{
	int data;
	struct List *next, *previous;
};

// Print a doubly-linked list, from beginning to end
void print_list (struct List *list) 
{
	for (; list != NULL; list = list->next) 
	{
		printf("%d ", list->data);
	}

	printf("\n");
}

// Add an element to the front of the list.
struct List *push_front (struct List *list, int data) 
{
	struct List *new_node = malloc(sizeof(*new_node));

	new_node->previous = NULL;
	new_node->next = list;
	new_node->data = data;

	if (list != NULL) 
	{ 		
		list->previous = new_node;     // Not the first insertion 
	}

	return new_node;
}
/* Return the data contained in the head of the list.  To make the duplicate-detection code cleaner 
later on, this function returns a pointer to the relevant int value, 
so that it can signal NULL if 'list' is NULL. */

int *peek (struct List *list) 
{
	if (list == NULL) 
	{
		return NULL;
	} 
	else 
	{
		int *value = malloc(sizeof(int));
		*value = list->data;
		return value;
	}
}
// Remove the front of the list.
struct List *pop_front (struct List *list) 
{
	struct List *rest = NULL;

	if (list == NULL) 
	{
		return NULL;
	}

	rest = list->next;

	if (rest != NULL) 
	{
		rest->previous = NULL;
		list->next = NULL;
	}

	free(list);
	return rest;
}
// Helper function for bubble sort. 
// Note that this function only swaps the data, not the actual nodes. 

void swap (struct List *node_1, struct List *node_2) 
{
	int tmp = node_1->data;

	node_1->data = node_2->data;
	node_2->data = tmp;
}

// Bubble-sort routine used for sorting the initial list of 200 elements.
struct List *sort (struct List *list) 
{
	int i, limit;
	struct List *ptr;

	// 'limit' is the position of the first element of the sorted region.
	limit = NUM_ELEMENTS - 1;

	while (limit >= 0) 
	{
		for (i = 0, ptr = list; i < limit; i++, ptr = ptr->next) 
		{
			if (ptr->data > ptr->next->data) 
			{
				swap(ptr, ptr->next);
			}
		}

		limit--;
	}

	return list;
}
// Make 'next' point to 'previous' referent, and vice-versa. 
// A helper function for essentially reversing a doubly-linked list.
void swap_references (struct List* list) 
{
	struct List *tmp = list->next;
	list->next = list->previous;
	list->previous = tmp;
}

// Reverse a list. The list should at least have one element. 
struct List *reverse (struct List *list) 
{
	assert(list->next != NULL);

	do 
	{
		swap_references(list);

		if (list->previous == NULL) 
		{
			break;
		}

		list = list->previous;
	} while (1);

	return list;
}
// Remove duplicates from a _sorted_ doubly-linked list, as defined by our program. 
// 'list' starts out with a size of NUM_ELEMENTS.
struct List *remove_duplicates (struct List *list) 
{
	struct List *new_list = NULL;

	for (; list != NULL; list = list->next) 
	{
		int *front = peek(new_list);

		if (front == NULL || *front != list->data) 
		{
			new_list = push_front(new_list, list->data);
		}

		free(front);
	}

	new_list = reverse(new_list);

	return new_list;
}
// Verify that a list is sorted. 
bool verify_is_sorted (struct List *list) 
{
	if (list == NULL || list->next == NULL) 
	{
		return TRUE;
	}

	for (; list->next != NULL; list = list->next) 
	{
		if (list->data > list->next->data) 
		{
			return FALSE;
		}
	}

	return TRUE;
}


// Verify that a sorted list has no duplicates.
bool verify_no_duplicates (struct List *list) 
{
	if (list == NULL || list->next == NULL) 
	{
		return TRUE;
	}

	for (; list->next != NULL; list = list->next) 
	{
		if (list->data == list->next->data) 
		{
			return FALSE;
		}
	}

	return TRUE;
}
int main (void) 
{
	struct List *list = NULL;
	int i;

	srand(time(NULL));

	for (i = 0; i < NUM_ELEMENTS; i++) 
	{
		list = push_front(list, rand() % RAND_RANGE);
	}

	printf("\nThe original list:\n");
	print_list(list);

	printf("\nThe sorted list, with duplicates:\n");
	list = sort(list);
	assert(verify_is_sorted(list));
	print_list(list);

	printf("\nThe same sorted list, with any duplicates removed:\n");
	list = remove_duplicates(list);
	assert(verify_no_duplicates(list));
	print_list(list);

	printf("\n");

	return 0;
}
