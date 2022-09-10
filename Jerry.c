#include "Jerry.h"

Jerry *Create_Jerry(char *id, char *dimension, Planet *planet, int HP)
{
	if ((id == NULL) || (dimension == NULL) || (planet == NULL))
		return NULL;
	Jerry *new_Jerry = (Jerry *)malloc(sizeof(Jerry));
	if (new_Jerry == NULL)
	{
		// memory problem
		return NULL;
	}

	new_Jerry->char_num = 0;
	new_Jerry->ID = ((char *)malloc(strlen(id) + 1));
	if (new_Jerry->ID == NULL)
	{
		// memory problem
		return NULL;
	}
	strcpy(new_Jerry->ID, id);
	new_Jerry->Happiness = HP;
	new_Jerry->physical_char = NULL;
	new_Jerry->origin = Create_Origin(dimension, planet);
	if (new_Jerry->origin == NULL)
	{
		// memory problem
		return NULL;
	}
	return new_Jerry;
}

Origin *Create_Origin(char *Name, Planet *planet)
{

	if ((Name == NULL) || (planet == NULL))
		return NULL;

	Origin *new_Origin = (Origin *)malloc(sizeof(Origin));
	if (new_Origin == NULL)
	{
		// memory problem
		return NULL;
	}

	new_Origin->name = ((char *)malloc(strlen(Name) + 1));
	if (new_Origin->name == NULL)
	{
		// memory problem
		return NULL;
	}
	strcpy(new_Origin->name, Name);
	new_Origin->origin_planet = planet;
	return new_Origin;
}

Planet *Create_Planet(char *Name, double x, double y, double z)
{
	if (Name == NULL)
		return NULL;
	Planet *new_Planet = (Planet *)malloc(sizeof(Planet));
	if (new_Planet == NULL)
	{
		// memory problem
		return NULL;
	}
	new_Planet->name = ((char *)malloc(strlen(Name) + 1));
	if (new_Planet->name == NULL)
	{
		// memory problem
		return NULL;
	}
	strcpy(new_Planet->name, Name);
	new_Planet->x = x;
	new_Planet->y = y;
	new_Planet->z = z;
	return new_Planet;
}

PhysicalCharacteristics *Create_Physical_Char(char *Name, double val)
{
	if (Name == NULL)
		return NULL;
	PhysicalCharacteristics *new_Physical_Char = (PhysicalCharacteristics *)malloc(sizeof(PhysicalCharacteristics));
	if (new_Physical_Char == NULL)
	{
		// memory problem
		return NULL;
	}
	new_Physical_Char->name = ((char *)malloc(strlen(Name) + 1));
	if (new_Physical_Char->name == NULL)
	{
		// memory problem
		return NULL;
	}
	strcpy(new_Physical_Char->name, Name);
	new_Physical_Char->value = val;
	return new_Physical_Char;
}

status Add_Physic_Char(Jerry *jerry, char *Name, double Val)
{
	if ((jerry == NULL) || Name == NULL)
		return failure;

	if (jerry->char_num == 0)
	{
		jerry->physical_char = (PhysicalCharacteristics **)malloc(sizeof(PhysicalCharacteristics *));
		if (jerry->physical_char == NULL)
		{
			// memory problem
			return failure;
		}
		jerry->physical_char[0] = Create_Physical_Char(Name, Val);
		if (jerry->physical_char[0] == NULL)
		{
			// Memory Problem
			return failure;
		}
		jerry->char_num++;
	}
	else
	{
		PhysicalCharacteristics **temp = (PhysicalCharacteristics **)realloc(jerry->physical_char, (jerry->char_num + 1) * sizeof(PhysicalCharacteristics *));
		if (temp == NULL)
		{
			printf("Memory Problem");
			return failure;
		}

		jerry->physical_char = temp;
		jerry->physical_char[jerry->char_num] = Create_Physical_Char(Name, Val);
		if (jerry->physical_char[jerry->char_num] == NULL)
		{
			// Memory Problem
			return failure;
		}
		jerry->char_num++;
	}
	return success;
}

bool Check_Physic_Char(Jerry jerry, char *physic_char_name)
{
	if (physic_char_name == NULL)
		return false;
	int i = 0;
	for (i = 0; i < jerry.char_num; i++)
	{
		if (strcmp(physic_char_name, jerry.physical_char[i]->name) == 0)
		{
			return true;
		}
	}
	return false;
}

status Print_Jerry(Element jerry_t)
{

	if (jerry_t == NULL)
		return failure;

	Jerry *jerry = (Jerry *)jerry_t;
	if (jerry->char_num == 0)
	{
		printf("Jerry , ID - %s : \nHappiness level : %d \nOrigin : %s \nPlanet : %s (%.2f,%.2f,%.2f) \n", jerry->ID, jerry->Happiness, jerry->origin->name, jerry->origin->origin_planet->name, jerry->origin->origin_planet->x, jerry->origin->origin_planet->y, jerry->origin->origin_planet->z);
	}
	else
	{
		// printing the physical chars in a for loop
		printf("Jerry , ID - %s : \nHappiness level : %d \nOrigin : %s \nPlanet : %s (%.2f,%.2f,%.2f) \n", jerry->ID, jerry->Happiness, jerry->origin->name, jerry->origin->origin_planet->name, jerry->origin->origin_planet->x, jerry->origin->origin_planet->y, jerry->origin->origin_planet->z);
		int i = 0;
		printf("Jerry's physical Characteristics available : \n\t");
		for (i = 0; i < (jerry->char_num) - 1; i++)
		{
			printf("%s : %.2f , ", jerry->physical_char[i]->name, jerry->physical_char[i]->value);
		}
		printf("%s : %.2f \n", jerry->physical_char[jerry->char_num - 1]->name, jerry->physical_char[jerry->char_num - 1]->value);
	}
	return success;
}

