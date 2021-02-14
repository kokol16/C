/* @Author : George Kokolakis csd4254 assignment 2 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define N 10

void *customers_function(void *arg);
void *chef_function(void *arg);
void Checkforfb();



pthread_mutex_t customer_mutex;

sem_t semaphore_fb; //semaphore for hadnling chef on facebook
sem_t semaphore_chef;//semaphore for handling that chef cooked the food    
sem_t semaphore_customer;//semaphore for handling that we have a customer


long numberofcust = 0;//counting number of customers
int customer_ended = 1;//customer left the store
long customers_served = 0;//how many customers have been served
long customers_in = 0;//the ammount of customers that need to get served

int main()
{
    pthread_t thread[N+1];
    long i = 0;

    // initialize the semaphore
    sem_init(&semaphore_chef, 0, 0);
    sem_init(&semaphore_customer, 0, 0);
    sem_init(&semaphore_fb, 0, 1);



    pthread_create(&thread[0], NULL, chef_function, NULL);
    // for loop creates threads΄

    for (i = 0; i < N; i++)
    {
        //if(i%3==0)
        if (i != 0   && i % 3 == 0)
        {

           sleep(4);

        }

        pthread_create(&thread[i + 1], NULL, customers_function, NULL);
    }
    for (i = 0; i < N + 1; i++)
    {
        pthread_join(thread[i], NULL);
    }

    sem_destroy(&semaphore_chef);
    sem_destroy(&semaphore_customer);
    sem_destroy(&semaphore_fb);

    return 0;
}

void *customers_function(void *arg)
{
    customer_ended = 0;
    customers_in++;

    /* one customer at a time*/
    pthread_mutex_lock(&customer_mutex);
    customer_ended = 0;
    customers_served++;
    sem_post(&semaphore_customer);
    sem_wait(&semaphore_chef);

    printf("customer : Got my food \n");
    printf("======================\n");

    if (customers_in == customers_served)
    {
        customer_ended = 1;
    }
    sem_post(&semaphore_fb);

    pthread_mutex_unlock(&customer_mutex);

    pthread_exit(NULL);
}

void *chef_function(void *arg)
{
    while (1)
    {
       
        sem_wait(&semaphore_fb);


        if (numberofcust == N)
        {
            printf("im closing the store\n");
            break;
        }



        Checkforfb();

        sem_wait(&semaphore_customer);

        printf("chef : food is ready \n");
        sem_post(&semaphore_chef);

        numberofcust++;
    }
}

void Checkforfb()
{
    if (customer_ended == 1)
    {
        printf("Chef : im on facebook\n");
        printf("----------------------\n");
    }
}
