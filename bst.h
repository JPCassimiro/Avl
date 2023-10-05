#ifndef BST_H
#define BST_H

typedef struct node *link;
struct node {
  link l;
  link r;
  int item;
  int N;      // quantidade de nos na subarvore
  int bf;     //-Fator de balancemento
  int id;     // id da nó
  int height; //-Altura do no
};

typedef struct tree {
  link head; // raiz
  link z;    // nó externo
} * Tree;

Tree createTree();

link rotR(Tree t, link h);

link rotL(Tree t, link h);

link search(Tree h, int query);

link insert(Tree h, int item);

void imprimeEmOrdem(Tree t, link h);
void imprimePosOrdem(Tree t, link h);
void imprimePreOrdem(Tree t, link h, int k);

void AVLinsert(Tree t, link h, int item);//Func alterada

void imprime(Tree a, char *s);
// Funções adicionadas por mim
int balanceFactor(Tree a, link h);
int alturaNo(Tree a, link h);
void balance(Tree a, link h);
//
#endif