#include "LinkedList.h"
#include "KeyValuePair.h"
#include "Defs.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"
#include <math.h>

void printMenu()
{
	printf("Welcome Rick, what are your Jerry's needs today ? \n");
	printf("1 : Take this Jerry away from me \n");
	printf("2 : I think I remember something about my Jerry \n");
	printf("3 : Oh wait. That can't be right \n");
	printf("4 : I guess I will take back my Jerry now \n");
	printf("5 : I can't find my Jerry. Just give me a similar one \n");
	printf("6 : I lost a bet. Give me your saddest Jerry \n");
	printf("7 : Show me what you got \n");
	printf("8 : Let the Jerries play \n");
	printf("9 : I had enough. Close this place \n");
}
/*returns the index of the planet in the planets array, -1 if not found*/
int findPlanetByName(Planet **Planets_array, int numofplanets, char *planet_name)
{
	if (Planets_array == NULL || planet_name == NULL)
		return -1;

	int planetIndex = 0;
	for (planetIndex = 0; planetIndex < numofplanets; planetIndex++)
	{
		if (strcmp(planet_name, Planets_array[planetIndex]->name) == 0)
		{
			return planetIndex;
		}
	}
	return -1;
}

status printID(Element id_t)
{
	if (id_t == NULL)
		return failure;
	printf("%s", (char *)id_t);
	return success;
}

status freeShallowCopy(Element elem)
{
	if (elem == NULL)
		return failure;
	return success;
}

status freeKeyCopy(Element elem)
{
	if (elem == NULL)
		return failure;
	free((char *)elem);
	return success;
}

Element copyID(Element id_t)
{
	if (id_t == NULL)
		return NULL;
	char *id = (char *)malloc(strlen((char *)id_t) + 1);
	if (id == NULL)
		// memory problem
		return NULL;
	strcpy(id, (char *)id_t);
	return id;
}

bool equalChar(Element key, Element charName)
{
	if (key == NULL || charName == NULL)
		return false;
	return (strcmp((char *)key, (char *)charName) == 0 ? true : false);
}

