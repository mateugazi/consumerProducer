#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define SizeOfBuffer 5

sem_t emptySlots;
sem_t fullSlots;
int indexProduce = 0;
int indexConsume = 0;
int numberOfMaxItems;
int numberOfProducers;
int numberOfConsumers;
int buffer[SizeOfBuffer];
pthread_mutex_t muteksior;

void *consumerMethod(void *consumeNumber)
{
  for (int i = 0; i < numberOfMaxItems; i++)
  {
    sem_wait(&fullSlots);
    pthread_mutex_lock(&muteksior);
    int item = buffer[indexConsume];
    printf("Consumer number:%d is now consuming the item nr:%d from the slot number:%d\n", *((int *)consumeNumber), item, indexConsume);
    indexConsume = (indexConsume + 1) % SizeOfBuffer;
    pthread_mutex_unlock(&muteksior);
    sem_post(&emptySlots);
  }
}

void *producerMethod(void *produceNumber)
{
  int item;
  for (int i = 0; i < numberOfMaxItems; i++)
  {
    item = rand();
    sem_wait(&emptySlots);
    pthread_mutex_lock(&muteksior);
    buffer[indexProduce] = item;
    printf("Producer number:%d is now producing the item number:%d at the slot number:%d\n", *((int *)produceNumber), buffer[indexProduce], indexProduce);
    indexProduce = (indexProduce + 1) % SizeOfBuffer;
    pthread_mutex_unlock(&muteksior);
    sem_post(&fullSlots);
  }
}

int main()
{
  printf("Number of max items\n");
  scanf("%d", &numberOfMaxItems);
  printf("Number of consumers\n");
  scanf("%d", &numberOfConsumers);
  printf("Number of producers\n");
  scanf("%d", &numberOfProducers);

  if (numberOfProducers * numberOfMaxItems - SizeOfBuffer > numberOfConsumers * numberOfMaxItems)
  {
    printf("You put the wrong values - the are not enought consumers to consume producers products");
  }
  else if (numberOfConsumers * numberOfMaxItems > numberOfProducers * numberOfMaxItems)
  {
    printf("You put the wrong values - producers won't fullfill the consumer's needs");
  }
  else
  {
    pthread_t producer[numberOfProducers];
    pthread_t consumer[numberOfConsumers];

    pthread_mutex_init(&muteksior, NULL);

    sem_init(&emptySlots, 0, SizeOfBuffer);
    sem_init(&fullSlots, 0, 0);

    int displayConsumer[numberOfConsumers];
    int displayProducer[numberOfProducers];

    for (int i = 0; i < numberOfProducers; i++)
    {
      displayConsumer[i] = i + 1;
    }

    for (int i = 0; i < numberOfProducers; i++)
    {
      displayProducer[i] = i + 1;
    }

    for (int i = 0; i < numberOfConsumers; i++)
    {
      pthread_create(&consumer[i], NULL, (void *)consumerMethod, (void *)&displayConsumer[i]);
    }

    for (int i = 0; i < numberOfProducers; i++)
    {
      pthread_create(&producer[i], NULL, (void *)producerMethod, (void *)&displayProducer[i]);
    }

    for (int i = 0; i < numberOfConsumers; i++)
    {
      pthread_join(consumer[i], NULL);
    }

    for (int i = 0; i < numberOfProducers; i++)
    {
      pthread_join(producer[i], NULL);
    }

    pthread_mutex_destroy(&muteksior);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
  }

  return 0;
}