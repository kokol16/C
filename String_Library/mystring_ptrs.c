<<<<<<< HEAD
/* Csd4254 Georgios Kokolakis
   Assignment 2 hy255
   FIle name: mystring_ptr.c
*/
#include"mystring.h"



size_t ms_length(const char *pcStr)
{
   const char *pcStrEnd = pcStr;
   assert(pcStr != NULL);
   while (*pcStrEnd != '\0')
      pcStrEnd++;
   return pcStrEnd - pcStr;
}

char *ms_copy(char *str1, const char *str2)
{
    char *str_start=str1;
    assert(str1);
    assert(str2);
   
    while(*str2 !='\0')
    {
        *str1= *str2;
        str2++;
        str1++;
    }

    *str1='\0';
    return str_start;
}


char *ms_ncopy(char *str1, const char *str2, size_t n)
{

    size_t index=0U;
    char *str_start=str1;
    assert(str1);
    assert(str2);
    while ( *str2 !='\0' && index<n)
    {
      *str1=*str2;
        index++;
        str1++;
        str2++;
    }
    
    return str_start;
}

char *ms_concat(char *str1, const char *str2)
{

    size_t i=0;
    char *str_start=str1;
    
    size_t index = ms_length(str1);
    assert(str1);
    assert(str2);
    for (i=0; i<index; i++)
    {
        str1++;
    }
    while(*str2!='\0')
    {
        *str1=*str2;
        str1++;
        str2++;
    }
    *str1='\0';
    return str_start;
}

char *ms_nconcat(char *str1, const char *str2, size_t n)
{

    char *str_start=str1;
    size_t i=0;
    size_t index = ms_length(str1);
    size_t index2=0U;
    assert(str1);
    assert(str2);
    for (i=0; i<index; i++)
    {
        str1++;
    }
    while(*str2!='\0' && index2<n)
    {
        *str1=*str2;
        str1++;
        str2++;
        index2++;
    }
    *str1='\0';
    return str_start;
}

int ms_compare(const char *str1, const char *str2)
{

    assert(str1);
    assert(str2);
    
    while(*str1!='\0' && *str2!='\0')
    {
        if (*str1!=*str2)
        {
                return  (*str1-*str2 ) ;
        }
        str1++;
        str2++;

    }
    return 0;
}

int ms_ncompare(const char *str1, const char *str2, size_t n)
{

    size_t index=0U;
    assert(str1);
    assert(str2);
    while(*str1!='\0' && *str2!='\0' && index<n)
    {
        if (*str1!=*str2)
        {
                return (*str1-*str2 );
        }
        str1++;
        str2++;
        index++;
    }
    return 0;
}

char *ms_search(const char * str,  char *sub_str)
{
    assert(sub_str);
    assert(str);
    char * sub_string_start=sub_str;
    size_t size_sub=ms_length(sub_str);
    size_t sub_index=0U;
    while(*str!='\0')
    {
        if (*sub_str == *str)
        {
            sub_index++;      
            sub_str++;
        }
        else
        {
            sub_str=sub_string_start;
            sub_index=0;
        }
        if(size_sub==sub_index)
        {
            return (char*) (str-sub_index+1);
        }
        str++;
    }

    return  NULL;

}

=======
/* Csd4254 Georgios Kokolakis
   Assignment 2 hy255
   FIle name: mystring_ptr.c
*/
#include"mystring.h"



size_t ms_length(const char *pcStr)
{
   const char *pcStrEnd = pcStr;
   assert(pcStr != NULL);
   while (*pcStrEnd != '\0')
      pcStrEnd++;
   return pcStrEnd - pcStr;
}

char *ms_copy(char *str1, const char *str2)
{
    char *str_start=str1;
    assert(str1);
    assert(str2);
   
    while(*str2 !='\0')
    {
        *str1= *str2;
        str2++;
        str1++;
    }

    *str1='\0';
    return str_start;
}


char *ms_ncopy(char *str1, const char *str2, size_t n)
{

    size_t index=0U;
    char *str_start=str1;
    assert(str1);
    assert(str2);
    while ( *str2 !='\0' && index<n)
    {
      *str1=*str2;
        index++;
        str1++;
        str2++;
    }
    
    return str_start;
}

char *ms_concat(char *str1, const char *str2)
{

    size_t i=0;
    char *str_start=str1;
    
    size_t index = ms_length(str1);
    assert(str1);
    assert(str2);
    for (i=0; i<index; i++)
    {
        str1++;
    }
    while(*str2!='\0')
    {
        *str1=*str2;
        str1++;
        str2++;
    }
    *str1='\0';
    return str_start;
}

char *ms_nconcat(char *str1, const char *str2, size_t n)
{

    char *str_start=str1;
    size_t i=0;
    size_t index = ms_length(str1);
    size_t index2=0U;
    assert(str1);
    assert(str2);
    for (i=0; i<index; i++)
    {
        str1++;
    }
    while(*str2!='\0' && index2<n)
    {
        *str1=*str2;
        str1++;
        str2++;
        index2++;
    }
    *str1='\0';
    return str_start;
}

int ms_compare(const char *str1, const char *str2)
{

    assert(str1);
    assert(str2);
    
    while(*str1!='\0' && *str2!='\0')
    {
        if (*str1!=*str2)
        {
                return  (*str1-*str2 ) ;
        }
        str1++;
        str2++;

    }
    return 0;
}

int ms_ncompare(const char *str1, const char *str2, size_t n)
{

    size_t index=0U;
    assert(str1);
    assert(str2);
    while(*str1!='\0' && *str2!='\0' && index<n)
    {
        if (*str1!=*str2)
        {
                return (*str1-*str2 );
        }
        str1++;
        str2++;
        index++;
    }
    return 0;
}

char *ms_search(const char * str,  char *sub_str)
{
    assert(sub_str);
    assert(str);
    char * sub_string_start=sub_str;
    size_t size_sub=ms_length(sub_str);
    size_t sub_index=0U;
    while(*str!='\0')
    {
        if (*sub_str == *str)
        {
            sub_index++;      
            sub_str++;
        }
        else
        {
            sub_str=sub_string_start;
            sub_index=0;
        }
        if(size_sub==sub_index)
        {
            return (char*) (str-sub_index+1);
        }
        str++;
    }

    return  NULL;

}

>>>>>>> 039bc7123c2d8d478bf0172a4ce0ad14e5f01aa1
