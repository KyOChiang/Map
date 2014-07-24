#include "unity.h"
#include "Map.h"
#include "Person.h"
#include "mock_Hash.h"
#include "comparePerson.h"
#include "LinkedList.h"
#include "CustomAssert.h"
#include "CException.h"
#include "ErrorCode.h"

#define getPersonFromBucket(x) ((Person *)((List *)(x))->data)



void setUp(void){}
void tearDown(void){}

///////////////////////////////
//    mapNew
//////////////////////////////
void test_mapNew_given_length_of_10_should_create_a_new_Map(){
	Map *map = mapNew(10);
  
  TEST_ASSERT_NOT_NULL(map);
  TEST_ASSERT_NOT_NULL(map->bucket);
  TEST_ASSERT_EQUAL(0,map->size);
  TEST_ASSERT_EQUAL(10,map->length);
}

///////////////////////////////
//    mapStore
//////////////////////////////
void test_mapStore_given_Ali_should_add_it_to_map(){
  Person *Ali = personNew("Ali" , 23 , 64.0);
	Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Ali, 3);
  
  mapStore(map, Ali, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person("Ali", 23, 64.0, getPersonFromBucket(map->bucket[3])); 
}

void test_mapStore_given_Ali_but_Ali_is_in_the_Map_should_throw_ERR_SAME_ELEMENT_exception(void){
  CEXCEPTION_T e;
  Person *Ali = personNew("Ali", 25, 70.3);
  List *list = listNew(Ali, NULL);
  Map *map = mapNew(5);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(Ali, 3);
  
  Try{
    mapStore(map, Ali, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT exception to be thrown.");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT,e);
    TEST_ASSERT_NOT_NULL(map->bucket[3]);
    TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3,getPersonFromBucket(map->bucket[3]));
  }

}

void test_mapStore_given_Zorro_with_hash_value_3_should_add_into_the_bucket(void){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *person2 = personNew("Zorro", 35, 75.3);
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person2, 3);
  
  mapStore(map, person2, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3,getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_EQUAL_Person("Zorro", 35, 75.3,getPersonFromBucket(map->bucket[3]));
}

///////////////////////////////
//    mapFind
//////////////////////////////
void test_mapFind_to_find_Ali_and_return_Ali(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Ali, 3);
  mapStore(map, Ali, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3 ,getPersonFromBucket(map->bucket[3]));
  
  hash_ExpectAndReturn(Ali, 3);
  
  findResult = mapFind(map, Ali, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3,findResult);
}


void test_mapFind_to_find_Ali_and_return_NULL_if_Ali_not_in_the_map(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Ali, 3);

  findResult = mapFind(map, Ali, comparePerson, hash);
  TEST_ASSERT_NULL(findResult);
}

void test_mapFind_to_find_Ali_and_return_NULL_if_Abu_only_in_the_map(){
  Person *Abu = personNew("Abu", 15, 60.3);
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Abu, 3);
  mapStore(map, Abu, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person("Abu", 15, 60.3 ,getPersonFromBucket(map->bucket[3]));
  
  hash_ExpectAndReturn(Ali, 3);
  
  findResult = mapFind(map, Ali, comparePerson, hash);
  TEST_ASSERT_NULL(findResult);
}

void test_mapFind_to_find_Ali_and_return_Ali_after_search_in_list(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Zorro = personNew("Zorro", 35, 75.3);
  Person *findResult;
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(Zorro, 3);
  
  mapStore(map, Zorro, comparePerson, hash);
  
  hash_ExpectAndReturn(Ali, 3);
  
  findResult = mapFind(map, Ali, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3,findResult);
}

void test_mapFind_to_find_Dave_and_return_NULL_after_search_in_list(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Zorro = personNew("Zorro", 35, 75.3);
  Person *Dave = personNew("Dave", 55, 85.3);
  Person *findResult;
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(Zorro, 3);
  
  mapStore(map, Zorro, comparePerson, hash);
  
  hash_ExpectAndReturn(Dave, 3);
  
  findResult = mapFind(map, Dave, comparePerson, hash);
  
  TEST_ASSERT_NULL(findResult);
}

