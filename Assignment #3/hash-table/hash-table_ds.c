#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash-table_ds.h"

// Static variables for universal hash
static unsigned int a = 0;
static unsigned int b = 0;

// Function to create a new hash table
// Parameters: None
// Returns: Pointer to hash table (if it has been created) / EXIT the program if
//          the hash table (or the Person array) can't be created
Hash* hsh_create(void) {
    // Attempts to allocate memory for the Hash Table
    Hash* table = (Hash*) malloc(sizeof(Hash));

    // Checks whether memory allocation has been made
    if (table) {
        table->n = 0; // At first, the table is empty.
        table->size = 10; // 10 is an arbitrary value
        // Attempts to allocate memory for the Person array
        table->p = (Person**) malloc(table->size * sizeof(Person*));
        // Checks whether memory allocation has been made
        if (table->p) {
            // Starts all p's elements with NULL
            for (int i = 0;i < table->size;++i) {
                table->p[i] = NULL;
            }
        } else {
            printf("There is no enough memory available to allocate the Person array!\n");
            exit(1);
        }

        // Return the pointer to Table
        return table;
    } else {
        printf("There is no enough memory available to allocate the Table!\n");
        exit(1);
    }
}

// Function to find an element in table
// Parameters: Pointer to an existing table and the value to be searched
// Returns: Pointer to value (if found) / NULL (if not found)
Person* hsh_find(Hash* table, long int CPF) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    // We invoke the 'hash' function to map the key
    unsigned int ind = hash(table, CPF);

    // Get the pointer to element in index 'ind'
    Person *person = table->p[ind];

    // Loop until we find the requested person, or, person->next == NULL
    while (person) {
        if (person->CPF == CPF) {
            return person;
        } else {
            person = person->next;
        }
    }

    // The requested person is not in the table
    return NULL;
}

// Function to insert a new element in the table
// Parameters: Pointer to an existing table and the person to be inserted
// Returns: None
void hsh_insert(Hash* table, Person* person) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    // if 'table->n' greater than 75% of 'table-size',
    // then we'll resize 'table->person'
    if (table->n > 0.75 * table->size) {
        hsh_resize(table);
    }

    // We invoke the 'hash' function to map the key
    unsigned int ind = hash(table, person->CPF);

    // Collision - handling with linked list
    if (table->p[ind]) {
        person->next = table->p[ind];
        table->p[ind]->prev = person;
    }

    // Insert the new person into the 'ind' index of the array
    table->p[ind] = person;

    table->n++;
}

// Function to print an element of the table
// Parameters: Pointer to an existing table and the CPF of the person
// Returns: None
void hsh_print(Hash* table, long int CPF) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    // Find the person
    Person* person = hsh_find(table, CPF);

    if (person) {
        printf("Name: %s\n", person->name);
        printf("CPF: %ld\n", person->CPF);
    } else {
        printf("The requested person is not in the table!\n");
    }
}

// Function to free memory
// Parameters: Pointer to an existing table
// Returns: None
void hsh_clear(Hash* table) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    Person* tmp;
    for (int i = 0;i < table->size;++i) {
        while (table->p[i]) {
            tmp = table->p[i];
            table->p[i] = table->p[i]->next;
            free(tmp);
        }
    }

    free(table->p);
    free(table);
}

// Function to check if the table is empty
// Parameters: Pointer to an existing table
// Returns: 1 empty / 0 not empty
unsigned short int hsh_is_empty(Hash* table) {
    // Checks if the Table and the array Person exists
    if (!table) {
        printf("*table == NULL\n");
        exit(1);
    }

    return table->n == 0;
}

// Hash function
// Parameters: Pointer to an existing table and the key
// Returns: Hashed key
// https://www.geeksforgeeks.org/generating-random-number-range-c/
unsigned int hash(Hash* table, long int CPF) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    // Universal hash: h(k)_{a,b} = ((ak + b) % p) % table-size
    if (a == 0 && b == 0) {
        // Use current time as seed
        srand(time(0));
        a = (rand() % (table->size*30 - 2)) + 1; // rand() % (upper - lower + 1)) + lower = ]0,table->size*30]
        b = (rand() % (table->size*30 - 1)) + 0; // rand() % (upper - lower + 1)) + lower = [0,table->size*30]
    }

    return ((a*CPF + b) % table->size*30) % table->size;
}

// Function to resize the table
// Parameters: Pointer to an existing table
// Returns: None
void hsh_resize(Hash* table) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    unsigned short int old_n = table->n; // old n (number of elements in table)
    Person **prev_person_array = table->p; // pointer to the first element

    table->n = 0;
    table->size = (unsigned short int) (table->size * 1.947);
    // Attempts to allocate memory for the person->p array
    table->p = (Person**) malloc(table->size * sizeof(Person*));
    // Checks whether memory allocation has been made
    if (table->p) {
        // Starts all p's elements with NULL
        for (int i = 0; i < table->size; ++i) {
            table->p[i] = NULL;
        }
    } else {
        printf("There is no enough memory available to allocate the Person array!\n");
        exit(1);
    }

    // Copy all the elements of 'prev_person_array' into new table
    for (int i = 0; i < old_n; ++i) {
        if (prev_person_array[i]) {
            if (!prev_person_array[i]->next) {
                hsh_insert(table, prev_person_array[i]); // if the element has no collided with another one, we just copy him to the new table
            } else {
                Person* current = prev_person_array[i];
                while (current->next) {
                    current = current->next; // get the tail of the linked list
                }
                while (current->prev) {
                    hsh_insert(table, current); // insert elements from the last to the first
                    current = current->prev; // get the previous element
                    current->next = NULL;
                }
                hsh_insert(table, current); // insert the head of the list in the new table
            }
        }
    }

    // Free the memory allocated to 'prev_person_array'
    free(prev_person_array);
}