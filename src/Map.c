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
  List * list;
  index = hash(element);
  
  
  if(((List *)map->bucket[index]) == NULL){
    list = listAdd(element, NULL);
    map->bucket[index] = (void *) list;
  }
  else{
    if(compare( ((List *)map->bucket[index])->data,element) == 1)
      Throw(ERR_SAME_ELEMENT);
    else{
      list = listAdd(element,((List *)map->bucket[index]));
      map->bucket[index] = (void *) list;
    }
  }
}

void *mapFind(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  return NULL;
}
