#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hash-table_ds.h>

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

Person* hsh_find(Hash* table, unsigned int CPF);
Person* hsh_insert(Hash* table, Person* person);
void hsh_print(Hash* table, unsigned int CPF);
void hsh_clear(Hash* table);
short int hsh_is_empty(Hash* table);

// ****** AUXILIARY FUNCTIONS ******
short int hash(Hash* table, unsigned int CPF);
void hsh_resize(Hash* table);