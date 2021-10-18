#define NAME_LEN 31

struct person_node {
    char first[NAME_LEN+1];
    char last[NAME_LEN+1];
    unsigned char age; // no man in recorded history has lived >255 years yet
    
    struct person_node *next;
};

struct person_node * insert_front(struct person_node * head, char *first, char *last, unsigned char age);

void print_person(struct person_node *p);

void print_list(struct person_node *head);

struct person_node * free_list(struct person_node * head);

// removes if first name matches
struct person_node * remove_node(struct person_node *head, char *first);

// for fun/testing purposes
struct person_node * random_node(struct person_node *head);