#ifndef Map_H
#define Map_H
#include <stdio.h>

#define isBucketEmpty(x) ((x) == NULL||(x) == (void *)-1)
#define isBucketMarked(x) ((x) == (void *)-1)

typedef struct Map Map;

/*    Separate chaining
 *   ---------------------
 *   |0|1|2|3|4|5|6|7|8|9|          < length is 10(no of bucket)
 *   ---------------------          < size is no of buckets occupy by element
 *    |                             < noOfElement is the total no of list under the map (not the bucket)
 *   (List)-+
 *     |    |
 *   (data) |
 *          |
 *   (List)-+
 *     |    |
 *   (data) |
 *        .....
 */


struct Map{
  void **bucket;
  int length; // Total no buckets
  int size;   // No of buckets used
};
Map *mapNew(int length);

// Implementing separate chaining method
void mapStore(Map *map, void *element, int(*compare)(void *, void*),
              unsigned int (*hash)(void*));

void *mapFind(Map *map, void *element, int(*compare)(void *, void*),
              unsigned int (*hash)(void*));

void *mapRemove(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*));

// Implementing linear probing method              
void mapLinearStore(Map *map, void *element, int(*compare)(void *, void*),
                    unsigned int (*hash)(void*));
             
void *mapLinearFind(Map *map, void *element, int(*compare)(void *, void*),
                    unsigned int (*hash)(void*));

void *mapLinearRemove(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*));
#endif // Map_H
