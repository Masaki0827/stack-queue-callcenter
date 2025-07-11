/*
 * This file contains the definition of the interface for a dynamic array.
 * You can find descriptions of the dynamic array functions, including their
 * parameters and their return values, in dynarray.c.
 */

#ifndef __DYNARRAY_H
#define __DYNARRAY_H

/*
 * Structure used to represent a dynamic array.  You may not change the fact
 * that only a forward declaration of the dynamic array structure is included
 * here.  In other words, you can't define the fields of the struct here.
 */
struct dynarray;

/*
 * Dynamic array interface function prototypes.  Refer to dynarray.c for
 * documentation about each of these functions.
 */
struct dynarray* dynarray_create();
void dynarray_free(struct dynarray* da);
int dynarray_size(struct dynarray* da);
void dynarray_insert(struct dynarray* da, void* val);
//void dynarray_remove(struct dynarray* da, int idx);  //dynarray_remove_front is used
void* dynarray_get(struct dynarray* da, int idx);
void dynarray_set(struct dynarray* da, int idx, void* val);
void* dynarray_get_front(struct dynarray* da);
void dynarray_remove_front(struct dynarray* da);


#endif
