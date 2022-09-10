#include "KeyValuePair.h"

struct KeyValuePairObj
{
	CopyFunction copyFunctionKey;
	FreeFunction freeFunctionKey;
	PrintFunction printFunctionKey;
	EqualFunction equalFunctionKey;
	CopyFunction copyFunctionVal;
	FreeFunction freeFunctionVal;
	PrintFunction printFunctionVal;
	Element key;
	Element value;
};

keyValPair createKeyValuePair(CopyFunction copyFunctionKey, FreeFunction freeFunctionKey, PrintFunction printFunctionKey, EqualFunction equalFunctionKey,
							  CopyFunction copyFunctionVal, FreeFunction freeFunctionVal, PrintFunction printFunctionVal, Element key, Element value)
{
	if (copyFunctionKey == NULL || freeFunctionKey == NULL || printFunctionKey == NULL || equalFunctionKey == NULL || key == NULL || value == NULL || copyFunctionVal == NULL || freeFunctionVal == NULL || printFunctionVal == NULL)
		return NULL;
	keyValPair keyVal = (keyValPair)malloc(sizeof(struct KeyValuePairObj));
	if (keyVal == NULL)
		// memory problem
		return NULL;
	keyVal->copyFunctionKey = copyFunctionKey;
	keyVal->equalFunctionKey = equalFunctionKey;
	keyVal->freeFunctionKey = freeFunctionKey;
	keyVal->printFunctionKey = printFunctionKey;
	keyVal->copyFunctionVal = copyFunctionVal;
	keyVal->freeFunctionVal = freeFunctionVal;
	keyVal->printFunctionVal = printFunctionVal;
	keyVal->key = keyVal->copyFunctionKey(key);
	keyVal->value = keyVal->copyFunctionVal(value);
	return keyVal;
}

status destroykeyValPair(Element keyValue)
{
	keyValPair keyVal = (keyValPair)keyValue;

	if (keyVal == NULL)
		return failure;
	keyVal->freeFunctionKey(keyVal->key);
	keyVal->freeFunctionVal(keyVal->value);
	free(keyVal);
	keyVal = NULL;
	return success;
}
status displayValue(keyValPair keyVal)
{
	if (keyVal == NULL)
		return failure;
	keyVal->printFunctionVal(keyVal->value);
	return success;
}
status displayKey(keyValPair keyVal)
{
	if (keyVal == NULL)
		return failure;
	keyVal->printFunctionKey(keyVal->key);
	return success;
}
Element getValue(keyValPair keyVal)
{
	if (keyVal == NULL)
		return NULL;
	return keyVal->value;
}
Element getKey(keyValPair keyVal)
{
	if (keyVal == NULL)
		return NULL;
	return keyVal->key;
}

status PrintPair(Element keyValue)
{
	keyValPair keyVal = (keyValPair)keyValue;
	if (keyVal == NULL)
		return failure;
	displayKey(keyVal);
	displayValue(keyVal);
	return success;
}
Element keyValCopy(Element keyValue)
{
	keyValPair keyVal = (keyValPair)keyValue;
	if (keyVal == NULL)
		return NULL;
	keyValPair newKeyVal = createKeyValuePair(keyVal->copyFunctionKey, keyVal->freeFunctionKey, keyVal->printFunctionKey, keyVal->equalFunctionKey, keyVal->copyFunctionVal, keyVal->freeFunctionVal, keyVal->printFunctionVal, keyVal->key, keyVal->value);
	if (newKeyVal == NULL)
		// memory problem
		return NULL;
	destroykeyValPair(keyValue);
	return (Element)newKeyVal;
}

bool isEqualValue(Element Value, Element valuePart)
{
	if (Value == NULL || valuePart == NULL)
		return false;
	keyValPair keyValue = (keyValPair)Value;
	Element val = keyValue->value;
	return keyValue->equalFunctionKey(val, valuePart);
}

bool isEqualKey(Element keyVal, Element key)
{
	keyValPair keyValue = (keyValPair)keyVal;
	if (keyValue == NULL || key == NULL)
		return false;
	return keyValue->equalFunctionKey((Element)keyValue->key, key);
}
