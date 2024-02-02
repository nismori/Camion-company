#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Step{
  int ID;
  float km;
  float max;
  float min;
  float numbr;
  float moy;
}Step;

typedef struct AVL{
  Step data;
  struct AVL *left;
  struct AVL *right;
  int height;
}AVL;

AVL *createNode(Step val);

int max(int a, int b);

int height(AVL *root);

int getBalance(AVL *root);

AVL *rightRotate(AVL *root);

AVL *leftRotate(AVL *root);

AVL * Balance(AVL *root, int balance, int val);

AVL *insert(AVL *root, Step now);

AVL * Balance2(AVL *root, int balance, float val);

AVL *insert2(AVL *root, Step now);

void Infixe(AVL *root,int* num);

AVL * Postfixe(AVL *root,AVL *root2);
