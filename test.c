#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ThreadArgs
{
  int *array_pos;
  int length;
};
typedef struct thread_struct
{
  int *array;
  int length;
  int sum;
  int max;

} Thread_struct;

void generate_r_array(int *r_array, int num_elements, int seed);
void *get_sum(Thread_struct *s);
void *max(Thread_struct *s);

void threads_sum_function(int max_threads, Thread_struct *s)
{
  pthread_t tids = malloc((max_threads + 1) * sizeof(pthread_t));
  Thread_struct struc_array = malloc((max_threads + 1) * sizeof(Thread_struct));
  int part_array = s->length / max_threads;
  int remainder_to_add = max_threads - (s->length % max_threads);
  int displacement_variable = 0;
  for (i = 0; i < max_threads; i++)
  {
    Thread_struct *x = malloc(sizeof(Thread_struct));
    x->array = malloc(part_array * sizeof(int));
    x->length = part_array;
    for (j = 0; j < part_array; j++)
    {
      if ((j + displacement_variable) < s->length)
      {
        x->array[j] = s->array[j + displacement_variable];
      }
      else
      {
        x->array[j] = 0;
      }
    }
    struc_array[i] = *x;
    displacement_variable += part_array;
  }

  /* Creating threads */
  for (i = 1; i <= max_threads; i++)
  {

    pthread_create(&tids[i], NULL, get_sum, &struc_array[i]);
    printf("Thread 0 created thread %d\n", i);
  }

  /* Waiting for threads to finish */
  for (i = 1; i <= max_threads; i++)
  {
    pthread_join(tids[i], NULL);
    printf("Thread 0 reaped thread %d\n", i);
  }
  free(x->array);
  free(x);
  free(struc_array);
  free(tids);

  return 0;
}

void threads_max_function(int max_threads, Thread_struct *s)
{
  pthread_t tids = malloc((max_threads + 1) * sizeof(pthread_t));
  Thread_struct struc_array = malloc((max_threads + 1) * sizeof(Thread_struct));
  int part_array = s->length / max_threads;
  int remainder_to_add = max_threads - (s->length % max_threads);
  int displacement_variable = 0;
  for (i = 0; i < max_threads; i++)
  {
    Thread_struct *x = malloc(sizeof(Thread_struct));
    x->array = malloc(part_array * sizeof(int));
    x->length = part_array;
    for (j = 0; j < part_array; j++)
    {
      if ((j + displacement_variable) < s->length)
      {
        x->array[j] = s->array[j + displacement_variable];
      }
      else
      {
        x->array[j] = 0;
      }
    }
    struc_array[i] = *x;
    displacement_variable += part_array;
  }

  /* Creating threads */
  for (i = 1; i <= max_threads; i++)
  {

    pthread_create(&tids[i], NULL, max, &struc_array[i]);
    printf("Thread 0 created thread %d\n", i);
  }

  /* Waiting for threads to finish */
  for (i = 1; i <= max_threads; i++)
  {
    pthread_join(tids[i], NULL);
    printf("Thread 0 reaped thread %d\n", i);
  }
  free(x->array);
  free(x);
  free(struc_array);
  free(tids);

  return 0;
}

int main(int argc, char *argv[])
{
  s->length = atoi(argv[2]);
  int task = atoi(argv[0]);
  int seed = atoi(argv[1]);
  /*int num_elements = atoi(argv[2]);*/
  int threads = atoi(argv[3]);
  char print_results = atoi(argv[4]);
  pthread_t *thread_ids;
  /*int *r_array;*/
  int i = 0;

  printf("You've entered: \nTask: %d \nSeed: %d \nElement Number: %d \nThread "
         "Number: %d \nPrint "
         "Results: %c\n",
         task, seed, s->length, threads, print_results);

  s->array = malloc(num_elements * sizeof(int));
  generate_r_array(s, seed);

  for (i = 0; i < s->length; i++)
  {
    printf("%d\n", s->array[i]);
  }

  printf("sum is %d", s->sum);
  printf("max is %d", s->max);

  max(s);
  get_sum(s);

  printf("sum is %d", s->sum);
  printf("max is %d", s->max);

  /*------------------------------------------------------------*/
  s->sum = 0;
  s->max = 0 printf("sum is %d", s->sum);
  printf("max is %d", s->max);

  free(s->array);
  free(s);
  return 0;
}

void generate_r_array(Thread_struct *s, int seed)
{
  int i;

  srand(seed);

  for (i = 0; i < s->length; i++)
  {
    s->array[i] = rand();
  }
}

void *get_sum(Thread_struct *s)
{
  int i;
  int *sum = malloc(sizeof(int));

  *sum = 0;

  for (i = 0; i < s->length; i++)
  {
    *sum = (*sum + s->array[i]) % 1000000;
  }

  s->sum = sum;
}

void *max(Thread_struct *s)
{
  int *max = malloc(sizeof(int));
  int i;
  *max = s->array[0];

  /* Iterate through the array and update max if a larger element is found*/
  for (i = 1; i < s->length; i++)
  {
    if (s->array[i] > *max)
    {
      *max = s->array[i];
    }
  }
  s->max = max;
}
