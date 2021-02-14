/* @Author :George Kokolakis (csd4254)
   exercise 3 hy255 */

#include"symtable.h"
#include<assert.h>
#include<string.h>
 
#define HASH_MULTIPLIER 65599
#define true 1
#define false 0 
typedef struct Binding_List *binding_List_t;

static int Check_for_Expand(SymTable_T oSymTable); 
static int SymTable_put_No_Expand(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

unsigned int Size=2;

struct Binding
{
    char * key;
    void * value;
    struct Binding* next;

};
 struct Binding_List
{
    unsigned int size;
    Bindning_t head;

};
struct  SymTableADT
{
   binding_List_t symTable;
};


/*This method creates an empty SymTable*/

SymTable_T SymTable_new(void)
{
    SymTable_T sym_table;
    int i=0;
    sym_table=malloc(sizeof(SymTable_T));
    sym_table->symTable= malloc( Size * sizeof(struct Binding_List));
    for (i=0; i<Size; i++)
    {
        (sym_table->symTable[i] ).size=0;
        (sym_table->symTable[i]).head=NULL;
        
    }
    return sym_table;
}
static unsigned int SymTable_hash(const char *pcKey)
{
    
    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)
 
    uiHash = (uiHash + pcKey[ui])/3;
     
/*
size_t ui;
unsigned int uiHash = 0U;
for (ui = 0U; pcKey[ui] != '\0'; ui++)
 
uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];

return (uiHash%Size);*/
    return  (uiHash%Size );
}


/*
    This method expands the hashtable's size
    when it's needed
*/
static int Check_for_Expand(SymTable_T oSymTable)
{
    unsigned int prev_size,new_size;
    int i=0;
    Bindning_t prev,node;
    int j;
    int Expand;
    Bindning_t iter;
    SymTable_T tmp_sym_table;
    prev_size=Size;
    Expand=0;
    /*check if the size of a list is bigger than the array size*/
    for(i=0; i<Size; i++)
    {
        if( (oSymTable->symTable[i]).size >= Size)
        {

            Expand=true;
            break;
        }
    }
    if(Expand)       
    {
        /*create a temporary symtable to store the old data*/
        tmp_sym_table=SymTable_new();
        /*copy old hash table to a temp table */
        for (i=0; i<Size; i++ )
        {
            iter= (oSymTable->symTable[i] ).head;
            if( iter!=NULL)
            {
                SymTable_put(tmp_sym_table,iter->key,iter->value);
            }
        }
      
        /*find the new size*/
        if(Size==2)
        {
            new_size=1021;
        }
        else if(Size==10)
        {
            new_size=2053;
            
        }
        else if(Size==2053)
        {
            new_size=4093;
            
        }
        else if(Size==4093)
        {
            new_size=8191;
            
        }
        else if(Size==8191)
        {
            new_size=16381;
            
        }
        else if(Size==16381)
        {
            new_size=32771;
            
        }
        else if(Size==32771)
        {
            new_size=65521;
            
        }

        /*free the array each binding of the table */
        for(i=0; i<Size; i++) 
        {
        
              node=(oSymTable->symTable[i]).head;
              for(j=0; j< (oSymTable->symTable[i]).size;  j++)
              {
                  prev=node;
                  node=node->next;
                  free(prev->key);
                  free(prev);
              }
        }
      
    
        free ( oSymTable->symTable); /*free array*/
        /*create new table with the new size*/
        Size=new_size;
        oSymTable->symTable= malloc( Size * sizeof(struct Binding_List));
        for (i=0; i<Size; i++)
        {
            (oSymTable->symTable[i] ).size=0;
            (oSymTable->symTable[i]).head=NULL;
        
        }
        
        /*copy the tmp table to the new table*/
        for (i=0; i<prev_size; i++ )
        {
            iter= (tmp_sym_table->symTable[i] ).head;
            while( iter!=NULL)
            {
                SymTable_put_No_Expand(oSymTable,iter->key,iter->value);
                iter=iter->next;
            }
        }

        /*free tmp table*/
        Size=prev_size;
        SymTable_free(tmp_sym_table);
       

        Size=new_size;
        return true;
    }
    return false;
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
    int i;
    for (i=0; i<Size; i++)
    {
        iterator= (oSymTable->symTable[i] ).head;
        while(iterator!=NULL)
        {
           (*pfApply)(iterator->key,iterator->value,(void*)3);
            iterator=iterator->next;
        }
    }
}

/*
   This method frees the memory that the SymTable has allocated
*/

