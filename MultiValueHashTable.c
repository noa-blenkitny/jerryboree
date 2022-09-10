#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
struct multiHashTable_s
{
	hashTable table;
	int hashNumber;
	TransformIntoNumberFunction transformIntoNumber;
	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
	EqualFunction equalElement;
	EqualFunction equalPartElement;
};

multiHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
										 CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, EqualFunction equalElement,
										 TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL || transformIntoNumber == NULL)

		return NULL;

	multiHashTable table_t = (multiHashTable)malloc(sizeof(struct multiHashTable_s));
	if (table_t == NULL)
		// memory problem
		return NULL;

	table_t->table = createHashTable(copyKey, freeKey, printKey, copyList, destroyList, displayList, equalKey, transformIntoNumber, hashNumber);
	if (table_t->table == NULL)
	{
		// memory problem

		return NULL;
	}
	table_t->hashNumber = hashNumber;
	table_t->transformIntoNumber = transformIntoNumber;
	table_t->copyKey = copyKey;
	table_t->freeKey = freeKey;
	table_t->printKey = printKey;
	table_t->copyValue = copyValue;
	table_t->freeValue = freeValue;
	table_t->printValue = printValue;
	table_t->equalKey = equalKey;
	table_t->equalElement = equalElement;

	return table_t;
}

status destroyMultiValueHashTable(multiHashTable multiTable)
{
	if (multiTable == NULL)
		return failure;
	destroyHashTable(multiTable->table);
	multiTable->table = NULL;
	free(multiTable);
	multiTable = NULL;
	return success;
}
status addToMultiValueHahTable(multiHashTable multiTable, Element key, Element value)
{
	if (multiTable == NULL || key == NULL || value == NULL)
		return failure;

	Element res = lookupInHashTable(multiTable->table, key);
	if (res == NULL)
	{ // the key is not in the hashtable
		List valList = createLinkedList(multiTable->copyValue, multiTable->freeValue, multiTable->printValue,
										multiTable->equalElement, multiTable->equalElement);
		if (valList == NULL)
			// memory problem
			return failure;

		if (addToHashTable(multiTable->table, key, (Element)valList) == failure)
		{
			// MEMORYPROBLEM
			return failure;
		}
		destroyList(valList);
		Element res2 = lookupInHashTable(multiTable->table, key);
		if (appendNode(res2, (Element)value) == failure)
			// MEMORYPROBLEM
			return failure;
		return success;
	}

	else
	{
		return appendNode(res, value);
	}
}

List lookupInMultiValueHashTable(multiHashTable multiTable, Element key)
{
	if (multiTable == NULL || key == NULL)
		return NULL;
	Element res = lookupInHashTable(multiTable->table, key);
	if (res == NULL)
		return NULL;
	return (List)res;
}
status removeFromMultiValueHashTable(multiHashTable multiTable, Element key, Element value)
{
	if (multiTable == NULL || key == NULL || value == NULL)
		return failure;
	Element res = lookupInHashTable(multiTable->table, key);
	if (res == NULL)
		return failure;
	Element resValue = searchByKeyInList((List)res, value);
	if (resValue == NULL)
		return failure;
	deleteNode(res, resValue);
	if (getLengthList(res) == 0)
		removeFromHashTable(multiTable->table, key);
	return success;
}
status displayMultiValueHashTable(multiHashTable multiTable, Element key)
{
	if (multiTable == NULL || key == NULL)
		return failure;
	Element res = lookupInHashTable(multiTable->table, key);
	if (res == NULL)
		return failure;
	multiTable->printKey(key);
	displayList(res);
	return success;
}
