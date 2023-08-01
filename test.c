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

void threads_function(function_type func, int max_threads, Thread_struct *s)
{
  pthread_t tids[max_threads + 1];
  int i, j, ids[max_threads + 1];
  Thread_struct struc_array[max_threads + 1];
  int part_array = s->length / max_threads;
  int remainder_to_add = max_threads - (s->length % max_threads);
  int displacement_variable = 0;
  for (i = 1; i <= max_threads; i++)
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
    free(x->array);
    free(x);
  }

  /* Creating threads */
  for (i = 1; i <= max_threads; i++)
  {

    pthread_create(&tids[i], NULL, func, &struc_array[i]);
    printf("Thread 0 created thread %d\n", i);
    displacement_variable += part_array;
  }

  /* Waiting for threads to finish */
  for (i = 1; i <= max_threads; i++)
  {
    pthread_join(tids[i], NULL);
    printf("Thread 0 reaped thread %d\n", i);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  Thread_struct *s = malloc(sizeof(Thread_struct));
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
         task, seed, num_elements, threads, print_results);

  s->array = malloc(num_elements * sizeof(int));
  generate_r_array(s, seed);

  for (i = 0; i < num_elements; i++)
  {
    printf("%d\n", r_array[i]);
  }
  free(r_array);
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
