#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphsearch.h"

// dealing with sets of integers. We wrote these in class.
LLint *add_to_set(LLint *set, int val) {
  LLint *newfront = calloc(1, sizeof(LLint));
  newfront->val = val;
  newfront->next = set;

  return newfront;
}

bool set_contains(LLint *set, int val) {
  if (set == NULL) {
    return false;
  } else if (set->val == val) {
    return true;
  } else {
    return set_contains(set->next, val);
  }
}

// Linked lists of paths. You'll need to implement these.

// Returns the new front of the queue, for a queue of Path structs.
// Usually this will be the old front of the queue, but if q is NULL, then it
// will allocate a new linked list node and return that.
LLPath *enqueue_path(LLPath *q, Path path) {
  // YOUR CODE HERE
  LLPath* new = (LLPath*)calloc(1, sizeof(LLPath));
  new->val = path;
  if (q == NULL){
    return new;
  }
  LLPath* current = q;
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = new;
  return q;
}

bool dequeue_path(LLPath **q, Path *ret) {
  // YOUR CODE HERE
  if (*q == NULL) {
    free(*q);
    return false;
  }
  *ret = (*q)->val;
  LLPath* deleteThis = *q;
  (*q) = (*q)->next;
  free(deleteThis);
  return true;
}

LLPath* push_path(LLPath *s, Path path){
  LLPath* new = (LLPath*)calloc(1, sizeof(LLPath));
  new->val = path;
  if (s == NULL){
    new->next = NULL;
    return new;
  }
  new->next = s;
  s = new;
  return s;
}

bool pop_path(LLPath **s, Path *ret){
  if (*s == NULL) {
    free(*s);
    return false;
  }
  *ret = (*s)->val;
  LLPath* deleteThis = *s;
  (*s) = (*s)->next;
  free(deleteThis);
  return true;
}
// We wrote these in class.
Graph *graph_create(int vertices) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  g->matrix = (int **)calloc(vertices, sizeof(int*));
  for (int i=0; i < vertices; i++) {
    g->matrix[i] = (int *)calloc(vertices, sizeof(int));
  }
  return g;
}

void graph_add_edge(Graph *g, int i, int j) {
  g->matrix[i][j] = 1;
}

bool graph_has_edge(Graph *g, int i, int j) {
  return g->matrix[i][j];
}

// Convenience method for you -- returns a new Path where you have added another
// vertex along the path.
Path path_extend(Path path, int new_vertex) {
  Path out;
  out.steps = path.steps;

  for (int i=0; i < path.steps; i++) {
    out.vertices_visited[i] = path.vertices_visited[i];
  }
  out.vertices_visited[path.steps] = new_vertex;
  out.steps += 1;
  return out;
}

// Print out a path nicely for the user.
void print_path(Path path) {
  if (path.steps == 0) {
    puts("(empty path)");
  }
  for (int i=0; i < path.steps; i++) {
    printf("%s%d",
        (i == 0) ? "" : " -> ",
        path.vertices_visited[i]);
  }
  puts("");
}

// Breadth-first search!
Path graph_find_path_bfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
  Path start = {1, {i}};
  Path result = {0, {0}};
  LLint* checked = NULL;
  LLPath* to_check = enqueue_path(NULL, start);
  Path deqP;
  while (dequeue_path(&to_check, &deqP)){
	  //printf("looped ");
	  print_path(deqP);
    if (deqP.vertices_visited[deqP.steps-1] == j) {
      return deqP;
    }
    add_to_set(checked, deqP.vertices_visited[deqP.steps-1]);
    for (int k = 0; k < g->vertices; k++) {
	//printf("checking %d to %d\n ", deqP.vertices_visited[deqP.steps-1], k);
	//printf("k in for %d\n", k);
      if (graph_has_edge(g, deqP.vertices_visited[deqP.steps-1], k)) {
	//printf("checking in if %d to %d; steps %d\n ", deqP.vertices_visited[deqP.steps], k, deqP.steps);
	//printf("n in if %d\n", k);
        if (!set_contains(checked, k)) {

          Path splitPath = path_extend(deqP, k);
          //printf("split %d ", k);
	  //print_path(splitPath);
	  to_check = enqueue_path(to_check, splitPath);
        }
      }
    }
  }
  return result;
}


// Depth-first search!
Path graph_find_path_dfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
  Path start = {1, {i}};
  Path result = {0, {0}};
  LLint* checked = NULL;
  LLPath* to_check = push_path(NULL, start);
  Path deqP;
  while (pop_path(&to_check, &deqP)){
	  print_path(deqP);
    if (deqP.vertices_visited[deqP.steps-1] == j) {
      return deqP;
    }
    add_to_set(checked, deqP.vertices_visited[deqP.steps-1]);
    for (int k = 0; k < g->vertices; k++) {
      if (graph_has_edge(g, deqP.vertices_visited[deqP.steps-1], k)) {
        if (!set_contains(checked, k)) {
          Path splitPath = path_extend(deqP, k);
	  //printf("split ");
	  //print_path(splitPath);
	  to_check = push_path(to_check, splitPath);
        }
      }
    }
  }
  return result;
}
