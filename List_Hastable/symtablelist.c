/* @Author :George Kokolakis (csd4254)
   exercise 3 hy255 */
#include"symtable.h"
#include<assert.h>
#include<string.h>
#define true 1
#define false 0
struct Binding
{
    char * key;
    void * value;
    struct Binding* next;

};

struct  SymTableADT
{
    struct  Binding *head;
};



/*
   This method frees the memory that the SymTable has allocated
*/
void SymTable_free(SymTable_T oSymTable)
{
    Bindning_t iterator,previous;
    if(oSymTable==NULL){return ;}
    iterator=oSymTable->head;
    while(iterator!=NULL)
    {
        previous=iterator;
        iterator=iterator->next;
        free(previous->key);
        free(previous);
    }
    free(oSymTable);


}
/*
   This method calls the apply method
   for every binding in the SymTable
   @param pfApply The method that will be called 
   for each binding on the SymTable
   @param pvExtra An extra variable 
*/

void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{ 
    Bindning_t iterator;
    iterator=oSymTable->head;
    while(iterator!=NULL)
    {
        (*pfApply)(iterator->key,iterator->value,(void*)5 );
        iterator=iterator->next;
    }
}

/*
   This method finds the value of the binding 
   with the current key
   @param pcKey The key of the  binding
   @return the value of the current binding
*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey) 
{
    Bindning_t iterator;
    assert(oSymTable);
    assert(pcKey);
    iterator=oSymTable->head;
    while(iterator!=NULL && strcmp (pcKey ,iterator->key)>0 )
    {
        iterator=iterator->next;
    }
    if(iterator!=NULL && strcmp(pcKey,iterator->key)==0)
    {
        return  iterator->value;
    }
    return NULL;
}

/*
   This method check if the SymTable contains the binding
   with the current key 
   @param pcKey The key of the  binding
   @return if the SymTable contains the binding
*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    Bindning_t iterator;
    assert(oSymTable);
    assert(pcKey);
    iterator=oSymTable->head;
    while(iterator!=NULL && strcmp (pcKey,iterator->key)>0 )
    {
        iterator=iterator->next;
    }
    if(iterator!=NULL && strcmp(pcKey,iterator->key)==0)
    {
        return  true;
    }
    return false;
}

/*
   This method removes a binding from the  SymTable
   @param pcKey The key of the  binding
   @return if the  binding removed succesfully
*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    Bindning_t iterator,previous=NULL;
    assert(oSymTable);
    assert(pcKey);
    iterator=oSymTable->head;
    while(iterator!=NULL && strcmp (pcKey ,iterator->key)>0 )
    {
        previous=iterator;
        iterator=iterator->next;
    }
    if(iterator!=NULL && strcmp(pcKey,iterator->key)==0)
    {
        if(previous==NULL)
        {
            oSymTable->head= iterator->next;

        
        }else
        {

            previous->next=iterator->next;            
        }
        free(iterator->key);
        free(iterator);
        
        return  true;
    }
    return false;
}

/*
   This method counts the number of bindings that SymTable contains
   @return The number of bindings 
*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    unsigned int count_nodes=0;
    Bindning_t iterator;
    assert(oSymTable);
    iterator=oSymTable->head;
    while(iterator!=NULL)
    {
        count_nodes++;
        iterator=iterator->next;
    }
    return count_nodes;
}



/*
    This method creates a new binding 
    with key->pcKey and value->pvValue
    @param pcKey the key of the new binding
    @param pvValue the value of the new binding
    @return the new binding
*/
static Bindning_t Create_Binding(const char *pcKey, const void *pvValue)
{
    Bindning_t  binding;
    binding=malloc(sizeof(Bindning_t));
    binding->key=malloc(strlen(pcKey)+1);
    strcpy (binding->key,pcKey);
    binding->value=(void *) pvValue;
    binding->next=NULL;
    return binding;
}

/* This method prints The SymTable's bindings*/

void Print_SymTable_list(SymTable_T table)
{ 
    Bindning_t iterator;
    iterator=table->head;
    while(iterator!=NULL)
    {
        printf("key:%s====value: %p \n",iterator->key, (iterator->value)  );
        iterator=iterator->next;
    }
}

/*
   This method inserts a new binding in the SymTable
   @param pcKey The key of the new binding
   @param pvValue The value of the new binding 
   @return if the new binding added to the SymTable succesfully

*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    Bindning_t iterator,new_bindning,previous=NULL;
    iterator= oSymTable->head;
    assert(pcKey);
    assert(pvValue);    
    assert(oSymTable);
    /*first node of the empty list*/
    if(oSymTable->head==NULL)
    {
        oSymTable->head=Create_Binding(pcKey,pvValue);
        return true;
    }
    while(iterator!=NULL && strcmp(pcKey,iterator->key)>0)
    {
        previous=iterator;
        iterator=iterator->next;
    }
    if(previous==NULL && strcmp(pcKey,iterator->key)!=0 )/*insert at the beggining of the list*/
    {
        new_bindning=Create_Binding(pcKey,pvValue);
        new_bindning->next=iterator;
        oSymTable->head=new_bindning;
    }
    else if(iterator!=NULL && strcmp(pcKey,iterator->key)==0)/*check if the key has already been inserted*/
    {
        printf("error , already inserted\n");
        return false;
    }
    else /*insert at the end of the list or at a regular position*/
    {
        new_bindning=Create_Binding(pcKey,pvValue);
        new_bindning->next=previous->next;
        previous->next=new_bindning;

    }
    
    
    
    return true;



}

/*This method creates an empty SymTable*/
SymTable_T SymTable_new(void)
{
    SymTable_T sym_table;
    sym_table=malloc(sizeof(SymTable_T));
    return sym_table;
}
