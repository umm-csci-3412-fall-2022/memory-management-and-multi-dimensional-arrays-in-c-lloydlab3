#include <gtest/gtest.h>
#include <stdlib.h>

#include "array_merge.h"
#include "../mergesort/mergesort.h"

void arrays_match(int size, int a[], int b[]) {
  int i;

  for (i=0; i<size; ++i) {
    EXPECT_EQ(b[i], a[i]);
  }
}

TEST(ArrayMerge, reallocate_does_what_I_think_it_does) {
  int* a = (int*) calloc(5, sizeof(int));
  for(int i=0; i<5; i++) {
    a[i] = i+1;
  }
  a = (int*) realloc(a, 6*sizeof(int));
  a[5] = 0;
  int expected[] = {1,2,3,4,5,0};
  arrays_match(6, a, expected);
  free(a);
}


TEST(ArrayMerge, unique_entries) {
  int a[] = {543254, -12313, 0, 1, 817753, 1, 3, 1, 3, 1, 5, 1, -55773};
  int* result = get_unique_entries(13, a);
  int expected[] = {8, 543254, -12313, 0, 1, 817753, 3, 5, -55773};
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_empty_list) {
  int* a[] = { };
  int sizes[] = { };
  int expected[] = { 0 };
  int* result;

  result = array_merge(0, sizes,  a);
  arrays_match(1, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_singleton_list) {
  int num_arrays = 1;
  int sizes[] = { 1 };
  int a0[] = { 5 };
  int* a[] = { a0 };
  int expected[] = { 1, 5 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(2, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_non_duplicate_list) {
  int num_arrays = 3;
  int sizes[] = { 3,3,3 };
  int a0[] = { 1, 2, 3 };
  int a1[] = { 4, 5, 6 };
  int a2[] = { 7, 8, 9 };
  int* a[] = { a0,a1,a2 };
  int expected[] = { 9, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(2, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_one_longer_list) {
  int num_arrays = 1;
  int sizes[] = { 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int* a[] = { a0 };
  int expected[] = { 7, 0, 2, 3, 5, 6, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_multiple_copies_of_longer_list) {
  int num_arrays = 10;
  int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  int a0[] = { 3, 2, 0, 5, 8, 9, 6, 3, 2, 0 };
  int* a[] = { a0, a0, a0, a0, a0, a0, a0, a0, a0, a0 };
  int expected[] = { 7, 0, 2, 3, 5, 6, 8, 9 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(8, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_multiple_copies_of_longer_list_different_orders) {
  int num_arrays = 9;
  int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  int a0[] = { 3, -22345, 0, 5, 8, 9, 6, 3, 2, 0 };
  int a1[] = { 5, 8, 9, 3, 2, 0, 6, 378293, 2, 0 };
  int a2[] = { 8, -52857, 0, 2, 3, 0, 2, 3, 6, 9 };
  int* a[] = { a0, a2, a1, a0, a2, a1, a1, a0, a2 };
  int expected[] = { 10, -52857, -22345, 0, 2, 3, 5, 6, 8, 9, 378293 };
  int* result;

  result = array_merge(num_arrays, sizes, a);
  arrays_match(11, result, expected);
  free(result);
}

TEST(ArrayMerge, Handle_different_sizes) {
  int num_arrays = 11;
  int sizes[num_arrays];
  int* a[num_arrays];
  int expected[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int* result;
  int i, j;

  for (i=0; i<num_arrays; ++i) {
    sizes[i] = i;
    a[i] = (int*) calloc(i, sizeof(int));
    for (j=0; j<i; ++j) {
      a[i][j] = j;
    }
  }

  result = array_merge(num_arrays, sizes, a);
  arrays_match(11, result, expected);
  free(result);
  for(int i=0; i<num_arrays; i++) {
    free(a[i]);
  }
}

TEST(ArrayMerge, Handle_different_sizes_reversed) {
  int num_arrays = 11;
  int sizes[num_arrays];
  int* a[num_arrays];
  int expected[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int* result;
  int i, j;

  for (i=num_arrays-1; i>=0; --i) {
    sizes[i] = i;
    a[i] = (int*) calloc(i, sizeof(int));
    for (j=0; j<i; ++j) {
      a[i][j] = j;
    }
  }

  result = array_merge(num_arrays, sizes, a);
  arrays_match(11, result, expected);
  free(result);
  for(int i=0; i<num_arrays; i++) {
    free(a[i]);
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
