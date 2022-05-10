# Design Doc hw4

## functions
### enqueue_path

This function will check if the q pointer is null, and if so, allocate a new LLPath using the inputted path. If the q pointer isn't null, then the function will allocate another LLPath node using the inputted path. The function will have to traverse to the end of the queue and set this new node as the next value of the node that used to be last. Then the front of the queue will be returned at the end of the function.
``` 
LLPath* new = (LLPath*)calloc(1, sizeof(LLPath));
new->val = path;
if (q is NULL){
  return new;
}
LLPath* current = q;
while(current->next != NULL) {
  current = current->next;
}
current->next = new;
return q;
```  

### dequeue_path

This function will set the ret pointer to the value of the node at the front of the queue and free the node, and then set the queue's pointer to the node after the freed node. Then the function will return true. If there is no node left when this function is called, then the LLPath will get freed, since there is nothing left. Once this is done, false will be returned. 
```
if (*q == NULL) {
  free(*q);
  return false;
}
*ret = (*q)->val;
LLPath* deleteThis = *q;
*q->next = *q->next->next;
free(deleteThis);
return true;
```

### path_bfs

This function will use a queue to keep track of paths of vertices it needs to check. First, it will create a new queue with a path that includes the starting vertex. Then it will dequeue a path, and then that vertex will be added to a set of vertices that were already checked. The function will also add the vertices that are linked to the current vertex to the path queue, that haven't been checked yet. For example ifit starts at vertex 1, that has 2 neighbors, 2 and 3, that havent been checked, then there will be 2 paths in the queue, 1->2 and 1->3. During this, the function will also add the current vertex to the Path vertices_visited. Once one vertex is checked, more paths are added to the queue with the neighbors of that vertex added to the end of their paths. Then it will dequeue, and start again, until it finds a path or doesn't find any. Before returning the path, the function will need to check the queue and store only the path that has the lowest steps and makes it to the destination. This will return the shortest path it finds.  
```
Path start = {0, {i}};
Path result = {0, {0}};
LLint* checked = NULL;
LLPath* to_check = enqueue_path(NULL, start);
LLPath* success = NULL;
Path deqP;
while (dequeue_path(&to_check, deqP)){
  if (deqP->vertices_visited[deqP->steps] == end) {
    success = enqueue_path(NULL, deqP);
  }
  add_to_set(checked, deqP->vertices_visited[deqP->steps];
  deqP->steps += 1;
  for (int i = 0; i < g->vertices; i++) {
    if (graph_has_edge(g, deqP->vertices_visited[deqP->steps-1], i)) {
      if (!set_contains(checked, i)) {
        Path splitPath = path_extend(deqP, i);
        to_check = enqueue(to_check, splitPath);
       }
    }
}
if (success) {
  Path result = dequeue_path(&success, deqP);
  while (dequeue_path(&success, deqP)){
    if (result->steps > deqP){
      result = deqP;
    }
  }
}
return result;
```

### path_dfs

This function apparently works the same as path_bfs, except a stack is used instead of a queue. So the code will mostly be the same except that the function uses a stack. However, it will return the first successful path it finds.
```
```

### push_path(LLPath *s, Path path)

This function will push an inputted path onto the stack. If the stack is null, then a stack will be allocated with the inputted stack on the top, with it's next value being null. 
```
LLPath* new = (LLPath*)calloc(1, sizeof(LLPath));
new->val = path;
if (s is NULL){
  new->next = NULL;
  return new;
}
new->next = s->next;
s->next = new;
return s;
```

### pop_path(LLPath **s, Path *ret)

This function will pop a path off the top of the stack. If pop is called and there is nothing left, the stack will be freed.
```
if (*s == NULL) {
  free(*s);
  return false;
}
*ret = (*s)->val;
LLPath* deleteThis = *s;
*s->next = *s->next->next;
free(deleteThis);
return true;
```
