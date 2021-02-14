#include "mystring.h"
#include <string.h>

int main(void){
    
    char s1[110] = "WWWabc";
    char s2[] = "WWWWWWWWW";

    char m1[] = "grafwVlakeies";
    char m2[] = "Vlak";

    size_t byt = 4;

    printf("s1 = %s\n",s1);
    printf("s2 = %s\n",s2);
    
    printf("\n------------PART 1------------\n");

    printf("Own: Size of s1 : %lu\n",ms_length(s1));
    printf("Lib: Size of s1 : %lu\n",strlen(s1));

    printf("Own: Size of s2 : %lu\n",ms_length(s2));
    printf("Lib: Size of s2 : %lu\n",strlen(s2));

    printf("Own: Compare s1 and s2 equals: %d\n",ms_compare(s1,s2));
    printf("Lib: Compare s1 and s2 equals: %d\n",strcmp(s1,s2));

    printf("Own: Compare 5 bytes s1 and s2 equals: %d\n",ms_ncompare(s1,s2,5));
    printf("Lib: Compare 5 bytes s1 and s2 equals: %d\n",strncmp(s1,s2,5));

    printf("Own: Compare 3 bytes s1 and s2 equals: %d\n",ms_ncompare(s1,s2,3));
    printf("Lib: Compare 3 bytes s1 and s2 equals: %d\n",strncmp(s1,s2,3));

    printf("Own: Compare 1 bytes s1 and s2 equals: %d\n",ms_ncompare(s1,s2,1));
    printf("Lib: Compare 1 bytes s1 and s2 equals: %d\n",strncmp(s1,s2,1));

    printf("Own: Compare 1000 bytes s1 and s2 equals: %d\n",ms_ncompare(s1,s2,1000));
    printf("Lib: Compare 1000 bytes s1 and s2 equals: %d\n\n",strncmp(s1,s2,1000)); /*segfault*/

    printf("------------PART 2------------\n");

    ms_copy(s1,s2);
    printf("Own: After copying whole s2 to s1:\n");
    printf("s1: %s\n",s1);
    printf("s2: %s\n",s2);

    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    strcpy(s1,s2);
    printf("Lib: After copying whole s2 to s1:\n");
    printf("s1: %s\n",s1);
    printf("s2: %s\n\n",s2);

    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    ms_ncopy(s1,s2,byt);
    printf("Own: After copying %lu bytes from s2 to s1:\n",byt);
    printf("s1: %s\n",s1);
    printf("s2: %s\n",s2);
    
    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    strncpy(s1,s2,byt);
    printf("Lib: After copying %lu bytes from s2 to s1:\n",byt);
    printf("s1: %s\n",s1);
    printf("s2: %s\n\n",s2);
    
    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    ms_concat(s1,s2);
    printf("Own: After colliding whole s2 to s1:\n");
    printf("s1: %s\n",s1);
    printf("s2: %s\n",s2);
    
    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    strcat(s1,s2);
    printf("Lib: After colliding whole s2 to s1:\n");
    printf("s1: %s\n",s1);
    printf("s2: %s\n\n",s2);
    
    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    byt = 3;
    ms_nconcat(s1,s2,byt);
    printf("Own: After colliding %lu bytes from s2 to s1:\n",byt);
    printf("s1: %s\n",s1);
    printf("s2: %s\n",s2);

    /*reset*/
    ms_copy(s1,"WWWabc");
    ms_copy(s2,"WWWWWWWWW");

    strncat(s1,s2,byt);
    printf("Lib: After colliding %lu bytes from s2 to s1:\n",byt);
    printf("s1: %s\n",s1);
    printf("s2: %s\n\n",s2);

    printf("------------PART 3------------\n");

    printf("Own:'%s' contains '%s' (1/0): %d\n",m1,m2,ms_search(m1,m2)!=NULL);
    printf("Lib:'%s' contains '%s' (1/0): %d\n",m1,m2,strstr(m1,m2)!=NULL);

    printf("Own:'%s' contains '%s' (1/0): %s\n",m1,m2,ms_search(m1,m2));
    printf("Lib:'%s' contains '%s' (1/0): %s\n\n",m1,m2,strstr(m1,m2));

    ms_copy(m1,m2);
    printf("After copying whole m2 to m1:\n");
    printf("m1: %s\n",m1);
    printf("m2: %s\n",m2);

    return 0;
}