status Print_Planet(Planet *planet)
{
	if (planet == NULL)
		return failure;
	else
	{
		printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->name, planet->x, planet->y, planet->z);
	}
	return success;
}

status Delete_Physic_Char(Jerry *jerry, char *Name)
{
	if ((jerry == NULL) || (Name == NULL))
		return failure;
	int i = 0;
	for (i = 0; i < jerry->char_num; i++)
	{
		if (strcmp(Name, jerry->physical_char[i]->name) == 0)
		{
			PhysicalCharacteristics **temp = (PhysicalCharacteristics **)malloc(((jerry->char_num) - 1) * sizeof(PhysicalCharacteristics *));
			if (temp == NULL)
			{
				// Memory Problem
				return failure;
			}
			int j = i - 1;
			for (j = i - 1; j >= 0; j--)
			{
				temp[j] = Create_Physical_Char(jerry->physical_char[j]->name, jerry->physical_char[j]->value);
				if (temp[j] == NULL)
				{
					// Memory Problem
					return failure;
				}
			}

			int k = i + 1;
			for (k = i + 1; k < jerry->char_num; k++)
			{
				temp[k - 1] = Create_Physical_Char(jerry->physical_char[k]->name, jerry->physical_char[k]->value);
				if (temp[k - 1] == NULL)
				{
					// Memory Problem
					return failure;
				}
			}
			int t = 0;
			for (t = 0; t < jerry->char_num; t++)
			{
				free(jerry->physical_char[t]->name);
				jerry->physical_char[t]->name = NULL;
				free(jerry->physical_char[t]);
				jerry->physical_char[t] = NULL;
			}

			free(jerry->physical_char);
			jerry->physical_char = NULL;
			jerry->char_num--;
			jerry->physical_char = temp;

			break;
		}
	}
	return success;
}
status Destroy_Jerry(Element jerry_t)
{
	Jerry *jerry = (Jerry *)jerry_t;
	if (jerry == NULL)
		return failure;
	free(jerry->ID);
	jerry->ID = NULL;
	int i = 0;
	for (i = 0; i < jerry->char_num; i++)
	{
		Destroy_Physical_Char(jerry->physical_char[i]);
		free(jerry->physical_char[i]);
		jerry->physical_char[i] = NULL;
	}
	free(jerry->physical_char);
	jerry->physical_char = NULL;
	Destroy_Origin(jerry->origin);
	free(jerry);
	jerry = NULL;
	return success;
}

void Destroy_Planet(Planet *planet)
{
	if (planet == NULL)
		return;
	free(planet->name);
	planet->name = NULL;
	free(planet);
	planet = NULL;
}
void Destroy_Origin(Origin *origin)
{
	free(origin->name);
	origin->name = NULL;
	free(origin);
	origin = NULL;
}

void Destroy_Physical_Char(PhysicalCharacteristics *physical_char)
{
	free(physical_char->name);
	physical_char->name = NULL;
}

Element CopyJerry(Element jerry_t)
{
	Jerry *jerry = (Jerry *)jerry_t;
	if (jerry == NULL)
		return NULL;
	Jerry *new_jerry = Create_Jerry(jerry->ID, jerry->origin->name, jerry->origin->origin_planet, jerry->Happiness);
	if (new_jerry == NULL)
		// memory problem
		return NULL;
	int i;
	for (i = 0; i < jerry->char_num; i++)
	{
		if (Add_Physic_Char(new_jerry, jerry->physical_char[i]->name, jerry->physical_char[i]->value) == failure)
			// memorry problem
			return NULL;
	}
	Destroy_Jerry(jerry_t);
	return new_jerry;
}

bool equalInJerryID(Element jerry_t, Element id_t)
{

	Jerry *jerry = (Jerry *)jerry_t;
	char *id = (char *)id_t;
	if (jerry == NULL || id == NULL)
		return false;
	if (strcmp(id, jerry->ID) == 0)
		return true;
	return false;
}

bool equalJerries(Element jerry_t, Element jerry_s)
{
	if (jerry_t == NULL || jerry_s == NULL)
		return false;
	Jerry *jerry1 = (Jerry *)jerry_t;
	Jerry *jerry2 = (Jerry *)jerry_s;
	return (strcmp(jerry1->ID, jerry2->ID) == 0 ? true : false);
}

Element shallowCopyJerry(Element jerry_t)
{
	if (jerry_t == NULL)
		return NULL;
	Jerry *jerry = (Jerry *)jerry_t;
	return jerry;
}
