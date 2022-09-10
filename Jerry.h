
#ifndef Jerry_h
#define Jerry_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct Planet
{
   char *name;
   double x;
   double y;
   double z;
} Planet;

typedef struct Origin
{
   char *name;
   Planet *origin_planet;
} Origin;

typedef struct PhysicalCharacteristics
{
   char *name;
   double value;
} PhysicalCharacteristics;

typedef struct Jerry
{
   char *ID;
   int Happiness;
   Origin *origin;
   PhysicalCharacteristics **physical_char;
   int char_num;
} Jerry;

/*allocates a new Jerry. returns NULL if fails*/
Jerry *Create_Jerry(char *id, char *dimension, Planet *planet, int HP);
/*allocates a new Planet. returns NULL if fails*/
Planet *Create_Planet(char *, double, double, double);
/*allocates a new Physical characteristic. returns NULL if fails*/
PhysicalCharacteristics *Create_Physical_Char(char *, double);
/*allocates a new Origin. returns NULL if fails*/
Origin *Create_Origin(char *, Planet *);
/*returns true if Jerry has the physical characteristic, else false */
bool Check_Physic_Char(Jerry, char *);
/*allocate a new Physical characteristic and add it to Jerry. return false if fails. */
status Add_Physic_Char(Jerry *jerry, char *Name, double Val);
/*deallocate the physical characteristic from jerry.*/
status Delete_Physic_Char(Jerry *, char *);
/*prints Jerry*/
status Print_Jerry(Element jerry_t);
/*prints Jerry*/
status Print_Planet(Planet *);
/*deallocates Jerry*/
status Destroy_Jerry(Element);
/*deallocates the Planet*/
void Destroy_Planet(Planet *);
/*deallocates the Origin*/
void Destroy_Origin(Origin *);
/*deallocates the physical characteristic*/
void Destroy_Physical_Char(PhysicalCharacteristics *);
/*returns deep copy of Jerry, deallocates the original Jerry*/
Element CopyJerry(Element jerry_t);
/*returns shallow copy of Jerry*/
Element shallowCopyJerry(Element jerry_t);
/*return true if the id_t is the id of jerry_t, else false*/
bool equalInJerryID(Element jerry_t, Element id_t);
/*return true if jerry_t is the same as jerry_s, else false*/
bool equalJerries(Element jerry_t, Element jerry_s);
#endif
