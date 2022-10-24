#ifndef MERGESORT_H_GUARD
#define MERGESORT_H_GUARD

#include <stdbool.h>

#define UNIT_TESTING

void mergesort(int size, int values[]);

void mergesort_range(int start_index, int end_index, int[] values);

void merge_ranges(int start_index, int midpoint, int end_index, int values[]);

#endif
