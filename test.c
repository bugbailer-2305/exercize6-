#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ThreadArgs
{
  int *array_pos;
  int length;
};

void generate_r_array(int *r_array, int num_elements, int seed);
void *get_sum(int *array_pos, int length);
void *max(int *array, int length);

void threads_function(function_type func, int max_threads)
{
  pthread_t tids[max_threads + 1];
  int i, ids[max_threads + 1];

  /* Creating threads */
  for (i = 1; i <= max_threads; i++)
  {
    ids[i] = i;
    pthread_create(&tids[i], NULL, func, &ids[i]);
    printf("Thread 0 created thread %d\n", i);
  }

  /* Waiting for threads to finish */
  for (i = 1; i <= THREAD_CT; i++)
  {
    pthread_join(tids[i], NULL);
    printf("Thread 0 reaped thread %d\n", i);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int task = atoi(argv[0]);
  int seed = atoi(argv[1]);
  int num_elements = atoi(argv[2]);
  int threads = atoi(argv[3]);
  char print_results = atoi(argv[4]);
  pthread_t *thread_ids;
  int *r_array;
  int i = 0;

  printf("You've entered: \nTask: %d \nSeed: %d \nElement Number: %d \nThread "
         "Number: %d \nPrint "
         "Results: %c\n",
         task, seed, num_elements, threads, print_results);

  r_array = malloc(num_elements * sizeof(int));
  generate_r_array(r_array, num_elements, seed);

  for (i = 0; i < num_elements; i++)
  {
    printf("%d\n", r_array[i]);
  }
  free(r_array);
  return 0;
}

void generate_r_array(int *r_array, int num_elements, int seed)
{
  int i;

  srand(seed);

  for (i = 0; i < num_elements; i++)
  {
    r_array[i] = rand();
  }
}

void *get_sum(int *array_pos, int length)
{
  int i;
  int *sum = malloc(sizeof(int));

  *sum = 0;

  for (i = 0; i < length; i++)
  {
    *sum = (*sum + array_pos[i]) % 1000000;
  }

  return sum;
}

void *max(int *array, int length)
{
  int *max = malloc(sizeof(int));
  int i;
  *max = array[0];

  /* Iterate through the array and update max if a larger element is found*/
  for (i = 1; i < length; i++)
  {
    if (array[i] > *max)
    {
      *max = array[i];
    }
  }
  return max;
}
