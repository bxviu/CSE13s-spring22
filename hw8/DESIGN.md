# Design Doc hw8

## structure
### customer

This program will need a customer struct to store the data for each customer. It will contain their email, name, shoe size, and favorite food. It will also contain a pointer to the next customer, if there is a collision within the hash table.
```
typedef struct CustomerNode {
  char* email;
  char* name;
  int shoe_size;
  char* fav_food;
  struct CustomerNode* next;
} CustomerNode; 
```

### customertable

The hashtable to store the customers. If there is a collision, the new customer will be added to the front of the linked list already there. If not, the customer will be placed in the slot.
```
typedef struct CustomerTable {
  CustomerNode** slots;
  size_t num_slots;
} CustomerTable;
```

## functions
### main

This function will need to read the customers.tsv file and add the customers and their data into a hash table. Then it will continuously wait for the user, in a while loop, to input one of the commands: add, lookup, delete, list, save, quit.If they enter an input that doesn't match up, then it will say invalid input. Also, if they write help, it will list the commands they can do.
```
\#define MAX_LENGTH 128;

int main(){
  char buffer[MAX_LENGTH*4];
  FILE* infile;
  char* file_name = "customers.tsv";
  infile = fopen(file_name, "r");
  char* token;
  CustomerTable* t = table_create(10);
  while ((fgets(buffer, MAX_LENGTH*4, infile) != NULL)) {
    CustomerNode* c = (CustomerNode*)calloc(1, sizeof(CustomerNode));
    token = strtok(buffer, "\t");
    c->email = strdup(buffer);
    token = strtok(buffer, "\t");
    c->name = strdup(buffer);
    token = strtok(buffer, "\t");
    c->shoe_size = (int)buffer;
    token = strtok(buffer, "\n");
    c->fav_food = strdup(buffer);
    table_add(t, c);
  }
  fclose(infile);
  
  while (true) {
    printf("\nEnter Command: ");
    fgets(buffer, MAX_LENGTH, stdin);
    if (strcmp(buffer,"add")){
      add(t);
    }
    else if (strcmp(buffer,"lookup")){
      if (!lookup(t)){
        printf("Customer Not Found\n");
      }
    }
    else if (strcmp(buffer,"delete")){
      char* del = delete(t);
      if (del) {
        printf("%s Deleted\n", del);
      }
      else {
        printf("Customer Not Found\n");
      }  
    }
    else if (strcmp(buffer,"list")){
      list(t);
    }
    else if (strcmp(buffer,"save")){
      save(t,file_name);
    }
    else if (strcmp(buffer,"quit")){
      quit(t);
      break;
    }
    else if (strcmp(buffer,"help")){
      printf("Commands\nadd: add a customer by answering the prompts about them\nlookup: look for the requested customer in the hash table using their email\ndelete: delete the inputted customer from the hash table by inputting their email\nlist: display all information of the customers in the hash table\nsave: save the hash table to the customers.tsv file\nquit: exit the program\nhelp: display what commands can be used\n);
    }
    else{
      printf("Invalid Command - Maybe Try Using "help");
    }
  }
}
```

### table_create

This function will create a hash table with the inputted number of slots. This is so the function can be called easily if the hash_table needs to be reallocated to have more slots, so there are less collisions.
```
CustomerTable* table_create(size_t size){
  CustomerTable* out = calloc(1, sizeof(CustomerTable));
  out->num_slots = size;
  out->slots = calloc(size, sizeof(CustomerNode*));
  return out;
}
```

### display

Display will print out the inputted customer's data nicely formatted.
```
void display(Customer* c){
  printf("Customer:
        \n-------
        \nEmail: %s
        \nName: %s
        \nShoe Size: %d
        \nFavorite Food: %s
        \n
        \n", c->email,c->name,c->shoe_size,c->fav_food); 
}
```

### hash

This is the hash function given from a demo in class.
```
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}
```

### add

Add will first ask for the customer email, then name, then shoe_size, and finally their favorite food. After getting each piece of information, it will add it to a new customer struct. This struct will then be added to the hash table created in main using the hash function provided in a class example. 
```
CustomerNode* add(CustomerTable* table){
  CustomerNode* c = (CustomerNode*)calloc(1, sizeof(CustomerNode));
  char buffer[MAX_LENGTH] = {0};
  printf("New Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  c->email = strdup(buffer); 
  printf("\nName: ");
  fgets(buffer, MAX_LENGTH, stdin);
  c->name = strdup(buffer);
  printf("\nShoe Size: ");
  fgets(buffer, MAX_LENGTH, stdin);
  c->shoe_size = (int)buffer;
  printf("\nFavorite Food: ");
  fgets(buffer, MAX_LENGTH, stdin);
  c->fav_food = strdup(buffer);
  table_add(table, c);
  printf("\nCustomer: %s added.\n", c->name);
  return c;
}
```  

