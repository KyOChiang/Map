#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum{
  ERR_NO_ERROR,
  ERR_SAME_ELEMENT,
  ERR_BUCKET_FULL,
  ERR_OUT_OF_BOUND
}ErrorCode;

#endif

// while(isBucketMarked(map->bucket[index]) == 1){ // bucket[index] is mark with -1
      // if(compare(map->bucket[index + 1], element)){ // Compare next bucket and it match
        // searchPerson = (Person *)(map->bucket[index]);
        // return searchPerson;
      // }
      // index = index + 1;  // Compare but not match, 
      // if(index > bufferLength)
        // Throw(ERR_BUCKET_FULL);
    // }