int TransformIntoNumberFunc(Element key)
{
	char *str = (char *)key;
	int sum = 0;
	while (*str)
	{
		sum += *str++;
	}
	return sum;
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char str[300];
	char *filename = argv[2];
	int numofplanets = atoi(argv[1]); // cast string to int

	Planet **Planets_array = (Planet **)malloc(numofplanets * sizeof(Planet *));
	if (Planets_array == NULL)
	{
		printf("Memory Problem \n"); // nothing was allocated yet
		exit(1);
	}

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s \n", filename);
		return 1;
	}

	fgets(str, 300, fp); // first line is planets

	int i = 0;
	for (i = 0; i < numofplanets; i++)
	{
		char *line = fgets(str, 300, fp); // gets the next line
		char *token = strtok(line, ",");  // gets the next token
		char *words[4];
		int j = 0;
		while (token != NULL)
		{

			words[j++] = token;

			token = strtok(NULL, ",");
		}
		Planets_array[i] = Create_Planet(words[0], atof(words[1]), atof(words[2]), atof(words[3]));
		if (Planets_array[i] == NULL) // need to deallocate the planets
		{
			int j = 0;
			for (j = 0; j < i; j++)
			{
				Destroy_Planet(Planets_array[j]);
			}
			free(Planets_array);
			Planets_array = NULL;
			printf("Memory Problem \n");
			exit(1);
		}
	}

	List jerriesList = createLinkedList(CopyJerry, Destroy_Jerry, Print_Jerry, equalInJerryID, equalInJerryID);
	if (jerriesList == NULL)
	{
		// memmory problem
		int k = 0;
		for (k = 0; k < numofplanets; k++)
		{
			Destroy_Planet(Planets_array[k]);
		}
		free(Planets_array);
		Planets_array = NULL;
		printf("Memory Problem \n");
		exit(1);
	}
	fgets(str, 300, fp); // first line is Jerries
	while (!feof(fp))
	{

		char *jerry_line = fgets(str, 300, fp);		 // gets the next line
		char *jerry_token = strtok(jerry_line, ","); // gets the next token
		char *jerry_words[4];
		int m = 0;
		while (jerry_token != NULL)
		{
			jerry_words[m++] = jerry_token;
			jerry_token = strtok(NULL, ",");
		}

		int n = 0;
		if (jerry_line[0] != '\t')
		{
			for (n = 0; n < numofplanets; n++)
			{
				if (strcmp(jerry_words[2], Planets_array[n]->name) == 0)
				{
					Jerry *new_jerry = Create_Jerry(jerry_words[0], jerry_words[1], Planets_array[n], atoi(jerry_words[3]));
					if (new_jerry == NULL)
					{
						// memmory problem
						destroyList(jerriesList);
						int k = 0;
						for (k = 0; k < numofplanets; k++)
						{
							Destroy_Planet(Planets_array[k]);
						}
						free(Planets_array);
						Planets_array = NULL;
						printf("Memory Problem \n");
						exit(1);
					}

					if (appendNode(jerriesList, new_jerry) == failure)
					{
						// memory problem
						destroyList(jerriesList);
						int k = 0;
						for (k = 0; k < numofplanets; k++)
						{
							Destroy_Planet(Planets_array[k]);
						}
						free(Planets_array);
						Planets_array = NULL;
						printf("Memory Problem \n");
						exit(1);
					}
				}
			}
		}

		else
		{
			char *jerry_token = strtok(jerry_line, ":");
			char *physical_chars[2];
			int l = 0;
			while (jerry_token != NULL)
			{
				physical_chars[l++] = jerry_token;
				jerry_token = strtok(NULL, ":");
			}

			int index = 0;
			memmove(&physical_chars[0][index], &physical_chars[0][index + 1], strlen(physical_chars[0]) - index); // the first char is a tab, we need to remove it
			Jerry *myJerry = (Jerry *)getEnd(jerriesList);
			if (Add_Physic_Char(myJerry, physical_chars[0], atof(physical_chars[1])) == failure)
			{
				destroyList(jerriesList);
				int k = 0;
				for (k = 0; k < numofplanets; k++)
				{
					Destroy_Planet(Planets_array[k]);
				}
				free(Planets_array);
				Planets_array = NULL;
				printf("Memory Problem \n");
				exit(1);
			}
		}
	}
	fclose(fp);

	hashTable hashTableByID = createHashTable(copyID, freeKeyCopy, printID, shallowCopyJerry, freeShallowCopy,
											  Print_Jerry, equalChar, TransformIntoNumberFunc, 19);
	if (hashTableByID == NULL)
	{
		// memory problem
		destroyList(jerriesList);
		int k = 0;
		for (k = 0; k < numofplanets; k++)
		{
			Destroy_Planet(Planets_array[k]);
		}
		free(Planets_array);
		Planets_array = NULL;
		printf("Memory Problem \n");
		exit(1);
	}

	multiHashTable multiHashByPhysicalChar = createMultiValueHashTable(copyID, freeKeyCopy, printID, shallowCopyJerry,
																	   freeShallowCopy, Print_Jerry, equalChar, equalJerries, TransformIntoNumberFunc, 19);
	if (multiHashByPhysicalChar == NULL)
	{
		// memory problem
		destroyHashTable(hashTableByID);
		destroyList(jerriesList);
		int k = 0;
		for (k = 0; k < numofplanets; k++)
		{
			Destroy_Planet(Planets_array[k]);
		}
		free(Planets_array);
		Planets_array = NULL;
		printf("Memory Problem \n");
		exit(1);
	}
	int jerryNum;
	for (jerryNum = 1; jerryNum <= getLengthList(jerriesList); jerryNum++)
	{
		Jerry *currJerry = (Jerry *)getDataByIndex(jerriesList, jerryNum);
		if (addToHashTable(hashTableByID, currJerry->ID, currJerry) == failure)
		{
			// memory problem
			destroyMultiValueHashTable(multiHashByPhysicalChar);
			destroyHashTable(hashTableByID);
			destroyList(jerriesList);
			int k = 0;
			for (k = 0; k < numofplanets; k++)
			{
				Destroy_Planet(Planets_array[k]);
			}
			free(Planets_array);
			Planets_array = NULL;
			printf("Memory Problem \n");
			exit(1);
		}
		int physicNum;
		for (physicNum = 0; physicNum < currJerry->char_num; physicNum++)
		{
			if (addToMultiValueHahTable(multiHashByPhysicalChar, currJerry->physical_char[physicNum]->name, currJerry) == failure)
			{
				// memory problem
				destroyMultiValueHashTable(multiHashByPhysicalChar);
				destroyHashTable(hashTableByID);
				destroyList(jerriesList);
				int k = 0;
				for (k = 0; k < numofplanets; k++)
				{
					Destroy_Planet(Planets_array[k]);
				}
				free(Planets_array);
				Planets_array = NULL;
				printf("Memory Problem \n");
				exit(1);
			}
		}
	}
	// starting the Main Menu
	char choosen[300], choosen7[300], choosen8[300];
	char ID[300], Planet[300], Origin[300], physical[300];
	int Happines = 0, planetNum = 0, jerryIndex, planetsIndex;
	float value;
	choosen[0] = '0';
	while (choosen[0] != '9')
	{
		printMenu();
		scanf("%s", choosen);
		if (strlen(choosen) == 1)
		{
			switch (choosen[0])
			{

			case '1':

				printf("What is your Jerry's ID ? \n");
				scanf("%s", ID);
				Jerry *jerry = lookupInHashTable(hashTableByID, ID);
				if (jerry != NULL)
					printf("Rick did you forgot ? you already left him here ! \n");
				else
				{
					printf("What planet is your Jerry from ? \n");
					scanf("%s", Planet);
					int planetIndex = findPlanetByName(Planets_array, numofplanets, Planet);
					if (planetIndex == -1)
					{
						printf("%s is not a known planet ! \n", Planet);
					}
					else
					{
						printf("What is your Jerry's dimension ? \n");
						scanf("%s", Origin);
						printf("How happy is your Jerry now ? \n");
						scanf("%d", &Happines);
						Jerry *newJerry = Create_Jerry(ID, Origin, Planets_array[planetIndex], Happines);
						if (newJerry == NULL)
						{
							// memory problem
							destroyMultiValueHashTable(multiHashByPhysicalChar);
							destroyHashTable(hashTableByID);
							destroyList(jerriesList);
							int k = 0;
							for (k = 0; k < numofplanets; k++)
							{
								Destroy_Planet(Planets_array[k]);
							}
							free(Planets_array);
							Planets_array = NULL;
							printf("Memory Problem \n");
							exit(1);
						}
						if (appendNode(jerriesList, newJerry) == failure)
						{
							// memory problem
							destroyMultiValueHashTable(multiHashByPhysicalChar);
							destroyHashTable(hashTableByID);
							destroyList(jerriesList);
							int k = 0;
							for (k = 0; k < numofplanets; k++)
							{
								Destroy_Planet(Planets_array[k]);
							}
							free(Planets_array);
							Planets_array = NULL;
							printf("Memory Problem \n");
							exit(1);
						}

						if (addToHashTable(hashTableByID, ID, searchByKeyInList(jerriesList, ID)) == failure)
						{
							// memory problem
							destroyMultiValueHashTable(multiHashByPhysicalChar);
							destroyHashTable(hashTableByID);
							destroyList(jerriesList);
							int k = 0;
							for (k = 0; k < numofplanets; k++)
							{
								Destroy_Planet(Planets_array[k]);
							}
							free(Planets_array);
							Planets_array = NULL;
							printf("Memory Problem \n");
							exit(1);
						}
						Print_Jerry(searchByKeyInList(jerriesList, ID));
					}
				}
				break;

			case '2':

				printf("What is your Jerry's ID ? \n");
				scanf("%s", ID);
				Jerry *jerry2 = lookupInHashTable(hashTableByID, ID);
				if (jerry2 == NULL)
				{
					printf("Rick this Jerry is not in the daycare ! \n");
				}
				else
				{
					printf("What physical characteristic can you add to Jerry - %s ? \n", ID);
					scanf("%s", physical);
					List jerriesWithPhysical = lookupInMultiValueHashTable(multiHashByPhysicalChar, physical);
					Jerry *jerryToAdd = searchByKeyInList(jerriesWithPhysical, jerry2);
					if (jerryToAdd != NULL)
					{
						printf("The information about his %s already available to the daycare ! \n", physical);
					}
					else
					{
						printf("What is the value of his %s ? \n", physical);
						scanf("%f", &value);

						if (Add_Physic_Char(jerry2, physical, value) == failure)
						{
							destroyMultiValueHashTable(multiHashByPhysicalChar);
							destroyHashTable(hashTableByID);
							destroyList(jerriesList);
							int k = 0;
							for (k = 0; k < numofplanets; k++)
							{
								Destroy_Planet(Planets_array[k]);
							}
							free(Planets_array);
							Planets_array = NULL;
							printf("Memory Problem \n");
							exit(1);
						}
						if (addToMultiValueHahTable(multiHashByPhysicalChar, physical, jerry2) == failure)
						{
							// memory problem
							destroyMultiValueHashTable(multiHashByPhysicalChar);
							destroyHashTable(hashTableByID);
							destroyList(jerriesList);
							int k = 0;
							for (k = 0; k < numofplanets; k++)
							{
								Destroy_Planet(Planets_array[k]);
							}
							free(Planets_array);
							Planets_array = NULL;
							printf("Memory Problem \n");
							exit(1);
						}
						printf("%s : \n", physical);
						displayList(lookupInMultiValueHashTable(multiHashByPhysicalChar, physical));
					}
				}
				break;

			case '3':
				printf("What is your Jerry's ID ? \n");
				scanf("%s", ID);
				Jerry *jerry3 = lookupInHashTable(hashTableByID, ID);
				if (jerry3 == NULL)
				{
					printf("Rick this Jerry is not in the daycare ! \n");
				}
				else
				{
					printf("What physical characteristic do you want to remove from Jerry - %s ? \n", ID);
					scanf("%s", physical);

					List jerriesWithPhysical3 = lookupInMultiValueHashTable(multiHashByPhysicalChar, physical);
					Jerry *jerry3ToRemove = searchByKeyInList(jerriesWithPhysical3, jerry3);
					if (jerry3ToRemove == NULL)
					{
						printf("The information about his %s not available to the daycare ! \n", physical);
					}
					else
					{
						Delete_Physic_Char(jerry3ToRemove, (char *)physical);
						removeFromMultiValueHashTable(multiHashByPhysicalChar, physical, jerry3ToRemove); // the last param changed from ID to jerry3ToRemove
						Print_Jerry(jerry3);
					}
				}
				break;

			case '4':
				printf("What is your Jerry's ID ? \n");
				scanf("%s", ID);
				Jerry *jerry4 = lookupInHashTable(hashTableByID, ID);
				if (jerry4 == NULL)
				{
					printf("Rick this Jerry is not in the daycare ! \n");
				}
				else
				{
					int physicalChar;
					for (physicalChar = 0; physicalChar < jerry4->char_num; physicalChar++)
					{
						removeFromMultiValueHashTable(multiHashByPhysicalChar, jerry4->physical_char[physicalChar]->name, jerry4);
					}
					removeFromHashTable(hashTableByID, ID);

					deleteNode(jerriesList, ID);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
				}
				break;

			case '5':
				printf("What do you remember about your Jerry ? \n");
				scanf("%s", physical);
				List JerriesWithPhysical5 = lookupInMultiValueHashTable(multiHashByPhysicalChar, physical);
				if (JerriesWithPhysical5 == NULL)
				{
					printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physical);
				}
				else
				{
					printf("What do you remember about the value of his %s ? \n", physical);
					scanf("%f", &value);
					int index;
					double minimalValue = INFINITY;
					Jerry *minimalValueJerry = getHead(JerriesWithPhysical5);
					for (index = 1; index <= getLengthList(JerriesWithPhysical5); index++)
					{
						Jerry *tempJerry = getDataByIndex(JerriesWithPhysical5, index);
						int physicInJerry;
						for (physicInJerry = 0; physicInJerry < tempJerry->char_num; physicInJerry++)
						{
							if (strcmp(physical, tempJerry->physical_char[physicInJerry]->name) == 0)
							{
								if (fabs(tempJerry->physical_char[physicInJerry]->value - value) < minimalValue)
								{
									minimalValue = fabs(tempJerry->physical_char[physicInJerry]->value - value);
									minimalValueJerry = tempJerry;
								}
							}
						}
					}
					printf("Rick this is the most suitable Jerry we found : \n");
					Print_Jerry(minimalValueJerry);
					int physicalChar5;
					for (physicalChar5 = 0; physicalChar5 < minimalValueJerry->char_num; physicalChar5++)
					{
						removeFromMultiValueHashTable(multiHashByPhysicalChar, minimalValueJerry->physical_char[physicalChar5]->name, minimalValueJerry);
					}
					removeFromHashTable(hashTableByID, minimalValueJerry->ID);
					deleteNode(jerriesList, minimalValueJerry->ID);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
				}

				break;

			case '6':

				if (getLengthList(jerriesList) == 0)
				{
					printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
				}
				else
				{
					int jerryIndex;
					int minimalHappiness = 100;
					Jerry *minimalHappinessJerry = getHead(jerriesList);
					for (jerryIndex = 1; jerryIndex <= getLengthList(jerriesList); jerryIndex++)
					{
						Jerry *tempJerry6 = getDataByIndex(jerriesList, jerryIndex);
						if (tempJerry6->Happiness < minimalHappiness)
						{
							minimalHappiness = tempJerry6->Happiness;
							minimalHappinessJerry = tempJerry6;
						}
					}
					printf("Rick this is the most suitable Jerry we found : \n");
					Print_Jerry(minimalHappinessJerry);
					int physicalChar6;
					for (physicalChar6 = 0; physicalChar6 < minimalHappinessJerry->char_num; physicalChar6++)
					{
						removeFromMultiValueHashTable(multiHashByPhysicalChar, minimalHappinessJerry->physical_char[physicalChar6]->name, minimalHappinessJerry);
					}
					removeFromHashTable(hashTableByID, minimalHappinessJerry->ID);
					deleteNode(jerriesList, minimalHappinessJerry->ID);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
				}
				break;

			case '7':

				printf("What information do you want to know ? \n");
				printf("1 : All Jerries \n");
				printf("2 : All Jerries by physical characteristics \n");
				printf("3 : All known planets \n");
				scanf("%s", choosen7);
				if (strlen(choosen7) == 1)
				{
					switch (choosen7[0])
					{
					case '1':
						if (getLengthList(jerriesList) == 0)
						{
							printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
						}
						else
						{
							displayList(jerriesList);
						}
						break;
					case '2':
						printf("What physical characteristics ? \n");
						scanf("%s", physical);
						List JerriesWithPhysical7 = lookupInMultiValueHashTable(multiHashByPhysicalChar, physical);
						if (JerriesWithPhysical7 == NULL)
						{
							printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physical);
						}
						else
						{
							printf("%s : \n", physical);
							displayList(JerriesWithPhysical7);
						}
						break;
					case '3':

						for (planetNum = 0; planetNum < numofplanets; planetNum++)
						{
							Print_Planet(Planets_array[planetNum]);
						}
						break;
					default:
						printf("Rick this option is not known to the daycare ! \n");
						break;
					}
				}
				else
				{
					printf("Rick this option is not known to the daycare ! \n");
					break;
				}

				break;

			case '8':
				if (getLengthList(jerriesList) > 0)
				{
					printf("What activity do you want the Jerries to partake in ? \n");
					printf("1 : Interact with fake Beth \n");
					printf("2 : Play golf \n");
					printf("3 : Adjust the picture settings on the TV \n");
					scanf("%s", choosen8);
					if (strlen(choosen8) == 1)
					{
						switch (choosen8[0])
						{

						case '1':
							for (jerryIndex = 1; jerryIndex <= getLengthList(jerriesList); jerryIndex++)
							{
								Jerry *currJerry1 = getDataByIndex(jerriesList, jerryIndex);
								if (currJerry1->Happiness >= 20)
								{
									currJerry1->Happiness += 15;
									if (currJerry1->Happiness > 100)
									{
										currJerry1->Happiness = 100;
									}
								}
								else
								{
									currJerry1->Happiness -= 5;
									if (currJerry1->Happiness < 0)
									{
										currJerry1->Happiness = 0;
									}
								}
							}
							printf("The activity is now over ! \n");
							displayList(jerriesList);
							break;
						case '2':
							for (jerryIndex = 1; jerryIndex <= getLengthList(jerriesList); jerryIndex++)
							{
								Jerry *currJerry2 = getDataByIndex(jerriesList, jerryIndex);
								if (currJerry2->Happiness >= 50)
								{
									currJerry2->Happiness += 10;
									if (currJerry2->Happiness > 100)
									{
										currJerry2->Happiness = 100;
									}
								}
								else
								{
									currJerry2->Happiness -= 10;
									if (currJerry2->Happiness < 0)
									{
										currJerry2->Happiness = 0;
									}
								}
							}
							printf("The activity is now over ! \n");
							displayList(jerriesList);
							break;

						case '3':
							for (jerryIndex = 1; jerryIndex <= getLengthList(jerriesList); jerryIndex++)
							{
								Jerry *currJerry3 = getDataByIndex(jerriesList, jerryIndex);
								currJerry3->Happiness += 20;
								if (currJerry3->Happiness > 100)
								{
									currJerry3->Happiness = 100;
								}
							}
							printf("The activity is now over ! \n");
							displayList(jerriesList);
							break;
						default:
							printf("Rick this option is not known to the daycare ! \n");
							break;
						}
					}
					else
					{
						printf("Rick this option is not known to the daycare ! \n");
						break;
					}
				}
				else
				{
					printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
				}
				break;

			case '9':
				destroyMultiValueHashTable(multiHashByPhysicalChar);
				destroyHashTable(hashTableByID);
				destroyList(jerriesList);
				for (planetsIndex = 0; planetsIndex < numofplanets; planetsIndex++)
				{
					Destroy_Planet(Planets_array[planetsIndex]);
				}
				free(Planets_array);
				Planets_array = NULL;
				printf("The daycare is now clean and close ! \n");
				exit(0);
				break;

			default:
				printf("Rick this option is not known to the daycare ! \n");
				break;
			}
		}

		else
		{
			printf("Rick this option is not known to the daycare ! \n");
			choosen[0] = '0';
		}
	}

	return 0;
}
