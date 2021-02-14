#include"symtable.h"


void pfApply(const char *pcKey, void *pvValue,  void *pvExtra)
{
  
    printf("%ld\n", (size_t)pvValue  +  (size_t)pvExtra ) ;
    
}

int main()
{
    SymTable_T table; 
    table =SymTable_new();
    

    SymTable_put(table,"george",(void*)10);
    SymTable_put(table,"manos",(void*)2);
    
    Print_SymTable_list(table);
    
    
    SymTable_put(table,"olimpia",(void*)10);
    
    SymTable_put(table,"olimpi",(void*)10);
    
    SymTable_put(table,"olimp",(void*)10);
    printf("--------------------------------\n");
    Print_SymTable_list(table);
    
    printf("--------------------------------\n");
    printf("after removing olimpia\n");
    
    SymTable_remove(table,"olimpia");

    Print_SymTable_list(table);

    printf("--------------------------------\n");
   
    SymTable_put(table,"giannis",(void*)13);
   
    Print_SymTable_list(table);
   

    printf("--------------------------------\n");
    
    printf("after removing giannis\n");
    SymTable_remove(table,"giannis");
    Print_SymTable_list(table);
    
    SymTable_put(table,"eua",(void*)1);
    printf("--------------------------------\n");
    
    Print_SymTable_list(table);
  
    if (SymTable_contains(table,"olimpia") )
    {
        printf("found olimpia\n");
    }
    else
    {
        printf("didn't find  olimpia\n");
        
    }
    
    printf("number of nodes: %d\n",SymTable_getLength(table));
    printf("%s key is : %p\n" ,"george", SymTable_get(table,"george") );
    printf("%s key is : %p\n" ,"olimpi", SymTable_get(table,"olimpi" ) );
    SymTable_put(table, "olimpi",(void*)10);
    printf("CALLING MAP ---------------\n");
    printf("value of each binding added with pVextra\n");
    SymTable_map( table,pfApply, (void*)5);  
   
    SymTable_free(table); 

    
    
                                                    
    return 0;
}
