#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int id = 0;
link novoNo(int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1; //-Folhas sempre tem mais um nó vazio
  t->id = id++;
  t->height = 0;
  return t;
}
Tree createTree() {
  Tree t = malloc(sizeof(struct tree));
  t->z = malloc(sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0; //-Nó vazio, refresenta o fim da arvore
  t->z->r = t->z;
  return t;
}

link rotR(Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

link rotL(Tree t, link h) { //-Mudar
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if (h->item == query)
    return h;
  if (h->item >= query)
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
}

link search(Tree t, int query) { return searchR(t, t->head, query); }

link insertR(Tree t, link h, link n) {
  if (h == t->z) {
    return n; //-Retorna o nó novo como filho do nó certo
  }

  if (h->item >= n->item)
    h->l = insertR(t, h->l, n); //-Insere na subarvore esquerda
  else
    h->r = insertR(t, h->r, n); //-Insere na subarvore direita
  (h->N)++;
  return h;
}

link insert(Tree t, int item) {
  if (t->head == t->z) {
    return (t->head = novoNo(item, t->z, t->z)); //-Arvore sem nós, raiz nova vem de novoNo
  }
  return insertR(t, t->head, novoNo(item, t->z, t->z)); //-Manda o nó da arvore para a func de entrada passando um nó novo
}

void imprimeEmOrdem(Tree t, link h) {
  if (h == t->z)
    return;
  imprimeEmOrdem(t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N);
  imprimeEmOrdem(t, h->r);
}

void imprimePosOrdem(Tree t, link h) {
  if (h == t->z)
    return;
  imprimePosOrdem(t, h->l);
  imprimePosOrdem(t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N);
}
void imprimePreOrdem(Tree t, link h, int k) {
  if (h == t->z)
    return;
  for (int i = 0; i <= k; i++)
    printf(" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N);
  imprimePreOrdem(t, h->l, k + 1);
  imprimePreOrdem(t, h->r, k + 1);
}

void printnode(char *x, int h) {
  int i;
  for (i = 0; i < h; i++)
    printf("\t");
  printf("%s\n", x);
}

int c = 0;
void imprimeR(Tree a, link t) {
  char s[255];
  if (t == a->z) {
    return;
  }
  imprimeR(a, t->r);
  printf("%d [ label = \"<f0>| <f1> %d (%d) bf:%d h:%d| <f2>\"]\n",t->id, t->item, t->N, t->bf, t->height);
  if (t->l != a->z) {
    printf("%d:f0->%d:f1;\n", t->id, t->l->id);
  } else {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f0->z%d;\n", t->id, c);
    c++;
  }
  if (t->r != a->z) {
    printf("%d:f2->%d:f1;\n", t->id, t->r->id);
  } else {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f2->z%d;\n", t->id, c);
    c++;
  }
  imprimeR(a, t->l);
}

void imprime(Tree a, char *s) {
  c = 0;
  printf("digraph %s {\n", s);
  printf("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, a->head);
  printf("}\n");
}

void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n");
  printf("name [label = \"%s\",shape=plaintext]\n", s);
  printf("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

//
int balanceFactor(Tree a,link h){
  if(h == a->z){//-Chega na folha
    return 0;
  }
  int hR = balanceFactor(a,h->r);
  int hL = balanceFactor(a,h->l);
  if((h->l != a->z)&&(h->r != a->z)){//Verifica se os proximos nos são nulos
    h->bf = hL - hR;
  }else if(h->l != a->z){
    h->bf = h->height;
  }else{
    h->bf = -h->height;
  }
  return h->height;
}

int alturaNo(Tree a, link h) { //-Determina a altura do nó da arvore
  if(h == a->z){//Encontra nó externo
    return -1;//Folhas tem altura 0, nós externos retornam -1
  }
  int hL = alturaNo(a,h->l);//Empiplha a arvore sub-arvore esquerda
  int hR = alturaNo(a,h->r);//Empiplha a arvore sub-arvore direita
  if(hL >= hR){//Determina maior altura
    h->height = hL + 1;
  }else{
    h->height = hR + 1;
  }
  return h->height;
}

void balance(Tree a, link h){
  if(h == a->z){
    return;
  }
  balance(a,h->r);
  balance(a,h->l);
  if((h->l->bf > 1)&&(h->l->l->bf <=-1)){//Rotação esquerda-direita
    h->l->l = rotL(a,h->l->l);//Nó filho desbalanceado positivo seguido por negativo
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    h->l = rotR(a,h->l);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if((h->r->bf < -1)&&(h->r->r->bf >= 1)){
    h->r->r = rotR(a,h->r->r);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    h->r = rotL(a,h->r);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if(h->l->bf > 1){//Rotação direita no nó filho esquerdo
    h->l = rotR(a,h->l);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if(h->r->bf > 1){//Rotação direita no nó filho direito
    h->r = rotR(a,h->r);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if(h->l->bf < -1){//Rotação esquerda no nó filho esquerdo
    h->l = rotL(a,h->l);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if(h->r->bf < -1){//Rotação esquerda no nó filho direito
    h->r = rotL(a,h->r);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if((a->head->bf < -1)&&(a->head->r->bf == -1)){
    a->head = rotL(a,a->head);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }else if((a->head->bf > 1)&&(a->head->l->bf == 1)){
    a->head = rotR(a,a->head);
    alturaNo(a,a->head);
    balanceFactor(a,a->head);
    return;
  }
}

//

void AVLinsert(Tree t, link h, int item) {
  insert(t,item); //-Insere normalmente
  alturaNo(t,h);//-Determina a altura de cada nó
  balanceFactor(t,h);//-Determina fator de balancemento de cada nó
  balance(t,h);//-Balanceia a arvore
}
