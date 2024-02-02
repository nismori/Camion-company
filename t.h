#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct AVL_int{
  int data;
  struct AVL_int *ls;
  struct AVL_int *rs;
  int height;
}AVL_int;

typedef struct Town{
  char name[60];
  AVL_int *IDs;
  int nbr_way;
  int nbr_first;
}Town;

typedef struct AVL{
  Town data;
  struct AVL *left;
  struct AVL *right;
  int height;
}AVL;

AVL *createNode(Town val);

AVL_int *createNodeint(int num);

int max(int a, int b);

int height(AVL *root);

int getBalance(AVL *root);

AVL *rightRotate(AVL *root);

AVL *leftRotate(AVL *root);

AVL * Balance(AVL *root, int balance, Town val);

AVL *insert(AVL *root, Town now);

AVL * Balance2(AVL *root, int balance, Town val);

AVL *insert2(AVL *root, Town now);

void Infixe(AVL *root);

AVL * Postfixe(AVL *root,AVL *root2);

AVL * InfixeInv(AVL *root,AVL *root2,int*num);
