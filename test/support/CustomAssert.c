#include "unity.h"
#include "CustomAssert.h"
#include "Person.h"

void assertEqualPerson(Person *expected, Person *actual, int line, char *msg){
  UNITY_TEST_ASSERT_EQUAL_STRING(expected->name,actual->name, line, "Name not the same.");
  UNITY_TEST_ASSERT_EQUAL_INT(expected->age, actual->age, line, "Age not the same.");
  UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, expected->weight, actual->weight, line, "Weight not the same.");
}
