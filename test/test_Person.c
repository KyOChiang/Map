#include "unity.h"
#include "Person.h"

void setUp(void){}

void tearDown(void){}

void test_personNew_given_Ali_23_64_should_create_the_Person(){
	Person *person = personNew("Ali" , 23 , 64.0);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_EQUAL_STRING("Ali", person->name);
  TEST_ASSERT_EQUAL(23,person->age);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 64.0, person->weight);
}

void test_PersonDump_explorer(){
  Person *person = personNew("Ali" , 23 , 64.0);
  
  personDump(person);
}
