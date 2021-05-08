// ****** HASH STRUCT ******
// This implementation uses an array with variable size, that starts in 10 (arbitrary)
typedef struct hash Hash;
typedef struct person Person;

struct hash {
    unsigned int n; // number of elements stored in hash table
    unsigned int size; // table size
    Person** p; // pointer of pointer to data array
};

// ****** PERSON DATA STRUCT ******
struct person {
    long int CPF; // data
    char name[30]; // data
    Person* next; // pointer to the next element (collision handling)
};


// ****** CORE ******
Hash* hsh_create(void);
Person* hsh_find(Hash* table, long int CPF);
void hsh_insert(Hash* table, long int CPF, char* name);
void hsh_print(Hash* table, long int CPF);
void hsh_clear(Hash* table);
unsigned short int hsh_is_empty(Hash* table);

// ****** AUXILIARY FUNCTIONS ******
unsigned int hash(Hash* table, long int CPF);
void hsh_resize(Hash* table);
unsigned int hsh_generate_parameters(unsigned short int parameters, unsigned int table_size);