#include "bst.h"
#include <stdio.h>

int main() {
  Tree t = createTree();
  link x;
  
 /* AVLinsert(t,t->head,1);
  AVLinsert(t,t->head,2);
  AVLinsert(t,t->head,3);*/ //caso raiz l

  /*AVLinsert(t,t->head,33);
  AVLinsert(t,t->head,8);
  AVLinsert(t,t->head,1);*/ //caso raiz r
  
  /*AVLinsert(t,t->head,44);
  AVLinsert(t,t->head,55);
  AVLinsert(t,t->head,33);
  AVLinsert(t,t->head,22); 
  AVLinsert(t,t->head,77); 
  AVLinsert(t,t->head,21);*///rot r

  /*AVLinsert(t,t->head,44);
  AVLinsert(t,t->head,55);
  AVLinsert(t,t->head,33);
  AVLinsert(t,t->head,66);
  AVLinsert(t,t->head,77);*/ //rot l

  
  /*AVLinsert(t,t->head,44);
  AVLinsert(t,t->head,55);
  AVLinsert(t,t->head,22);
  AVLinsert(t,t->head,19);
  AVLinsert(t,t->head,21);*/ //rot lr

  AVLinsert(t,t->head,44);
  AVLinsert(t,t->head,55);
  AVLinsert(t,t->head,33);
  AVLinsert(t,t->head,66);
  AVLinsert(t,t->head,65); //rot rl
  
  imprime(t, "oi");

  return 0;
}