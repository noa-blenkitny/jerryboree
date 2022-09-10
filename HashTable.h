
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Defs.h"

typedef struct hashTable_s *hashTable;
/*allocaets a new hash table, returns NULL if failes */
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
						  FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
/*deallocates the hash table, return false if failes */
status destroyHashTable(hashTable);
/* adds a new element to the hash table by unique key, return false if failed or if the key is already in the table*/
status addToHashTable(hashTable, Element key, Element value);
/*returns the value mapped to the key in the hash table, return NULL if the key isn't in the table */
Element lookupInHashTable(hashTable, Element key);
/*deallocates the key and the value mapped to the key from the hash table, return failure if the key isn't in the table */
status removeFromHashTable(hashTable, Element key);
/*prints all the keys and the values mapped to them in the hash table */
status displayHashElements(hashTable);

#endif /* HASH_TABLE_H */
