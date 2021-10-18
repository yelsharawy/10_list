#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "personlist.h"


struct person_node * insert_front(struct person_node * head, char *first, char *last, unsigned char age) {
    struct person_node *result = malloc(sizeof(struct person_node));
    
    strncpy(result->first, first, NAME_LEN);
    result->first[NAME_LEN] = 0;
    
    strncpy(result->last, last, NAME_LEN);
    result->last[NAME_LEN] = 0;
    
    result->age = age;
    result->next = head;
    
    return result;
}

void print_person(struct person_node *p) {
    printf("%s %s\n  Age: %hhu\n", p->first, p->last, p->age);
}

void print_list(struct person_node *head) {
    printf("== Person List ==\n");
    while (head) {
        print_person(head);
        head = head->next;
    }
    printf("=================\n\n");
}

struct person_node * free_list(struct person_node * head) {
    while (head) {
        struct person_node *next = head->next;
        // ^ must keep ptr to next before freeing
        free(head);
        head = next;
    }
    return head;
}

// most easily done recursively
struct person_node * remove_node(struct person_node *head, char *first) {
	if (head) {
		if (!strcmp(head->first, first)) {
			struct person_node *next = head->next;
			free(head);
			return next;
		} else {
			head->next = remove_node(head->next, first);
		}
	}
	return head;
}

// for fun/testing purposes
struct person_node * random_node(struct person_node *head) {
    struct person_node *result = 0;
    int i;
    for (i = 1; head; i++, head = head->next) {
        if (!(rand() % i)) result = head;
    }
    return result;
}
