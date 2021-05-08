// ****** HASH STRUCT ******
// This implementation uses an array with variable size, that starts in 10 (arbitrary)
typedef struct hash Hash;
typedef struct person Person;

struct hash {
    short int n; // number of elements stored in hash table
    short int size; // table size
    Person** p; // pointer of pointer to data array
};

// ****** PERSON DATA STRUCT ******
struct person {
    unsigned int CPF;
    char name[30];
    Person* next;
};


// ****** CORE ******
Hash* hsh_create(void);
Person* hsh_find(Hash* table, unsigned int CPF);
Person* hsh_insert(Hash* table, Person* person);
void hsh_print(Hash* table, unsigned int CPF);
void hsh_clear(Hash* table);
short int hsh_is_empty(Hash* table);

// ****** AUXILIARY FUNCTIONS ******
short int hash(Hash* table, unsigned int CPF);
void hsh_resize(Hash* table);