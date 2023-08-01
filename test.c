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

int main()
{
  int *r_array;
  int num_elements;
  int threads;
  pthread_t *thread_ids;
  int seed;
  int task;
  char print_results;
  int i = 0;

  printf("Enter Tasks(1 for max, 2 for sum): ");
  scanf("%d", &task);

  printf("Enter Seed: ");
  scanf("%d", &seed);

  printf("Enter Number of elements: ");
  scanf("%d", &num_elements);

  printf("Enter Number of Threads: ");
  scanf("%d", &threads);

  printf("Print Results?(Y for yes)");
  scanf(" %c", &print_results);

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
