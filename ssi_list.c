#include "ssi_list.h"


node* getHead(){
   return head;
}

void printList() {
   struct node *ptr = head;
	int i=0;
   while(ptr != NULL) {
      i++;
      printf("%d: %s %d\n",ptr->pid,ptr->file,i);
      
      
      ptr = ptr->next;
   }
   printf("Total Background jobs: %d\n", i);
}


void insertEnd(pid_t pid, char *file) {
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   if (link == NULL) { 
      perror("malloc failed");
   }

   link->next = NULL;
   link->pid = pid;
   link->file = strdup(file);

    if (head == NULL) {
        head = link;
    } else {
        struct node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = link;
    }
}


struct node* delete(pid_t pid) {

   struct node* current = head;
   struct node* previous = NULL;
	
   if(head == NULL) {
      return NULL;
   }

   while(current->pid != pid) {

      if(current->next == NULL) {
         return NULL;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if(current == head) {
      head = head->next;
   } else {
      previous->next = current->next;
   }    
	
   return current;
}