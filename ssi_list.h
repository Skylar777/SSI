#ifndef PMAN_LIST_H
#define PMAN_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

typedef struct node {
   pid_t pid;
   char* file;
   struct node *next;
} node;

struct node *head;
struct node *current;

void printList();
void insertEnd(pid_t pid, char* file);
struct node* delete(pid_t pid);


#endif