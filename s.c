#include "s.h"

AVL *createNode(Step val){
  //create a node containing a structure Step
  AVL *newNode = malloc(sizeof(AVL));
  if (newNode == NULL){
    printf("Error: Memory allocation failed\n");
    exit(1);
  }
  newNode->data = val;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}

int max(int a, int b){
  //compare two integers and return the maximum
  return (a > b) ? a : b;
}

int height(AVL *root){
  //return the height of a node
  if(root == NULL){
    return 0;
  }
  return root->height;
}

int getBalance(AVL *root){
  if(root == NULL){
    return 0;
  }
  return height(root->left) - height(root->right);
}

AVL *rightRotate(AVL *root){
  //Return the root of the tree after it was rotated to the right
  AVL *x = root->left;
  AVL *y = x->right;
  x->right = root;
  root->left = y;
  root->height = max(height(root->left), height(root->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVL *leftRotate(AVL *root){
  //Return the root of the tree after it was rotated to the left
  AVL *x = root->right;
  AVL *y = x->left;
  x->left = root;
  root->right = y;
  root->height = max(height(root->left), height(root->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVL * Balance(AVL *root, int balance, int val){
  //Search if the tree is balanced and if not : balance it.
  if(balance > 1 && val < root->left->data.ID){
    return rightRotate(root);
  }
  if(balance < -1 && val > root->right->data.ID){
    return leftRotate(root);
  }
  if(balance > 1 && val > root->left->data.ID){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if(balance < -1 && val < root->right->data.ID){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

AVL *insert(AVL *root, Step now){
  //Insert a structure Step into the AVL and return it
  if(root == NULL){
    now.max = now.km;
    now.min = now.km;
    return createNode(now);
  }
  if(now.ID < root->data.ID){
    root->left = insert(root->left, now);
  }
  else if(now.ID > root->data.ID){
    root->right = insert(root->right, now);
  }
  else{
    root->data.numbr += 1;
    root->data.km += now.km;
    if(now.km > root->data.max){
      root->data.max = now.km;
    }
    if(now.km < root->data.min){
      root->data.min = now.km;
    }
    return root;
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if(balance != 0){
    root = Balance(root, balance, now.ID);  
  }
  return root;
}

AVL * Balance2(AVL *root, int balance, float val){
  if(balance > 1 && val < root->left->data.moy){
    return rightRotate(root);
  }
  if(balance < -1 && val > root->right->data.moy){
    return leftRotate(root);
  }
  if(balance > 1 && val > root->left->data.moy){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if(balance < -1 && val < root->right->data.moy){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

AVL *insert2(AVL *root, Step now){
  if(root == NULL){
    return createNode(now);
  }
  if(now.moy < root->data.moy){
    root->left = insert2(root->left, now);
  }
  else if(now.moy > root->data.moy){
    root->right = insert2(root->right, now);
  }
  else{
    return root;
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if(balance != 0){
    root = Balance2(root, balance, now.moy);  
  }
  return root;
}

void Infixe(AVL *root,int* num){
  // Print the 50 highest data.max-data.min structure
  if(root != NULL && *num > 0){
    Infixe(root->right,num);
    if(*num > 0){
      printf("%d, %f, %f, %f \n", root->data.ID, root->data.km/root->data.numbr, root->data.max, root->data.min);
      (*num) --;
    }
    Infixe(root->left,num);
  }
}

AVL * Postfixe(AVL *root,AVL *root2){
  //Fill the first AVL into the second
  if(root != NULL){
    root->data.moy = root->data.max - root->data.min;
    root2 = Postfixe(root->left,root2);
    root2 = Postfixe(root->right,root2);
    root2 = insert2(root2,root->data);
    free(root);
  }
  return root2;
}


void main(){
  AVL * tree = NULL;
  AVL * tree2 = NULL;
  Step a;
  int b = 50;
  int* pb = &b;
  FILE * file = NULL;
  a.numbr = 1;
  a.moy = 0;
  file = fopen("data.txt", "r+");
  if(file == NULL){
    printf("Ouverture du fichier impossible\n");
    exit(2);
  }
  char phrase[200];
  fgets(phrase,199,file);
  while(fscanf(file,"%d;%f",&a.ID,&a.km) != EOF){
    tree = insert(tree, a);
  }
  fclose(file);
  tree2 = Postfixe(tree,tree2);
  Infixe(tree2,pb);
}
