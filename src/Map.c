#include <stdio.h>
#include <malloc.h>
#include "Map.h"
#include "LinkedList.h"
#include "Person.h"
#include "comparePerson.h"
#include "ErrorCode.h"

Map *mapNew(int length){
  Map *map = malloc(sizeof(Map));
  
  map->bucket = calloc(sizeof(void *),length);
  map->length = length;
  map->size = 0;
  
  return map;
}

void mapLinearStore(Map *map, void *element, int(*compare)(void *, void*), unsigned int (*hash)(void*)){
  int index, bufferLength, hashValue;
  index = hash(element);
  hashValue = index;
  
  if(map != NULL){
    bufferLength = map->length;
    while(map->bucket[index] != NULL){
      if(compare(map->bucket[index],element))
        Throw(ERR_SAME_ELEMENT);
      index = index + 1;
      if(index >= bufferLength)
        Throw(ERR_BUCKET_FULL);
    }
    map->bucket[index] = element;
    if(map->bucket[index-1] == NULL && index > 0){
      map->bucket[index-1] == (void *)-1;
    }
  }
  // printf("%d\n", hashValue);
  // printf("%d\n", isBucketEmpty(map->bucket[1]));
  // printf("%d\n", isBucketEmpty(map->bucket[3]));
}

/*  mapLinearFind
 *  ----------------------
 *  if NULL, check mark 
 *  ----------------------
 *  if got mark, go next   <------------+
 *  Otherwise, return NULL              |
 *  ----------------------              |
 *  compare, both match?                |
 *  yes, return. Otherwise, check mark -+
 */

void *mapLinearFind(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  Person *searchPerson = NULL;
  int index, bufferLength;
  index = hash(element);
  bufferLength = map->length;
  
  if(isBucketEmpty(map->bucket[index])&&(isBucketMarked(map->bucket[index]) == 0))
    return NULL;
  
  if(isBucketEmpty(map->bucket[index])){ //NULL
    if(isBucketMarked(map->bucket[index])){ //MARKED
      index = index + 1;
      if(index > bufferLength)
        Throw(ERR_OUT_OF_BOUND);
    }
    if(compare(map->bucket[index], element) == 1){ // element in next index not the same
      searchPerson = (Person *)(map->bucket[index]);
      return searchPerson;
    }
    return NULL;
  }
  else{ // map->bucket[index] != NULL
    while(compare(map->bucket[index], element) == 0){ // Compare and not match
      index = index + 1;
      if(index > bufferLength)
        Throw(ERR_OUT_OF_BOUND);
    }
    searchPerson = (Person *)(map->bucket[index]);
    return searchPerson;
  }
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

/* mapFind -> To find person in map.
 *  Is NULL? Yes, return NULL. Otherwise, compare
 *    (a) Yes, return person
 *    Otherwise, check next is NULL?
 *      Yes, return NULL
 *      Otherwise, compare and repeat step (a)
 */

void *mapFind(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  Person *searchPerson = NULL;
  int index; List *nextList;
  index = hash(element);
  
  if(((List *)map->bucket[index]) == NULL){ // if bucket is NULL
    return NULL;
  }
  else{ // if bucket not NULL
    if(compare( ((List *)map->bucket[index])->data,element) == 1){ // if Person found
      searchPerson = (Person *)(((List *)map->bucket[index])->data);
      // printf("Person found! %s\n",((Person *)(((List *)map->bucket[index])->data))->name);
    }
    else{ //if Person not found
      nextList = (((List *)map->bucket[index])->next);
      while(nextList != NULL){ // if there is nextList after List
        if(compare(nextList->data,element) == 1){
          searchPerson = (Person *)(nextList->data);
          // printf("Person found! %s\n",searchPerson->name);
          return searchPerson;
        }
        nextList = nextList->next;
      }
    }
  }
  
  return searchPerson;
}

/*
 *  Remove
 *  Hash
 *  Check bucket is null or mark
 *  If null and no mark, return NULL
 *  Otherwise, compare
 *
 *  Correct, return remove out of bound
 *  otherwise, index + 1
 */

void *mapLinearRemove(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  Person *removePerson = NULL;
  int index, bufferLength;
  index = hash(element);
  if(isBucketEmpty(map->bucket[index])&&(isBucketMarked(map->bucket[index]) == 0))
    return NULL;
  else{  
    bufferLength = map->length;
    if(isBucketMarked(map->bucket[index])){
      index = index + 1;
      if(index > bufferLength)
        Throw(ERR_OUT_OF_BOUND);
    }
    if(compare(map->bucket[index], element) == 1){
      removePerson = map->bucket[index];
      map->bucket[index]=NULL;
      if(isBucketEmpty(map->bucket[index-1])){
        map->bucket[index-1] = NULL;
      }
      return removePerson;
    }
    return NULL;
  }
}

void *mapRemove(Map *map, void *element, int(*compare)(void *, void*),unsigned int (*hash)(void*)){
  Person *removePerson = NULL;
  int index; List *nextList, *tempList;
  index = hash(element);
  
  if(((List *)map->bucket[index]) == NULL){ // if bucket is NULL
    return NULL;
  }
  else{ // if bucket not NULL
    if(compare( ((List *)map->bucket[index])->data,element) == 1){ // if Person found
      removePerson = (Person *)(((List *)map->bucket[index])->data);
      printf("Remove person found! %s\n",removePerson->name);
      ((List *)map->bucket[index])->data = NULL;
      return removePerson;
    }
    else{ //if Person not found
      tempList = ((List *)map->bucket[index]);
      nextList = (((List *)map->bucket[index])->next);
      while(nextList != NULL){ // if there is nextList after List
        if(compare(nextList->data,element) == 1){
          removePerson = (Person *)(nextList->data);
          // printf("%p\n",nextList);
          // printf("%p\n",nextList->next);
          if(nextList->next != NULL)
            tempList->next = nextList->next;
          else
            nextList = NULL;
          printf("Remove person found! %s\n",removePerson->name);
          return removePerson;
        }
        tempList = nextList;
        nextList = nextList->next;
      }
    }
  }
  
  return removePerson;
}







