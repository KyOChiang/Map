#include <stdio.h>
#include <string.h>
#include "Person.h"
#include "comparePerson.h"

int comparePerson(void *person1, void *person2){
  Person *p1 = (Person *)person1;
  Person *p2 = (Person *)person2;
  
  if(strcmp(p1->name, p2->name) == 0) return 1;
  else return 0;
}


