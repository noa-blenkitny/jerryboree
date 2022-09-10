/*
 * MultiValueHashTable.h
 *
 *  Created on: Dec 5, 2020
 *      Author: ise
 */

#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "Defs.h"
#include "LinkedList.h"
typedef struct multiHashTable_s *multiHashTable;
/*allocaets a new multiHashTable, returns NULL if failes */
multiHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
										 CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
										 EqualFunction equalElement, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
/*deallocates the multiHashTable, return false if failes */
status destroyMultiValueHashTable(multiHashTable multiTable);
/* adds a new element to the multiHashTable by unique key, return false if failed or if the key is already in the table*/
status addToMultiValueHahTable(multiHashTable multiTable, Element key, Element value);
/*returns the value mapped to the key in the multiHashTable, return NULL if the key isn't in the table */
List lookupInMultiValueHashTable(multiHashTable multiTable, Element key);
/*deallocates the key and the value mapped to the key from the multiHashTable, return failure if the key isn't in the table */
status removeFromMultiValueHashTable(multiHashTable multiTable, Element key, Element value);
/*prints all the keys and the values mapped to them in the multiHashTable*/
status displayMultiValueHashTable(multiHashTable multiTable, Element key);

#endif /* MULTIVALUEHASHTABLE_H_ */
