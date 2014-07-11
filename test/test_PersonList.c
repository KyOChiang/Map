#include "unity.h"
#include "LinkedList.h"
#include "Person.h"

void setUp(void){}

void tearDown(void){}

void test_PersonList_explore(){
  List *list;
	Person *person;
  
  person = personNew("Ali", 23, 64.4);
  list = listAdd(person, NULL);
  person = personNew("Zorro", 60, 55.4);
  list = listAdd(person, list);
  person = personNew("Sman", 80, 75.4);
  list = listAdd(person, list);
  
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL_STRING("Sman", ((Person *)list->data)->name);
  TEST_ASSERT_EQUAL_STRING("Zorro", ((Person *)list->next->data)->name);
  TEST_ASSERT_EQUAL_STRING("Ali", ((Person *)list->next->next->data)->name);
  
  listDump(list,personDump);
}
