#pragma once
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 128

typedef struct CustomerNode {
  char* email;
  char* name;
  int shoe_size;
  char* fav_food;
  struct CustomerNode* next;
} CustomerNode;

typedef struct CustomerTable {
  CustomerNode** slots;
  size_t num_slots;
} CustomerTable;

CustomerTable* table_create(size_t size);

void display(CustomerNode* c);

unsigned long hash(char *str);

void add(CustomerTable* table);

void table_add(CustomerTable* table, CustomerNode* c);

bool lookup(CustomerTable* table);

char* delete(CustomerTable* table);

void list(CustomerTable* table);

void save(CustomerTable* table, char* file_name);

void quit(CustomerTable* table);
