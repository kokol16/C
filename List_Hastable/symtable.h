/* @Author :George Kokolakis (csd4254)
   exercise 3 hy255 */

#include<stdio.h>
#include<stdlib.h>
typedef struct  SymTableADT *SymTable_T;
typedef struct Binding *Bindning_t;

/*This method creates an empty SymTable*/
SymTable_T SymTable_new(void);

/*
   This method frees the memory that the SymTable has allocated
*/
void SymTable_free(SymTable_T oSymTable);


/*
   This method counts the number of bindings that SymTable contains
   @return The number of bindings 
*/
unsigned int SymTable_getLength(SymTable_T oSymTable);

/*
   This method inserts a new binding in the SymTable
   @param pcKey The key of the new binding
   @param pvValue The value of the new binding 
   @return if the new binding added to the SymTable succesfully

*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

/*
   This method removes a binding from the  SymTable
   @param pcKey The key of the  binding
   @return if the  binding removed succesfully
*/

int SymTable_remove(SymTable_T oSymTable, const char *pcKey);
/*
   This method check if the SymTable contains the binding
   with the current key 
   @param pcKey The key of the  binding
   @return if the SymTable contains the binding
*/

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);


/*
   This method finds the value of the binding 
   with the current key
   @param pcKey The key of the  binding
   @return the value of the current binding
*/

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);



/*
   This method calls the apply method
   for every binding in the SymTable
   @param pfApply The method that will be called 
   for each binding on the SymTable
   @param pvExtra An extra variable 
*/

void SymTable_map(SymTable_T oSymTable,

void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
const void *pvExtra);


/*my functions*/

/* This method prints The SymTable's bindings*/
void Print_SymTable_list(SymTable_T oSymTable);
