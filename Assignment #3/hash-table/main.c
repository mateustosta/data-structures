#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash-table_ds.h"

int main(void) {
    // Create a table
    Hash* table = hsh_create();

    // Check if is empty - 1 = empty/0 = not empty
    printf("==========IS EMPTY?==========\nEmpty: %d\n", hsh_is_empty(table));

    // Create persons
    Person* person1 = (Person*) malloc(sizeof(Person));
    person1->CPF = 12345678910;
    strcpy(person1->name, "John Doe");
    person1->next = NULL;
    person1->prev = NULL;

    Person* person2 = (Person*) malloc(sizeof(Person));
    person2->CPF = 12345678911;
    strcpy(person2->name, "Jane Doe");
    person2->next = NULL;
    person2->prev = NULL;

    Person* person3 = (Person*) malloc(sizeof(Person));
    person3->CPF = 12345678912;
    strcpy(person3->name, "John Roe");
    person3->next = NULL;
    person3->prev = NULL;

    Person* person4 = (Person*) malloc(sizeof(Person));
    person4->CPF = 12345678913;
    strcpy(person4->name, "Richard Roe");
    person4->next = NULL;
    person4->prev = NULL;

    Person* person5 = (Person*) malloc(sizeof(Person));
    person5->CPF = 12345678914;
    strcpy(person5->name, "Jane Roe");
    person5->next = NULL;
    person5->prev = NULL;

    Person* person6 = (Person*) malloc(sizeof(Person));
    person6->CPF = 12345678915;
    strcpy(person6->name, "Baby Doe");
    person6->next = NULL;
    person6->prev = NULL;

    Person* person7 = (Person*) malloc(sizeof(Person));
    person7->CPF = 12345678916;
    strcpy(person7->name, "Janie Doe");
    person7->next = NULL;
    person7->prev = NULL;

    Person* person8 = (Person*) malloc(sizeof(Person));
    person8->CPF = 12345678917;
    strcpy(person8->name, "Johnny Doe");
    person8->next = NULL;
    person8->prev = NULL;

    Person* person9 = (Person*) malloc(sizeof(Person));
    person9->CPF = 12345678918;
    strcpy(person9->name, "Harry Hoe");
    person9->next = NULL;
    person9->prev = NULL;

    // Insert persons
    hsh_insert(table, person1);
    hsh_insert(table, person2);
    hsh_insert(table, person3);
    hsh_insert(table, person4);
    hsh_insert(table, person5);
    hsh_insert(table, person6);

    // Print elements
    printf("\n==========BEFORE RESIZE==========\n");
    hsh_print(table, 12345678910); // John Doe
    printf("\n");
    hsh_print(table, 12345678911); // Jane Doe
    printf("\n");
    hsh_print(table, 12345678912); // John Roe
    printf("\n");
    hsh_print(table, 12345678913); // Richard Roe
    printf("\n");
    hsh_print(table, 12345678914); // Jane Roe
    printf("\n");
    hsh_print(table, 12345678915); // Baby Doe

    // Insert others persons
    hsh_insert(table, person7);
    hsh_insert(table, person8);
    printf("\n");
    hsh_print(table, 12345678916); // Janie Doe
    printf("\n");
    hsh_print(table, 12345678917); // Johnny Doe
    hsh_insert(table, person9); // resize hash table at this point

    // Print elements
    printf("\n==========AFTER RESIZE==========\n");
    hsh_print(table, 12345678910); // John Doe
    printf("\n");
    hsh_print(table, 12345678911); // Jane Doe
    printf("\n");
    hsh_print(table, 12345678912); // John Roe
    printf("\n");
    hsh_print(table, 12345678913); // Richard Roe
    printf("\n");
    hsh_print(table, 12345678914); // Jane Roe
    printf("\n");
    hsh_print(table, 12345678915); // Baby Doe
    printf("\n");
    hsh_print(table, 12345678916); // Janie Doe
    printf("\n");
    hsh_print(table, 12345678917); // Johnny Doe
    printf("\n");
    hsh_print(table, 12345678918); // Harry Hoe

    // Check if is empty - 1 = empty/0 = not empty
    printf("\n==========IS EMPTY?==========\nEmpty: %d\n", hsh_is_empty(table));

    // Clear the table
    hsh_clear(table);
}