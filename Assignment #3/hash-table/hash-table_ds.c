#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <hash-table_ds.h>

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

    // Checks if *person is the person we want
    if (person->CPF == CPF) {
        return person;
    }

    // Loop until we find the requested person, or, person->next == NULL
    while (person != NULL) {
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
void hsh_insert(Hash* table, long int CPF, char* name) {
    // Checks if the Table and the array Person exists
    if (!table || !table->p) {
        printf("*table == NULL or *table->p == NULL\n");
        exit(1);
    }

    // We invoke the 'hash' function to map the key
    unsigned int ind = hash(table, CPF);

    // if 'table->n' greater than 75% of 'table-size',
    // then we'll resize 'table->person'
    if (table->n > 0.75 * table->size) {
        hsh_resize(table);
    }

    // Attempts to allocate memory for the Person
    Person* person = (Person*) malloc(sizeof(Person));

    // Checks whether memory allocation has been made
    if (person) {
        person->CPF = CPF; // set data
        strcpy(person->name, name); // set data
        person->next = table->p[ind]; // insert the element in the first position of the linked list
    } else {
        printf("There is no enough memory available to allocate the Person struct!\n");
        exit(1);
    }

    table->p[ind] = person; // insert the new person in the first position of the linked list
    table->n++;
}

// Function to print an element of the table
// Parameters: Pointer to an existing table and the CPF of the person
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

    for (int i = 0;i < table->size;++i) {
        free(table->p[i]);
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
unsigned int hash(Hash* table, long int CPF) {
    // Universal hash: h(k)_{a,b} = ((ak + b) % p) % table-size
    if (a == 0) {
        a = hsh_generate_parameters(0, table->size);
    }

    if (b == 0) {
        b = hsh_generate_parameters(1, table->size);
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
    Person** prev_person_array = table->p; // pointer to the first element

    table->n = 0;
    table->size = (unsigned short int)(table->size * 1.947);
    // Attempts to allocate memory for the person->p array
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

    // Copy all the elements of 'prev_person_array' into new table
    for (int i = 0;i < old_n;++i) {
        hsh_insert(table, prev_person_array[i]->CPF, prev_person_array[i]->name);
    }

    // Free the memory allocated to 'prev_person_array'
    free(prev_person_array);
}

// Function to generate A and B for the universal hashing
// Parameters: 0 - A / 1 - B
// Returns: Random number
// https://www.geeksforgeeks.org/generating-random-number-range-c/
unsigned int hsh_generate_parameters(unsigned short int parameter, unsigned int table_size) {
    // Use current time as seed
    srand(time(0));

    // An value greater than table->size
    unsigned int p = table_size*30; // 30 is an arbitrary number

    if (parameter == 0) {
        // Generate a number in ]0,p]
        a = (rand() % (p - 2)) + 1; // rand() % (upper - lower + 1)) + lower
        return a;
    } else {
        // Generate a number in [0,p]
        b = (rand() % (p - 1)) + 0; // rand() % (upper - lower + 1)) + lower
        return b;
    }
}