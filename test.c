#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

// This code is designed to test the correctness of your implementation. 
// You do not need to significantly change it. 
// Compile and run it in the command line by typing: 
// make test; ./test

int main(void) {

  hashtable* ht=NULL;
  int num_tests = 20;
  allocate(&ht, num_tests);

  int seed = 1;
  srand(seed);
  keyType keys[num_tests];
  valType values[num_tests];

  printf("Testing putting and getting from the hash table.\n");
  printf("Inserting %d key-value pairs.\n", num_tests);
  for (int i = 0; i < num_tests; i += 1) {
    keys[i] = rand();
    values[i] = rand();
    put(ht, keys[i], values[i]);
    printf("\t(%d -> %d) \n", keys[i], values[i]);
  }

  int num_values = 1;
  int results[num_values];
  int* num_results = NULL;

  for (int i = 0; i < num_tests; i += 1) {
    int index = rand() % num_tests;
    keyType target_key = keys[index];
    get(ht, target_key, results, num_values, num_results);
    if (results[0] != values[index]) {
      printf("Test failed with key %d. Got value %d. Expected value %d.\n", target_key, results[0], values[index]);
      return 1;
    } 
  }

  printf("Passed tests for putting and getting.\n");
  printf("Now testing erasing.\n");

  for (int i = 0; i < num_tests; i += 1) {
    keyType target_key = keys[i];
    erase(ht, target_key);
    get(ht, target_key, results, num_values, num_results);
    if ((*num_results) != 0) {
      printf("Test failed with key %d. Expected it to be erased, but got %d matches.\n", target_key, *num_results);
      return 1;
    } 
  }
  deallocate(ht);
  printf("Passed tests for erasing.\n");
  printf("All tests have been successfully passed.\n");
  return 0;
}
