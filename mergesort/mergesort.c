#include "mergesort.h"
#include <stdlib.h>

void mergesort(int size, int* values) {
  mergesort_range(0, size, values);
}

void mergesort_range(int start_index, int end_index, int* values) {
  if((end_index - start_index) >= 2) {
    int midpoint = (start_index + end_index)/2;
    mergesort_range(start_index, midpoint, values);
    mergesort_range(midpoint, end_index, values);
    merge_ranges(start_index, midpoint, end_index, values);
  }
}

void merge_ranges(int start_index, int midpoint, int end_index, int* values) {
  int range_size = end_index - start_index;
  int* destination = (int*) calloc(range_size, sizeof(int));
  int first_index = start_index;
  int second_index = midpoint;
  int copy_index = 0;
  while(first_index < midpoint && second_index < end_index) {
    if(values[first_index] < values[second_index]) {
      destination[copy_index] = values[first_index];
      first_index++;
    } 
    else {
      destination[copy_index] = values[second_index];
      second_index++;
    }
    copy_index++;
  }
  while(first_index < midpoint) {
    destination[copy_index] = values[first_index];
    copy_index++;
    first_index++;
  }
  while(second_index < end_index) {
    destination[copy_index] = values[second_index];
    copy_index++;
    second_index++;
  }
  for(int i=0; i<range_size; i++) {
    values[i + start_index] = destination[i];
  }
  free(destination);
}
