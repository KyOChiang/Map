#include "unity.h"
#include "Map.h"
#include "Person.h"
#include "mock_Hash.h"
#include "mock_comparePerson.h"
#include "LinkedList.h"
#include "CustomAssert.h"
#include "CException.h"
#include "ErrorCode.h"

#define getPersonFromBucket(x) ((Person *)((List *)(x))->data)

void setUp(void){}

void tearDown(void){}

void test_mapNew_given_length_of_10_should_create_a_new_Map(){
	Map *map = mapNew(10);
  
  TEST_ASSERT_NOT_NULL(map);
  TEST_ASSERT_NOT_NULL(map->bucket);
  TEST_ASSERT_EQUAL(0,map->size);
  TEST_ASSERT_EQUAL(10,map->length);
}

void test_mapStore_given_Ali_should_add_it_to_map(){
  Person *person = personNew("Ali" , 23 , 64.0);
	Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  
  mapStore(map, person, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(person ,getPersonFromBucket(map->bucket[3]));
  
}

void test_mapStore_given_Ali_but_Ali_is_in_the_Map_should_throw_ERR_SAME_ELEMENT_exception(void){
  CEXCEPTION_T e;
  Person *person = personNew("Ali", 25, 70.3);
  List *list = listNew(person, NULL);
  Map *map = mapNew(5);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person, 3);
  comparePerson_ExpectAndReturn(person, person, 1);
  
  Try{
    mapStore(map, person, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT exception to be thrown.");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT,e);
    TEST_ASSERT_NOT_NULL(map->bucket[3]);
    TEST_ASSERT_EQUAL_Person(person ,getPersonFromBucket(map->bucket[3]));
  }

}

void test_mapStore_given_Zorro_with_hash_value_3_should_add_into_the_bucket(void){
  Person *person = personNew("Ali", 25, 70.3);
  Person *person2 = personNew("Zorro", 35, 75.3);
  Map *map = mapNew(5);
  List *list = listNew(person, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person2, 3);
  comparePerson_ExpectAndReturn(person, person2, 0);
  
  mapStore(map, person2, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(person ,getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_EQUAL_Person(person2 ,getPersonFromBucket(map->bucket[3]));
}

void test_mapFind_to_find_Ali_and_return_Ali(){
  Person *person = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  mapStore(map, person, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person(person ,getPersonFromBucket(map->bucket[3]));
  
  hash_ExpectAndReturn(person, 3);
  comparePerson_ExpectAndReturn(person, person, 1);
  
  findResult = mapFind(map, person, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person(person ,findResult);
}

void test_mapFind_to_find_Ali_and_return_NULL_if_Ali_not_in_the_map(){
  Person *person = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);

  findResult = mapFind(map, person, comparePerson, hash);
  TEST_ASSERT_NULL(findResult);
}







