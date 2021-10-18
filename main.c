#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "personlist.h"


// for fun (not in "personlist" because it's not specific to nodes):
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
    printf("## POPULATING LIST");
    head = insert_front(head, "Yusuf", "Elsharawy", 17);
    print_list(head);
    head = insert_front(head, "JonAlf", "Dyrland-Weaver", 30 + rand() % 30);
    
    char rand_first[NAME_LEN+1], rand_last[NAME_LEN+1];
    makeRandomName(rand_first, NAME_LEN);
    makeRandomName(rand_last, NAME_LEN);
    head = insert_front(head, rand_first, rand_last, 10 + rand() % 90);
    
    print_list(head);
    printf("## REMOVING 1 AT A TIME, IN RANDOM ORDER\n");
    while (head) {
        struct person_node *toremove = random_node(head);
        printf("# REMOVING: %s\n", toremove->first);
        head = remove_node(head, toremove->first);
        printf("# REMANING:\n");
        print_list(head);
    }
    printf("## FREEING REMAINING (which should be none)\n");
    head = free_list(head);
    print_list(head);
}
