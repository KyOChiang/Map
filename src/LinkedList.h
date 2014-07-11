#ifndef LinkedList_H
#define LinkedList_H

#define listAdd listNew

typedef struct List List;

struct List{
  List *next;
  void *data;
};

List *listNew(void *data,List *next);
List *listAdd(void *newdata,List *list);
void listDump(List *list, void (*dump)(void *));

#endif // LinkedList_H