///////////////////////////////
//    mapRemove
//////////////////////////////
void test_mapRemove_should_remove_Ali_based_on_nameCompare_and_return_Ali_element_in_map(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *person2Remove = personNew("Ali", 0, 0);
  Person *removeResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Ali, 3);
  mapStore(map, Ali, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3 ,getPersonFromBucket(map->bucket[3]));
  
  hash_ExpectAndReturn(person2Remove, 3);
  
  printf("\n mapRemove Case1 \n -------------\n");
  removeResult = mapRemove(map, person2Remove, comparePerson, hash);
  TEST_ASSERT_NULL(getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3 ,removeResult);
}

void test_mapRemove_to_remove_Ali_should_fail_and_return_NULL_if_Abu_only_in_the_map(){
  Person *Abu = personNew("Abu", 15, 60.3);
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *person2Remove = personNew("Ali", 0, 0);
  Person *removeResult;
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(Abu, 3);
  mapStore(map, Abu, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person("Abu", 15, 60.3 ,getPersonFromBucket(map->bucket[3]));
  
  hash_ExpectAndReturn(person2Remove, 3);
  
  printf("\n mapRemove Case2 \n -------------\n");
  removeResult = mapRemove(map, person2Remove, comparePerson, hash);
  TEST_ASSERT_NULL(removeResult);
}

void test_mapRemove_to_remove_Ali_and_return_Ali_after_search_in_list(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Zorro = personNew("Zorro", 35, 75.3);
  Person *person2Remove = personNew("Ali", 0, 0);
  Person *removeResult;
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(Zorro, 3);
 
  mapStore(map, Zorro, comparePerson, hash);
  
  hash_ExpectAndReturn(person2Remove, 3);
  
  printf("\n mapRemove Case3 \n -------------\n");
  removeResult = mapRemove(map, person2Remove, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(removeResult);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3,removeResult);
}

void test_mapRemove_to_remove_Dave_and_return_NULL_after_search_in_list(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Zorro = personNew("Zorro", 35, 75.3);
  Person *person2Remove = personNew("Dave", 0, 0);
  Person *removeResult;
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(Zorro, 3);
  
  mapStore(map, Zorro, comparePerson, hash);
  
  hash_ExpectAndReturn(person2Remove, 3);
  
  printf("\n mapRemove Case4 \n -------------\n");
  removeResult = mapRemove(map, person2Remove, comparePerson, hash);
  
  TEST_ASSERT_NULL(removeResult);
}

void test_mapRemove_to_remove_Dave_which_is_between_Ali_and_Zorro_should_return_Dave_after_search_in_list(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Dave = personNew("Dave", 15, 60.3);
  Person *Zorro = personNew("Zorro", 35, 75.3);
  Person *person2Remove = personNew("Dave", 0, 0);
  Person *removeResult;
  Map *map = mapNew(5);
  List *list = listNew(Ali, NULL);
  list = listNew(Dave, list);
  list = listNew(Zorro, list);
  map->bucket[3] = list;
  
  TEST_ASSERT_EQUAL_Person("Zorro", 35, 75.3 ,getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person("Dave", 15, 60.3 ,getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3 ,getPersonFromBucket(((List *)map->bucket[3])->next->next));
  
  hash_ExpectAndReturn(person2Remove, 3);
  
  printf("\n mapRemove Case5 \n -------------\n");
  removeResult = mapRemove(map, person2Remove, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(removeResult);
  TEST_ASSERT_EQUAL_Person("Dave", 15, 60.3,removeResult);
  TEST_ASSERT_EQUAL_Person("Zorro", 35, 75.3 ,getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3 ,getPersonFromBucket(((List *)map->bucket[3])->next));
}
/*
///////////////////////////////
//    mapLinearStore
//////////////////////////////
void test_mapLinearStore_to_store_Ali(){
  Person *person = personNew("Ali", 25, 70.3);
  Map *map = mapNew(6);
  
  hash_ExpectAndReturn(person, 3);
  
  mapLinearStore(map, person, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(person ,map->bucket[3]);
}

void test_mapLinearStore_to_store_Ali_first_then_follow_by_Abu_with_hash_value_of_3_and_2(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Abu = personNew("Abu", 16, 50.3);
  Map *map = mapNew(6);
  
  hash_ExpectAndReturn(Ali, 3);
  mapLinearStore(map, Ali, comparePerson, hash);
    
  hash_ExpectAndReturn(Abu, 2);
  mapLinearStore(map, Abu, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[2]);
  TEST_ASSERT_EQUAL_Person(Ali ,map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(Abu ,map->bucket[2]);
}

void test_mapLinearStore_to_store_Ali_first_then_follow_by_Ani_with_same_hash_value_of_3(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Ani = personNew("Ani", 17, 52.3);
  Map *map = mapNew(6);
  
  hash_ExpectAndReturn(Ali, 3);
  mapLinearStore(map, Ali, comparePerson, hash);
    
  hash_ExpectAndReturn(Ani, 3);
  comparePerson_ExpectAndReturn(Ali, Ani, 0);
  mapLinearStore(map, Ani, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[4]);
  TEST_ASSERT_EQUAL_Person(Ali ,map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(Ani ,map->bucket[4]);
}

void test_mapLinearStore_to_store_Ali_Ani_Muthu_Sammi_with_same_hash_value_of_3_should_throw_exception_because_bucket_full(){
  CEXCEPTION_T e;
  
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Ani = personNew("Ani", 17, 52.3);
  Person *Muthu = personNew("Muthu", 37, 62.3);
  Person *Sammi = personNew("Sammi", 27, 68.3);
  Map *map = mapNew(6);
  
  hash_ExpectAndReturn(Ali, 3);
  mapLinearStore(map, Ali, comparePerson, hash);
    
  hash_ExpectAndReturn(Ani, 3);
  comparePerson_ExpectAndReturn(Ali, Ani, 0);
  mapLinearStore(map, Ani, comparePerson, hash);
  
  hash_ExpectAndReturn(Muthu, 3);
  comparePerson_ExpectAndReturn(Ali, Muthu, 0);
  comparePerson_ExpectAndReturn(Ani, Muthu, 0);
  mapLinearStore(map, Muthu, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[4]);
  TEST_ASSERT_NOT_NULL(map->bucket[5]);
  TEST_ASSERT_EQUAL_Person(Ali ,map->bucket[3]);
  TEST_ASSERT_EQUAL_Person(Ani ,map->bucket[4]);
  TEST_ASSERT_EQUAL_Person(Muthu ,map->bucket[5]);
  
  hash_ExpectAndReturn(Sammi, 3);
  comparePerson_ExpectAndReturn(Ali, Sammi, 0);
  comparePerson_ExpectAndReturn(Ani, Sammi, 0);
  comparePerson_ExpectAndReturn(Muthu, Sammi, 0);
  Try{
    mapLinearStore(map, Sammi, comparePerson, hash);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_BUCKET_FULL,e);
  }
}

///////////////////////////////
//    mapLinearFind
//////////////////////////////
void test_mapLinearFind_to_find_Ali(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *findResult;
  Map *map = mapNew(3);
  
  hash_ExpectAndReturn(Ali, 2);
  mapLinearStore(map, Ali, comparePerson, hash);
  TEST_ASSERT_EQUAL_Person(Ali ,(map->bucket[2]));
  
  hash_ExpectAndReturn(Ali, 2);
  comparePerson_ExpectAndReturn(Ali, Ali, 1);
  
  findResult = mapLinearFind(map, Ali, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person(Ali ,findResult);
}

void test_mapLinearFind_to_find_Muthu_from_Ali_Muthu(){
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Muthu = personNew("Muthu", 37, 62.3);
  Person *findPerson = personNew("Muthu", 0, 0);
  Person *findResult;
  Map *map = mapNew(4);
  
  hash_ExpectAndReturn(Ali, 2);
  mapLinearStore(map, Ali, comparePerson, hash);
  
  hash_ExpectAndReturn(Muthu, 2);
  comparePerson_ExpectAndReturn(Ali, Muthu, 0);
  mapLinearStore(map, Muthu, comparePerson, hash);
  
  hash_ExpectAndReturn(findPerson, 2);
  comparePerson_ExpectAndReturn(Ali, findPerson, 0);
  comparePerson_ExpectAndReturn(Muthu, findPerson, 1);
  
  findResult = mapLinearFind(map, findPerson, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person(Muthu ,findResult);
}

void test_mapLinearFind_to_find_Muthu_from_NULL(){
  Person *Muthu = personNew("Muthu", 37, 62.3);
  Person *findPerson = personNew("Muthu", 0, 0);
  Person *findResult;
  Map *map = mapNew(4);
  
  map->bucket[2] = (void *)-1;
  
  hash_ExpectAndReturn(Muthu, 2);
  comparePerson_ExpectAndReturn((void *)-1, Muthu, 0);
  mapLinearStore(map, Muthu, comparePerson, hash);
  
  hash_ExpectAndReturn(findPerson, 2);
  comparePerson_ExpectAndReturn(Muthu, findPerson, 1);
  
  findResult = mapLinearFind(map, findPerson, comparePerson, hash);
  TEST_ASSERT_NOT_NULL(findResult);
  TEST_ASSERT_EQUAL_Person(Muthu ,findResult);
}

void test_mapLinearFind_to_find_Muthu_but_fail(){
  Person *findPerson = personNew("Muthu", 0, 0);
  Person *findResult;
  Map *map = mapNew(3);
  
  map->bucket[2] = NULL;
  hash_ExpectAndReturn(findPerson, 2);
  findResult = mapLinearFind(map, findPerson, comparePerson, hash);
  TEST_ASSERT_NULL(findResult);
}

void test_mapLinearFind_to_find_Muthu_from_Ali_Ani_but_fail_and_throw_exception(){
  CEXCEPTION_T e;
  Person *findResult;
  Person *Ali = personNew("Ali", 25, 70.3);
  Person *Ani = personNew("Ani", 17, 52.3);
  Person *Muthu = personNew("Muthu", 37, 62.3);
  Person *findPerson = personNew("Muthu", 0, 0);
  Map *map = mapNew(4);
  
  map->bucket[1] = Ali;
  map->bucket[2] = Ani;
  
  hash_ExpectAndReturn(findPerson, 1);
  comparePerson_ExpectAndReturn(Ali, findPerson, 0);
  comparePerson_ExpectAndReturn(Ani, findPerson, 0);
  
  Try{
    findResult = mapLinearFind(map, findPerson, comparePerson, hash);}
  Catch(e){
    TEST_ASSERT_EQUAL(ERR_OUT_OF_BOUND,e);
  }
}

///////////////////////////////
//    mapLinearRemove
//////////////////////////////
// void test_mapLinearRemove_to_remove_Ali_but_fail_and_return_NULL(){
  // Person *removePerson = personNew("Ali", 0, 0);
  // Person *removeResult;
  // Map *map = mapNew(5);
  
  // hash_ExpectAndReturn(removePerson, 3);
  
  // removeResult = mapLinearRemove(map, removePerson, comparePerson, hash);
  // TEST_ASSERT_NULL(removeResult);
// }

// void test_mapLinearRemove_to_remove_Ali_and_return_Ali(){
  // Person *Ali = personNew("Ali", 25, 70.3);
  // Person *removePerson = personNew("Ali", 0, 0);
  // Person *removeResult;
  // Map *map = mapNew(5);
  // map->bucket[3] = Ali;
  // hash_ExpectAndReturn(removePerson, 3);
  // comparePerson_ExpectAndReturn(Ali, removePerson, 1);
  
  // removeResult = mapLinearRemove(map, removePerson, comparePerson, hash);
  // TEST_ASSERT_NOT_NULL(removeResult);
  // TEST_ASSERT_EQUAL_Person(NULL ,map->bucket[3]);
// }














*/