### table_add

Table_add will add the inputted customer to the hashtable using the hash function to determine which slot they will go in. This function is not part of add since I want to be able to use this function to also add customers from the tsv file. If the customer is already in the hash table, their information will be updated according to the new data.
```
CustomerNode* table_add(CustomerTable* table, CustomerNode* c){
  unsigned long hashval = hash(c->email);
  size_t slot = hashval % table->num_slots;
  
  CustomerNode* here = table->slots[slot];

  while(here) {
    if (!strcmp(here->email, c->email)) {
      free(here->name);
      free(here->fav_food);
      here->name = c->name;
      here->shoe_size = c->shoe_size;
      here->fav_food = c->fav_food;
      return c;
    }
    here = here->next;
  }
  c->next = table->slots[slot];
  table->slots[slot] = c;
  return c;
} 
```

### lookup

Lookup will use the hash function to check a specific slot in the hash table. If it finds a matching customer, it will display their data. If not the function will say that it can't find the customer.
```
bool lookup(CustomerTable* table){
  char buffer[MAX_LENGTH] = {0};
  printf("Look Up Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  unsigned long hashval = hash(buffer);
  size_t slot  = hashval % table->num_slots;

  CustomerNode* here = table->slots[slot];

  while(here) {
    if (!strcmp(here->email, buffer)) {
      display(here);
      return true;
    }
    here = here->next;
  }
  return false;
}
```

### delete

Delete will use the hash function to check a specific slot in the hash table. If it finds a customer with a match to the inputted name, then it will delete and free that customer struct. It will also return their name. If the customer is part of a linked list, the function will have to change the next pointer of the customer before it. If there is no matching customer, the function will return NULL.
```
char* delete(CustomerTable* table){
  char buffer[MAX_LENGTH] = {0};
  printf("Delete Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  unsigned long hashval = hash(buffer);
  size_t slot  = hashval % table->num_slots;

  CustomerNode* linkedlist = table->slots[slot];
  CustomerNode* here = linkedlist;
  CustomerNode* prev = NULL;
  while(here) {
    if (!strcmp(here->email, buffer)) {
      prev->next = here->next;
      char* temp = strdup(here->email);
      free(here->email);
      free(here->name);
      free(here->fav_food);
      free(here);
      return temp;
    }
    here = here->next;
    prev = (prev) ? prev->next : table->slots[slot];
  }
  return NULL;
}
```

### list

List will iterate through the hash table and display every customer it sees. If there is a linked list within a slot, then the function will iterate through that link list before continuing to the next slot.
```
void list(CustomerTable* table){
  printf("Customer List:\n")
  for (int i = 0; i < table->num_slots; i++) {
    if (table->slots[i] != NULL){
      CustomerNode* here = table->slots[slot];
      while(here) {
        display(here);
        here = here->next;
      }
    }
  }
}
```

### save

Save will have to iterate through the hash table and write to the customers.tsv file. Each customer will be on one line, and their data is split up by \t, and ending with \n.
```
void save(CustomerTable* table, char* file_name){
  FILE* infile;
  infile = fopen(file_name, "w");
   for (int i = 0; i < table->num_slots; i++) {
    if (table->slots[i] != NULL){
      CustomerNode* here = table->slots[slot];
      while(here) {
        fprintf(infile, "%s\t%s\t%d\t%s\n", here->email, here->name, here->shoe_size, here->fav_food);
        here = here->next;
      }
    }
  } 
  fclose(infile);
}
```

### quit

Quit will iterate through the hash table. It will free the customer's data, the customer struct, and the hash table. Then in main right after it, the loop asking for user input will be ended with break, finishing the program. 
```
void quit(CustomerTable* table){
  for (int i = 0; i < table->num_slots; i++) {
    if (table->slots[i] != NULL){
      CustomerNode* here = table->slots[slot];
      while(here) {
        CustomerNode* deleteThis = here;
        free(here->email);
        free(here->name);
        free(here->fav_food);
        here = here->next;
        free(deleteThis);
      }
    }
  }
  free(table->slots);
  free(table);
}
```
