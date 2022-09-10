

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"

typedef struct KeyValuePairObj *keyValPair;
/*allocaets a new keyValPair, returns NULL if failes */
keyValPair createKeyValuePair(CopyFunction copyFunctionKey, FreeFunction freeFunctionKey, PrintFunction printFunctionKey, EqualFunction equalFunctionKey,
							  CopyFunction copyFunctionVal, FreeFunction freeFunctionVal, PrintFunction printFunctionVal, Element key, Element value);
/*deallocates the keyValPair, return false if failes */
status destroykeyValPair(Element keyValue);
/*prints the Value of the keyValPair */
status displayValue(keyValPair keyVal);
/*prints the key of the keyValPair */
status displayKey(keyValPair keyVal);
/*returns the Value of the keyValPair */
Element getValue(keyValPair keyVal);
/*returns the key of the keyValPair */
Element getKey(keyValPair keyVal);
/*return true if a given key is equal to the key in a given keyValPair, else false*/
bool isEqualKey(Element keyVal, Element key);
/*prints keyValPair */
status PrintPair(Element keyValue);
/*returns deep copy of keyValPair, deallocates the original keyValPair*/
Element keyValCopy(Element keyValue);
/*return true if a given value is equals to the value in a given keyValPair, else false*/
bool isEqualValue(Element Value, Element valuePart);
#endif /* KEYVALUEPAIR_H_ */
