#include "array_merge.h"
#include "../mergesort/mergesort.h"
#include <stdlib.h>

int* array_merge(int num_arrays, int* sizes, int** values) {
  int num_entries = 0;
  for(int i=0; i<num_arrays; i++) {
    num_entries += sizes[i];
  }
  int* combined_arr = (int*) calloc(num_entries, sizeof(int));

  int position_in_combined_arr = 0;
  for(int i=0; i<num_arrays; i++) {
    for(int j=0; j<sizes[i]; j++) {
      combined_arr[position_in_combined_arr] = values[i][j];
      position_in_combined_arr++;
    }
  }
  int* result = get_unique_entries(num_entries, combined_arr);
  free(combined_arr);
  mergesort_range(1, result[0]+1, result);
  return result;
}

int* get_unique_entries(int size, int* entries) {
  int* result = (int*) calloc(0, sizeof(int));
  int num_of_unique_entries = 0;
  for(int i=0; i<size; i++) {
    bool alreadyFound = false;
    for(int j=0; j<num_of_unique_entries; j++) {
      if(result[j] == entries[i]) {
        alreadyFound = true;
      }
    }
    if(!alreadyFound) {
      num_of_unique_entries++;
      result = (int*) realloc(result, num_of_unique_entries * sizeof(int));
      result[num_of_unique_entries-1] = entries[i];
    }
  }
  result = (int*) realloc(result, (num_of_unique_entries+1)*sizeof(int));
  for(int i=num_of_unique_entries; i>0; i--) {
    result[i] = result[i-1];
  }
  result[0] = num_of_unique_entries;
  return result;
}
