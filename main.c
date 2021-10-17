#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NAME_LEN 31

struct person_node {
    char first[NAME_LEN+1];
    char last[NAME_LEN+1];
    unsigned char age; // no man in recorded history has lived >255 years yet
    
    struct person_node *next;
};

struct person_node * new_person(char *first, char *last, unsigned char age) {
    struct person_node *result = malloc(sizeof(struct person_node));
    
    strncpy(result->first, first, NAME_LEN);
    result->first[NAME_LEN] = 0;
    
    strncpy(result->last, last, NAME_LEN);
    result->last[NAME_LEN] = 0;
    
    result->age = age;
    result->next = 0;
    
    return result;
}

void print_person(struct person_node *p) {
    printf("%s %s\n  Age: %hhu\n", p->first, p->last, p->age);
}

struct person_node * insert_front(struct person_node *head, char *first, char *last, unsigned char age) {
    struct person_node *result = new_person(first, last, age);
    result->next = head;
    return result;
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

// for fun:
void makeRandomName(char *dest, int max) {
    const static char *vowels = "aeiou";
    int len = 1;
    int consecutive = 0; // # of consecutive consonants
    
    if (max--) {
        *(dest++) = 'A' + rand() % 26;
        if (!strchr(vowels, dest[-1] + 32)) { // if it's a consonant...
            consecutive = 4;    // ensure the next is a vowel
        }
        while ((len++ < 2 || rand() % 5) && max--) { // ensures len is at least 2 & less than max, 1/5 chance to stop
            if (rand() % 5 <= consecutive) {
                *(dest++) = vowels[rand() % 5];
                consecutive = 0;
            } else {
                char chosen;
                do { // ensures a consonant is chosen
                    chosen = 'b' + rand() % 25;
                } while (strchr(vowels+1, chosen));
                *(dest++) = chosen;
                consecutive++;
            }
        }
    }
    *dest = 0;
}

int main() {
    srand(time(NULL));
    
    struct person_node *head = 0;
    print_list(head);
    head = insert_front(head, "Yusuf", "Elsharawy", 17);
    print_list(head);
    head = insert_front(head, "JonAlf", "Dyrland-Weaver", 30 + rand() % 30);
    { // test for keeping string even after original is removed from stack
        char first[NAME_LEN+1], last[NAME_LEN+1];
        makeRandomName(first, NAME_LEN);
        makeRandomName(last, NAME_LEN);
        head = insert_front(head, first, last, 10 + rand() % 90);
    }
    print_list(head);
    head = free_list(head);
    print_list(head);
}