#include t.h

AVL *createNode(Town val){
  //Initialise an AVL of a structure 'Town'
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

AVL_int *createNodeint(int num){
  //Create an AVL of integers
  AVL_int *newNode = malloc(sizeof(AVL_int));
  if (newNode == NULL){
    printf("Error: Memory allocation failed\n");
    exit(1);
  }
  newNode->data = num;
  newNode->ls = NULL;
  newNode->rs = NULL;
  newNode->height = 1;
  return newNode;
}

int max(int a, int b){
  //Compare a and b and return the bigger number
  return (a > b) ? a : b;
}

int height(AVL *root){
  //return the height of the node of an AVL
  if(root == NULL){
    return 0;
  }
  return root->height;
}

int getBalance(AVL *root){
  //return the balnace of a node 
  if(root == NULL){
    return 0;
  }
  return height(root->left) - height(root->right);
}

AVL *rightRotate(AVL *root){
  // make the right rotation of a root
  AVL *x = root->left;
  AVL *y = x->right;
  x->right = root;
  root->left = y;
  root->height = max(height(root->left), height(root->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVL *leftRotate(AVL *root){
  //make the left rotation of a root
  AVL *x = root->right;
  AVL *y = x->left;
  x->left = root;
  root->right = y;
  root->height = max(height(root->left), height(root->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVL * Balance(AVL *root, int balance, Town val){
  //Check if a balance needs to be done and use the coorect fonctions if neccessary.
  if(balance > 1 && strcmp(root->left->data.name, val.name) < 0){
    return rightRotate(root);
  }
  if(balance < -1 && strcmp(root->right->data.name, val.name) > 0){
    return leftRotate(root);
  }
  if(balance > 1 && strcmp(root->left->data.name, val.name) > 0){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if(balance < -1 && strcmp(root->right->data.name, val.name) < 0){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

AVL *insert(AVL *root, Town now){
  //This function insert a structure Town inside an AVL ordered by alphabetical order and return the new AVL
  if(root == NULL){
    return createNode(now);
  }
  if(strcmp(root->data.name, now.name) < 0){
    root->left = insert(root->left, now);
  }
  else if(strcmp(root->data.name, now.name) > 0){
    root->right = insert(root->right, now);
  }
  else{
    root->data.nbr_first += now.nbr_first;
    root->data.nbr_way += 1;
    return root;
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if(balance != 0){
    root = Balance(root, balance, now);  
  }
  return root;
}

AVL * Balance2(AVL *root, int balance, Town val){
  if(balance > 1 && val.nbr_way < root->left->data.nbr_way){
    return rightRotate(root);
  }
  if(balance < -1 && val.nbr_way > root->right->data.nbr_way){
    return leftRotate(root);
  }
  if(balance > 1 && val.nbr_way > root->left->data.nbr_way){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if(balance < -1 && val.nbr_way < root->right->data.nbr_way){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

AVL *insert2(AVL *root, Town now){
  //This function insert a structure Town inside an AVL ordered by numerical order and return the new AVL
  if(root == NULL){
    return createNode(now);
  }
  if(now.nbr_way < root->data.nbr_way){
    root->left = insert2(root->left, now);
  }
  else if(now.nbr_way > root->data.nbr_way){
    root->right = insert2(root->right, now);
  }
  else{
    return root;
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if(balance != 0){
    root = Balance2(root, balance, now);  
  }
  return root;
}

void Infixe(AVL *root){
  //This function writes the town's name, the number of passage and number of time it was first
  if (root != NULL){
    Infixe(root->left);
    printf("Name: %s %d %d\n", root->data.name, root->data.nbr_first, root->data.nbr_way);
    Infixe(root->right);
  }
}

AVL * Postfixe(AVL *root,AVL *root2){
  //Takes one AVL by alphabetical and transfer it to a new AVL by numerical order
  if(root != NULL){
    root2 = Postfixe(root->left,root2);
    root2 = Postfixe(root->right,root2);
    root2 = insert2(root2,root->data);
    free(root);
  }
  return root2;
}

AVL * InfixeInv(AVL *root,AVL *root2,int*num){
  //Takes one AVL by numerical and transfer the 10 highest values to a new AVL by numerical order
  if(root != NULL && *num > 0){
    root2 = InfixeInv(root->right,root2,num);
    if(*num > 0){
      root2 = insert(root2,root->data);
      (*num) --;
    }
    root2 = InfixeInv(root->left,root2,num);
  }
  return root2;
}


void main(){
  AVL * tree = NULL;
  AVL * tree2 = NULL;
  AVL * tree3 = NULL;
  int ID,step,decr = 10;
  int * pdecr = &decr;
  Town first,second;
  first.nbr_way = 1;
  second.nbr_way = 1;
  second.nbr_first = 0;
  FILE * file = NULL;
  file = fopen("data.txt", "r");
  if(file == NULL){
    printf("Error: File not found\n");
    exit(2);
  }
  char phrase[200];
  fgets(phrase,199,file);
  while(fscanf(file,"%d %d %s %s",&ID,&step,first.name,second.name) != EOF){
    if(step == 1){
      first.nbr_first = 1;
    }
    else{
      first.nbr_first = 0;
    }
    first.IDs = createNodeint(ID);
    second.IDs = createNodeint(ID);
    tree = insert(tree,first);
    tree = insert(tree,second);
  }
  tree2 = Postfixe(tree,tree2);
  tree3 = InfixeInv(tree2,tree3,pdecr);
  fclose(file);
  Infixe(tree3);
}
