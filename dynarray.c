/*
 * This file contains a simple implementation of a dynamic array.  See the
 * documentation below for more information on the individual functions in
 * this implementation.
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"

/*
 * This structure is used to represent a single dynamic array.
 */
struct dynarray {
  void** data;
  int size;
  int capacity;
  int start; //Track the logical start of the circular buffer
};

#define DYNARRAY_INIT_CAPACITY 4

/*
 * This function allocates and initializes a new, empty dynamic array and
 * returns a pointer to it.
 */
struct dynarray* dynarray_create() {
  struct dynarray* da = malloc(sizeof(struct dynarray));
  assert(da);

  da->data = malloc(DYNARRAY_INIT_CAPACITY * sizeof(void*));
  assert(da->data);
  da->size = 0;
  da->capacity = DYNARRAY_INIT_CAPACITY;
  da->start = 0;

  return da;
}

/*
 * This function frees the memory associated with a dynamic array.  Freeing
 * any memory associated with values stored in the array is the responsibility
 * of the caller.
 *
 * Params:
 *   da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da) {
  assert(da);
  free(da->data);
  free(da);
}

/*
 * This function returns the size of a given dynamic array (i.e. the number of
 * elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da) {
  assert(da);
  return da->size;
}


/*
 * Auxilliary function to perform a resize on a dynamic array's underlying
 * storage array.
 */
void _dynarray_resize(struct dynarray* da, int new_capacity) {
  assert(new_capacity > da->size);

  /*
   * Allocate space for the new array.
   */
  void** new_data = malloc(new_capacity * sizeof(void*));
  assert(new_data);

  /*
   * Copy data from the old array to the new one.
   */
  for (int i = 0; i < da->size; i++) {
    int index = (da->start + i) % da->capacity;  //
    new_data[i] = da->data[index];
  }

  /*
   * Put the new array into the dynarray struct.
   */
  free(da->data);
  da->data = new_data;
  da->capacity = new_capacity;
  da->start = 0;
}

/*
 * This function inserts a new value to a given dynamic array.  The new element
 * is always inserted at the *end* of the array.
 *
 * Params:
 *   da - the dynamic array into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val) {
  assert(da);

  /*
   * Make sure we have enough space for the new element.  Resize if needed.
   */
  if (da->size == da->capacity) { //change from capacity to capacity * 2
    _dynarray_resize(da, 2 * da->capacity);
  }

  /*
   * Put the new element at the end of the array.
   */
    int physical = (da->start + da->size) % da->capacity;  //formulation:(start + logical) % capacity
    da->data[physical] = val;
    da->size = da->size + 1;
}


/*
 * This function returns the value of an existing element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array from which to get a value.  May not be NULL.
 *   idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  int physical_index = (da->start + idx) % da->capacity;
  return da->data[physical_index];
}

/*
 * This function updates (i.e. overwrites) the value of an existing element in
 * a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  int physical_index = (da->start + idx) % da->capacity;
  free(da->data[physical_index]);
  da->data[physical_index] = val;
}


/*Additional functuion
 * This function get the value stored at the front of the dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 * 
 * Return:
 *   Returns the value at the logical start of the array.
 */
void* dynarray_get_front(struct dynarray* da) {
    int front_index = da->start;
    return da->data[front_index];
}


/*Additional 
 * This function remove the front value from the dynamic array by incrementing
 * the start index, advancing the logical front of the array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *     
 */
void dynarray_remove_front(struct dynarray* da) {
    da->start = (da->start + 1) ;  // start + 1 
    da->size--;  
}
