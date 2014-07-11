#include <stdio.h>
#include <malloc.h>
#include "Map.h"
#include "LinkedList.h"
#include "Person.h"
#include "ErrorCode.h"

// #define personGetFromBucket(x) ((List *)(x))->data

Map *mapNew(int length){
  Map *map = malloc(sizeof(Map));
  
  map->bucket = calloc(sizeof(void *),length);
  map->length = length;
  map->size = 0;
  
  return map;
}

void mapStore(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  int index;
  
  index = hash(element);
  List *list = listAdd(element, NULL);
  
  if(((List *)map->bucket[index]) == NULL)
    map->bucket[index] = (void *) list;
  else if(compare( ((List *)map->bucket[index])->data,element) == 1)
    Throw(ERR_SAME_ELEMENT);
}

void *mapFind(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  return NULL;
}
