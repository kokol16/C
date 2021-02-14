/* Csd4254 Georgios Kokolakis
   Assignment 2 hy255
   FIle name: mystring_ars.c
*/

#include"mystring.h"


size_t ms_length(const char pcStr[])
{
   size_t uiLength = 0U;
    assert(pcStr);

   assert(pcStr); /* Works because NULL and FALSE are identical. */
   while (pcStr[uiLength]) /* Works because end-of-string and FALSE are identical. */
      uiLength++;
   return uiLength;
}   

char *ms_copy(char str1[], const char str2[])
{
    size_t i=0U;  
    assert(str1);
    assert(str2);
    while(str2[i]!='\0')
    {
        str1[i]=str2[i];
        i++;
    }
    str1[i]='\0';
    return str1;
}


char *ms_ncopy(char str1[], const char str2[], size_t n)
{
    
    size_t index=0U;
    assert(str1);
    assert(str2);
    assert(n>0);
    while ( str2[index]!='\0' && index<n)
    {
        str1[index]=str2[index];
        index++;
    }
    
    return str1;
}
char *ms_concat(char str1[], const char str2[])
{
    
    size_t index = ms_length(str1);
    size_t index2=0U;
    assert(str1);
    assert(str2);

    while(str2[index2]!='\0')
    {
        str1[index]=str2[index2];
        index++;
        index2++;
    }
    return str1;
}

char *ms_nconcat(char *str1, const char *str2, size_t n)
{
    size_t index = ms_length(str1);
    size_t index2=0U;
    assert(str1);
    assert(str2);
    assert(n>0);
    while(str2[index2]!='\0' && index2<n)
    {
        str1[index]=str2[index2];
        index++;
        index2++;
    }
    str1[index]='\0';
    return str1;
}

int ms_compare(const char str1[], const char str2[])
{
    int index=0U;
    assert(str1);
    assert(str2);
    while(str1[index]!='\0' && str2[index]!='\0')
    {
        if (str1[index]!=str2[index])
        {
                return  (str1[index]-str2[index] ) ;
        }
        index++;
    }
    return 0;
}

int ms_ncompare(const char str1[], const char str2[], size_t n)
{
    size_t index=0U;
    assert(str1);
    assert(str2);
    assert(n>0);
    while(str1[index]!='\0' && str2[index]!='\0' && index<n)
    {
        if (str1[index]!=str2[index])
        {
                return (str1[index]-str2[index] );
        }
        index++;
    }
    return 0;
}

char *ms_search(const char str[],  char sub_str[])
{
    size_t size_sub=ms_length(sub_str);
    size_t sub_index=0U;
    size_t index=0U;
    assert(str);
    assert(sub_str);
    while(str[index]!='\0')
    {
        if (sub_str[sub_index] == str[index])
        {
            sub_index++;      
        }
        else
        {
            sub_index=0;
        }
        if(size_sub==sub_index)
        {
            return (char*) (str+index-sub_index+1);
        }
        index++;
    }
    return  NULL;


}

