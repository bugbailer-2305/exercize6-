#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

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

void generate_r_array(Thread_struct *s, int seed);
void *get_sum(void *s);
void *max(void *s);

void threads_sum_function(int max_threads, Thread_struct *s)
{
  pthread_t *tids = malloc((max_threads + 1) * sizeof(pthread_t));
  Thread_struct *struc_array = malloc((max_threads + 1) * sizeof(Thread_struct));
  int part_array = s->length / max_threads;
  int remainder_to_add = max_threads - (s->length % max_threads);
  int displacement_variable = 0;
  int i, j;
  Thread_struct *final = malloc(sizeof(Thread_struct));
  final->array = malloc((max_threads) * sizeof(int));
  final->length = max_threads;
  for (i = 1; i <= max_threads; i++)
  {
    Thread_struct *x = malloc(sizeof(Thread_struct));
    x->array = malloc((part_array + 1) * sizeof(int));
    x->length = part_array;
    for (j = 1; j <= part_array; j++)
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
  for (i = 1; i <= max_threads; i++)
  {
    final->array[i - 1] = struc_array[i].sum;
  }
  get_sum(final);
  printf("value of sum bby threads %d", final->sum);
  free(final->array);
  free(final);
  free(struc_array);
  free(tids);
}

void threads_max_function(int max_threads, Thread_struct *s)
{
  pthread_t *tids = malloc((max_threads + 1) * sizeof(pthread_t));
  Thread_struct *struc_array = malloc((max_threads + 1) * sizeof(Thread_struct));
  int part_array = s->length / max_threads;
  int remainder_to_add = max_threads - (s->length % max_threads);
  int displacement_variable = 0;
  int i, j;
  Thread_struct *final = malloc(sizeof(Thread_struct));
  final->array = malloc((max_threads) * sizeof(int));
  final->length = max_threads;
  for (i = 1; i <= max_threads; i++)
  {
    Thread_struct *x = malloc(sizeof(Thread_struct));
    x->array = malloc((part_array + 1) * sizeof(int));
    x->length = part_array;
    for (j = 1; j <= part_array; j++)
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
  for (i = 1; i <= max_threads; i++)
  {
    final->array[i - 1] = struc_array[i].sum;
  }
  max(final);
  printf("value of sum bby threads %d", final->max);
  free(final->array);
  free(final);
  free(struc_array);
  free(tids);
}

int main(int argc, char *argv[])
{
  int task = atoi(argv[0]);
  int seed = atoi(argv[1]);
  /*int num_elements = atoi(argv[2]);*/
  int threads = atoi(argv[3]);
  char print_results = atoi(argv[4]);
  pthread_t *thread_ids;
  /*int *r_array;*/
  int i = 0;
  Thread_struct *s = malloc(sizeof(Thread_struct));
  s->length = atoi(argv[2]);

  printf("You've entered: \nTask: %d \nSeed: %d \nElement Number: %d \nThread "
         "Number: %d \nPrint "
         "Results: %c\n",
         task, seed, s->length, threads, print_results);

  s->array = malloc(s->length * sizeof(int));
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
  s->max = 0;
  printf("sum is %d", s->sum);
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

void *get_sum(void *s)
{
  int i;
  int *sum = malloc(sizeof(int));

  *sum = 0;

  for (i = 0; i < ((Thread_struct *)s)->length; i++)
  {
    *sum = (*sum + ((Thread_struct *)s)->array[i]) % 1000000;
  }

  ((Thread_struct *)s)->sum = *sum;
}

void *max(void *s)
{
  int *max = malloc(sizeof(int));
  int i;
  *max = ((Thread_struct *)s)->array[0];

  /* Iterate through the array and update max if a larger element is found*/
  for (i = 1; i < ((Thread_struct *)s)->length; i++)
  {
    if (((Thread_struct *)s)->array[i] > *max)
    {
      *max = ((Thread_struct *)s)->array[i];
    }
  }
  ((Thread_struct *)s)->max = *max;
}
