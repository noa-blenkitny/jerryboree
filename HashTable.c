#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s
{
	List *array;
	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
	TransformIntoNumberFunction transformIntoNumber;
	int hashNumber;
};

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
						  CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
						  TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL || transformIntoNumber == NULL)
		return NULL;
	hashTable table = (hashTable)malloc(sizeof(struct hashTable_s));
	if (table == NULL)
		// memory problem
		return NULL;
	table->copyKey = copyKey;
	table->freeKey = freeKey;
	table->printKey = printKey;
	table->equalKey = equalKey;
	table->copyValue = copyValue;
	table->freeValue = freeValue;
	table->printValue = printValue;
	table->transformIntoNumber = transformIntoNumber;
	table->hashNumber = hashNumber;
	table->array = (List *)malloc((sizeof(List)) * hashNumber);
	if (table->array == NULL)
		// memory problem
		return NULL;

	int index;
	for (index = 0; index < hashNumber; index++)
	{
		table->array[index] = createLinkedList(keyValCopy, destroykeyValPair, PrintPair, isEqualKey, isEqualKey);
		if (table->array[index] == NULL)
			// memory problem
			return NULL;
	}

	return table;
}

status addToHashTable(hashTable table, Element key, Element value)
{
	if (table == NULL || key == NULL || value == NULL)
		return failure;
	int index = table->transformIntoNumber(key) % table->hashNumber;
	if (searchByKeyInList(table->array[index], key) != NULL) // the key is already in the list
		return failure;
	keyValPair keyVal = createKeyValuePair(table->copyKey, table->freeKey, table->printKey, table->equalKey, table->copyValue,
										   table->freeValue, table->printValue, key, value);
	if (keyVal == NULL)
		// memory problem
		return failure;

	status res = appendNode(table->array[index], (Element)keyVal);
	if (res == failure)
		// memory problem
		return failure;
	return success;
}

status destroyHashTable(hashTable table)
{
	if (table == NULL)
		return failure;
	int i;
	for (i = 0; i < table->hashNumber; i++)
	{
		destroyList(table->array[i]);
		table->array[i] = NULL;
	}
	free(table->array);
	table->array = NULL;
	free(table);
	table = NULL;
	return success;
}

Element lookupInHashTable(hashTable table, Element key)
{
	if (table == NULL || key == NULL)
		return NULL;
	int index = table->transformIntoNumber(key) % table->hashNumber;
	Element res = searchByKeyInList(table->array[index], key);
	if (res == NULL)
		return NULL;
	return getValue(res);
}

status removeFromHashTable(hashTable table, Element key)
{
	if (table == NULL || key == NULL)
		return failure;
	int index = table->transformIntoNumber(key) % table->hashNumber;
	return (deleteNode(table->array[index], key));
}

status displayHashElements(hashTable table)
{
	if (table == NULL)
		return failure;
	int i;
	for (i = 0; i < table->hashNumber; i++)
	{
		displayList(table->array[i]);
	}
	return success;
}
