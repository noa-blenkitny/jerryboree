#include "LinkedList.h"
typedef struct Node
{
	struct Node *next;
	Element elem;
} Node;
/* a structure that represents a generic LinkedList */
struct LinkedList
{
	CopyFunction copyFunction;
	FreeFunction freeFunction;
	PrintFunction printFunction;
	EqualFunction equalFunctionElement;
	EqualFunction equalFunctionElementPart;
	int size;
	Node *head;
	Node *end;
};

List createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction,
					  EqualFunction equalFunctionElement, EqualFunction equalFunctionElementPart)
{
	if (copyFunction == NULL || freeFunction == NULL || printFunction == NULL || equalFunctionElement == NULL || equalFunctionElementPart == NULL)
		return NULL;
	List list = (List)malloc(sizeof(struct LinkedList));
	if (list == NULL)
		// memory problem
		return NULL;
	list->copyFunction = copyFunction;
	list->equalFunctionElement = equalFunctionElement;
	list->equalFunctionElementPart = equalFunctionElementPart;
	list->freeFunction = freeFunction;
	list->printFunction = printFunction;
	list->size = 0;
	list->head = NULL;
	list->end = NULL;
	return list;
}

status destroyList(Element list_t)
{
	List list = (List)list_t;
	if (list == NULL)
		return failure;
	Node *curr;
	while (list->head != NULL)
	{
		curr = list->head;
		list->head = curr->next;
		list->freeFunction(curr->elem);
		free(curr);
	}
	curr = NULL;
	list->size = 0;
	list->head = NULL;
	list->end = NULL;
	free(list);
	list = NULL;
	return success;
}
status appendNode(List list, Element elem)
{
	if (list == NULL || elem == NULL)
		return failure;
	Node *node = (Node *)malloc(sizeof(Node));
	node->next = NULL;
	Element newElem = list->copyFunction(elem);
	if (newElem == NULL)
		// memory problem?
		return failure;
	node->elem = newElem;
	if (list->size == 0)
	{
		list->head = node;
		list->end = node;
	}
	else
	{
		list->end->next = node;
		list->end = node;
	}
	list->size++;
	return success;
}
status deleteNode(List list, Element elem)
{
	if (list == NULL || elem == NULL)
		return failure;

	if (list->size == 0)
	{
		return failure;
	}
	else if (list->size == 1)
	{
		if (list->equalFunctionElement(list->head->elem, elem))
		{
			list->freeFunction(list->head->elem);
			free(list->head);
			list->head = NULL;
			list->end = NULL;
			list->size--;
			return success;
		}
		return failure;
	}
	else
	{
		if (list->equalFunctionElement(list->head->elem, elem))
		{
			Node *temp = list->head;
			list->head = list->head->next;
			list->freeFunction(temp->elem);
			free(temp);
			temp = NULL;
			list->size--;
			return success;
		}
		Node *curr = list->head->next;
		Node *prev = list->head;
		int i;
		for (i = 1; i < list->size - 1; i++)
		{

			if (list->equalFunctionElement(curr->elem, elem))
			{
				prev->next = curr->next;
				list->freeFunction(curr->elem);
				free(curr);
				curr = NULL;
				list->size--;
				return success;
			}
			prev = prev->next;
			curr = curr->next;
		}
		if (list->equalFunctionElement(curr->elem, elem))
		{
			list->end = prev;
			list->end->next = NULL;
			list->freeFunction(curr->elem);
			free(curr);
			curr = NULL;
			list->size--;
			return success;
		}
	}
	return failure;
}
int getLengthList(List list)
{
	if (list == NULL)
		return -1;
	return list->size;
}
status displayList(Element list_t)
{
	List list = (List)list_t;
	if (list == NULL)
		return failure;

	Node *curr;
	curr = list->head;
	while (curr != NULL)
	{
		list->printFunction(curr->elem);
		curr = curr->next;
	}
	return success;
}

Element getDataByIndex(List list, int index)
{
	if (list == NULL)
		return NULL;
	if (index < 1 || index > list->size)
		return NULL;
	int i;
	Node *curr = list->head;
	for (i = 1; i < index; i++)
	{
		curr = curr->next;
	}
	return curr->elem;
}

Element searchByKeyInList(List list, Element elem)
{
	if (list == NULL || elem == NULL)
		return NULL;
	int i;
	Node *curr = list->head;
	for (i = 0; i < list->size; i++)
	{

		if (list->equalFunctionElementPart(curr->elem, elem))
		{
			return curr->elem;
		}
		curr = curr->next;
	}
	return NULL;
}

Element copyList(Element list_t)
{
	List list = (List)list_t;
	List copyList = (List)malloc(sizeof(struct LinkedList));
	if (copyList == NULL)
		// memory problem
		return NULL;
	copyList->copyFunction = list->copyFunction;
	copyList->equalFunctionElement = list->equalFunctionElement;
	copyList->equalFunctionElementPart = list->equalFunctionElementPart;
	copyList->freeFunction = list->freeFunction;
	copyList->printFunction = list->printFunction;
	copyList->size = 0;
	copyList->head = NULL;
	copyList->end = NULL;
	Node *curr;
	while (list->head != NULL)
	{
		curr = list->head;
		appendNode(copyList, curr);
		list->head = curr->next;
	}
	return copyList;
}

Element getHead(List list)
{
	if (list == NULL)
		return NULL;
	return list->head->elem;
}
Element getEnd(List list)
{
	if (list == NULL)
		return NULL;
	return list->end->elem;
}
