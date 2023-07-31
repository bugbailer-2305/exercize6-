#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ThreadArgs {
  int *array_pos;
  int length;
};

void generate_r_array(int *r_array, int num_elements, int seed);

int main(int argc, char *argv[]) {
  int task = atoi(argv[0]);
  int seed = atoi(argv[1]);
  int num_elements = atoi(argv[2]);
  int threads = atoi(argv[3]);
  char print_results = argv[4];
  pthread_t *thread_ids;
  int *r_array;
  int i = 0;

  printf("Enter Tasks(1 for max, 2 for sum): ");

  printf("Enter Seed: ");

  printf("Enter Number of elements: ");

  printf("Enter Number of Threads: ");

  printf("Print Results?(Y for yes)");

  printf("You've entered: \nTask: %d \nSeed: %d \nElement Number: %d \nThread "
         "Number: %d \nPrint "
         "Results: %c\n",
         task, seed, num_elements, threads, print_results);

  r_array = malloc(num_elements * sizeof(int));
  generate_r_array(r_array, num_elements, seed);

  for (i = 0; i < num_elements; i++) {
    printf("%d\n", r_array[i]);
  }
  free(r_array);
  return 0;
}

void generate_r_array(int *r_array, int num_elements, int seed) {
  int i;

  srand(seed);

  for (i = 0; i < num_elements; i++) {
    r_array[i] = rand();
  }
}
