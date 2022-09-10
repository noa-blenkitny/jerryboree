/*
 * LinkedList.h
 *
 *  Created on: Dec 2, 2020
 *      Author: ise
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"

typedef struct LinkedList *List;
/*allocaets a new LinkedList, returns NULL if failes */
List createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction,
					  EqualFunction equalFunctionElement, EqualFunction equalFunctionElementPart);
/*deallocates the LinkedList, return false if failes */
status destroyList(Element list_t);
/*allocate a new Node and add it to the end of the LinkedList. return false if fails. */
status appendNode(List list, Element elem);
/*searching for the elem in the LinkedList, if exists deallocate the Node with the elem from the LinkedList, if dosn't exist return failure.*/
status deleteNode(List list, Element elem);
/*prints all the Value of each Node in the LinkedList */
status displayList(Element list_t);
/*searching for elem in the LinkedList by given index. returns NULL if failes */
Element getDataByIndex(List list, int index);
/*returns the size of the LinkesList by an updating field of the LinkedList */
int getLengthList(List list);
/*searching for elem in the LinkedList by given key . returns NULL if failes */
Element searchByKeyInList(List list, Element elem);
/*returns deep copy of LinkedList, returns NULL if failes. doesn't deallocate the original list*/
Element copyList(Element list_t);
/*returns the head pointer value of the LinkesList */
Element getHead(List list);
/*returns the end pointer value of the LinkesList */
Element getEnd(List list);
#endif /* LINKEDLIST_H_ */