void SymTable_free(SymTable_T oSymTable)
{
    int i,j;
    Bindning_t prev,node;
    printf  ("size is : %d\n",Size);

    for(i=0; i<Size; i++) 
    {
        
        node=(oSymTable->symTable[i]).head;
        for(j=0; j< (oSymTable->symTable[i]).size;  j++)
        {
            prev=node;
            node=node->next;
            free(prev->key);
            free(prev);
        }
       
      /* free ( (oSymTable->symTable[i]).head->key );free the key*/
    }
   free ( oSymTable->symTable); /*free array*/
   free(oSymTable);
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
    unsigned int index;
    assert(oSymTable);
    assert(pcKey);
    index=SymTable_hash(pcKey);/*get the index of the array that the key will be inserted*/
    iterator=(oSymTable->symTable[index]).head;
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
    unsigned int index;
    assert(oSymTable);
    assert(pcKey);
    index=SymTable_hash(pcKey);/*get the index of the array that the key will be inserted*/
    
    iterator=(oSymTable->symTable[index]).head;

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
    Bindning_t  iterator, previous=NULL;
    unsigned int index;
    assert(pcKey);
    assert(oSymTable);
 
    index=SymTable_hash(pcKey);/*get the index of the array that the key will be inserted*/
    
    iterator=(oSymTable->symTable[index]).head;
    
    while(iterator!=NULL && strcmp (pcKey ,iterator->key)>0 )
    {
        previous=iterator;
        iterator=iterator->next;
    }
    if(iterator!=NULL && strcmp(pcKey,iterator->key)==0)
    {
        if(previous==NULL)
        {
            ( oSymTable->symTable[index] ).head = iterator->next;
        }
        else
        {
            previous->next=iterator->next; 
        }
        ( oSymTable->symTable[index] ).size--; 
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
    unsigned int count_nodes=0,i;
    binding_List_t iterator;
    assert(oSymTable);
    iterator=oSymTable->symTable;
    for(i=0; i<Size; i++)
    {
        count_nodes+= iterator[i].size;
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
    binding->value=(void *)pvValue;
    binding->next=NULL;
    return binding;
}

/*
   This method inserts a new binding in the SymTable
   @param pcKey The key of the new binding
   @param pvValue The value of the new binding 
   @return if the new binding added to the SymTable succesfully

*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    Bindning_t  iterator, new_bindning, previous=NULL;
    unsigned int index;

    assert(pcKey);
    assert(pvValue);    
    assert(oSymTable);
 
    index=SymTable_hash(pcKey);/*get the index of the array that the key will be inserted*/
    if(index>=Size)
    {
        printf("size is not acceptable \n");
        return false;
    }
   
    if( (oSymTable->symTable[index] ).head==NULL)
    {
        (oSymTable->symTable[index] ).head=Create_Binding(pcKey,pvValue);
        (oSymTable->symTable[index]).size++;
        Check_for_Expand(oSymTable);

        return true;
    }
    iterator = (oSymTable->symTable[index] ).head;
   
    while(iterator!=NULL && strcmp(pcKey,iterator->key)>0)
    {
        previous=iterator;
        iterator=iterator->next;
    }
    if(previous==NULL && strcmp(pcKey,iterator->key)!=0 )/*insert at the beggining of the list*/
    {
        new_bindning=Create_Binding(pcKey,pvValue);
        new_bindning->next=iterator;
        (oSymTable->symTable[index] ).head=new_bindning;
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
    oSymTable->symTable[index].size++;
 
    Check_for_Expand(oSymTable);


    return true;

}






 

/* This method prints The SymTable's bindings*/



void Print_SymTable_list(SymTable_T table)
{
    int i,j;
    Bindning_t iterator;
    for (i=0; i<Size; i++)
    {
        iterator =(table->symTable[i] ).head;
        if ( iterator!=NULL )
        {
            for (j=0; j< (table->symTable[i] ).size; j++)
            {
                printf("( %s==%p )-->",iterator->key, iterator->value);
                iterator=iterator->next;
            }
        printf("\n");
        }
    }
}


/*
   This method inserts a new binding in the SymTable
   without checking if expand is needed
   @param pcKey The key of the new binding
   @param pvValue The value of the new binding 
   @return if the new binding added to the SymTable succesfully

*/
static int SymTable_put_No_Expand(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    Bindning_t  iterator, new_bindning, previous=NULL;
    unsigned int index;

    assert(pcKey);
    assert(pvValue);    
    assert(oSymTable);
 
    index=SymTable_hash(pcKey);/*get the index of the array that the key will be inserted*/
    if(index>=Size)
    {
        printf("size is not acceptable \n");
        return false;
    }
   
    if( (oSymTable->symTable[index] ).head==NULL)
    {
        (oSymTable->symTable[index] ).head=Create_Binding(pcKey,pvValue);
        (oSymTable->symTable[index]).size++;
        Check_for_Expand(oSymTable);

        return true;
    }
    iterator = (oSymTable->symTable[index] ).head;
   
    while(iterator!=NULL && strcmp(pcKey,iterator->key)>0)
    {
        previous=iterator;
        iterator=iterator->next;
    }
    if(previous==NULL && strcmp(pcKey,iterator->key)!=0 )/*insert at the beggining of the list*/
    {
        new_bindning=Create_Binding(pcKey,pvValue);
        new_bindning->next=iterator;
        (oSymTable->symTable[index] ).head=new_bindning;
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
    oSymTable->symTable[index].size++;
 
    

    return true;

}
