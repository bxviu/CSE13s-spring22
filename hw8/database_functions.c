#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "database_functions.h"

//#define MAX_LENGTH 128;

CustomerTable* table_create(size_t size){
  CustomerTable* out = calloc(1, sizeof(CustomerTable));
  out->num_slots = size;
  out->slots = calloc(size, sizeof(CustomerNode*));
  return out;
}

void display(CustomerNode* c){
  printf("\n-------\nEmail: %s\nName: %s\nShoe Size: %d\nFavorite Food: %s\n-------\n", c->email,c->name,c->shoe_size,c->fav_food);
}

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

void add(CustomerTable* table){
  CustomerNode* c = (CustomerNode*)calloc(1, sizeof(CustomerNode));
  char buffer[MAX_LENGTH] = {0};
  printf("New Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  c->email = strdup(buffer);
  printf("Name: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  c->name = strdup(buffer);
  printf("Shoe Size: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  c->shoe_size = atoi(buffer);
  printf("Favorite Food: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  c->fav_food = strdup(buffer);
  printf("\nCustomer Added: %s\n", c->email);
  table_add(table, c);
}

void table_add(CustomerTable* table, CustomerNode* c){
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
      free(c->email);
      free(c);
      return;
    }
    here = here->next;
  }
  c->next = table->slots[slot];
  table->slots[slot] = c;
}

bool lookup(CustomerTable* table){
  char buffer[MAX_LENGTH] = {0};
  printf("Look Up Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  unsigned long hashval = hash(buffer);
  size_t slot  = hashval % table->num_slots;

  CustomerNode* here = table->slots[slot];

  while(here) {
    if (!strcmp(here->email, buffer)) {
      printf("\nCustomer:");
      display(here);
      return true;
    }
    here = here->next;
  }
  return false;
}

char* delete(CustomerTable* table){
  char buffer[MAX_LENGTH] = {0};
  printf("Delete Customer:\nEmail: ");
  fgets(buffer, MAX_LENGTH, stdin);
  buffer[strlen(buffer)-1] = '\0';
  unsigned long hashval = hash(buffer);
  size_t slot  = hashval % table->num_slots;

  CustomerNode* linkedlist = table->slots[slot];
  CustomerNode* here = linkedlist;
  CustomerNode* prev = NULL;
  while(here) {
    if (!strcmp(here->email, buffer)) {
      if (prev) {
        prev->next = here->next; 
      }
      else {
        table->slots[slot] = here->next;
      }
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

void list(CustomerTable* table){
  printf("\nCustomer List:");
  bool customers = false;
  for (size_t i = 0; i < table->num_slots; i++) {	  
    if (table->slots[i] != NULL){
      if (!customers) { customers = true; }
      CustomerNode* here = table->slots[i];
      while(here) {
        display(here);
        here = here->next;
      }
    }
  }
  if (!customers) {
    printf("\nNo Customers in Database.\n");
  }
}

void save(CustomerTable* table, char* file_name){
  FILE* infile;
  infile = fopen(file_name, "w");
  for (size_t i = 0; i < table->num_slots; i++) {
    if (table->slots[i] != NULL){
      CustomerNode* here = table->slots[i];
      while(here) {
        fprintf(infile, "%s\t%s\t%d\t%s\n", here->email, here->name, here->shoe_size, here->fav_food);
        here = here->next;
      }
    }
  }
  fclose(infile);
  printf("Database Saved!\n");
}

void quit(CustomerTable* table){
  for (size_t i = 0; i < table->num_slots; i++) {
    if (table->slots[i] != NULL){
      CustomerNode* here = table->slots[i];
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
