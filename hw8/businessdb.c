#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "database_functions.h"

//#define MAX_LENGTH = 128;

int main(){
  char buffer[MAX_LENGTH];
  FILE* infile;
  char* file_name = "customers.tsv";
  infile = fopen(file_name, "r");
  char* token;
  CustomerTable* t = table_create(10);
  while ((fgets(buffer, MAX_LENGTH, infile) != NULL)) {
    CustomerNode* c = (CustomerNode*)calloc(1, sizeof(CustomerNode));
    token = strtok(buffer, "\t");
    c->email = strdup(token);
    token = strtok(NULL, "\t");
    c->name = strdup(token);
    token = strtok(NULL, "\t");
    c->shoe_size = atoi(token);
    token = strtok(NULL, "\n");
    c->fav_food = strdup(token);
    table_add(t, c);
  }
  fclose(infile);
  
  printf("Customer Database Opened");
  while (true) {
    printf("\nEnter Command: ");
    fgets(buffer, MAX_LENGTH, stdin);
    buffer[strlen(buffer)-1] = '\0';
    if (!strcmp(buffer,"add")){
      add(t);
    }
    else if (!strcmp(buffer,"lookup")){
      if (!lookup(t)){
        printf("Customer Not Found\n");
      }
    }
    else if (!strcmp(buffer,"delete")){
      char* del = delete(t);
      if (del) {
        printf("Deleted Customer: %s\n", del);
	free(del);
      }
      else {
        printf("Customer Not Found\n");
      }
    }
    else if (!strcmp(buffer,"list")){
      list(t);
    }
    else if (!strcmp(buffer,"save")){
      save(t,file_name);
    }
    else if (!strcmp(buffer,"quit")){
      quit(t);
      break;
    }
    else if (!strcmp(buffer,"help")){
      printf("Commands:\n-------\nadd: add a customer by answering the prompts about them\n-------\nlookup: look for the requested customer in the hash table using their email\n-------\ndelete: delete the inputted customer from the hash table by inputting their email\n-------\nlist: display all information of the customers in the hash table\n-------\nsave: save the hash table to the customers.tsv file\n-------\nquit: exit the program\n-------\nhelp: display what commands can be used\n-------\n");
    }
    else{
      printf("Invalid Command - Maybe Try Using \"help\"");
    }
  }
}
