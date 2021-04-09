//PRIORITY QUEUE using by BST
#include <iostream>

using namespace std;

typedef struct node{
	double key;  // key
    string val;
    struct node *left;
    struct node *right;  //left, right child
} tree_node;

class BST {
  private :
    tree_node *root;

  public :
    BST(){ root = NULL; }
    ~BST(){ delete root; }

    tree_node* modified_search(double key)
    {
      tree_node *tree = root;
      while(tree) {
        if(key == tree->key) return NULL;
        else if(key < tree->key)
          if(tree->left == NULL) { return tree; }
          else { tree = tree->left; }
        else
          if(tree->right == NULL)
          {
            return tree;
          }
          else
          {
            tree = tree->right;
          }
      }
     return NULL;
    }

    void insert_node(double key, string val)
    {
      tree_node *ptr = NULL, *parent = NULL;
      parent = modified_search(key);
      
      if(parent || isEmpty()) //in case of key is not in the tree.
      {
        ptr = new tree_node;
        ptr->key = key;
        ptr->val = val;
        ptr->left = ptr->right = NULL;
        
        if(isEmpty()) root = ptr;
        else
        {
          if(key < parent->key)
          {
            parent->left = ptr;
            parent->left->val = val;
          }
          else
          {
            parent->right = ptr;
            parent->right->val = val;
          }
        }
      }
      else  // in case of key is already in the tree.
      {
        cout << key << " is already in this queue." << endl;
        return;
      }
    }

    void delete_node(double key)
    {
      tree_node *temp = modified_search(key);
      if(temp || isEmpty()) //in case of key is not in the tree.
      {
        cout << key << " is not in the tree" << endl;
        return;
      }
      root = delete_node(root, key);
    }

    tree_node * minValueNode(tree_node* node)// return node that has the most smallest key
    {
      tree_node* current = node; // node copy
      while(current->left != NULL) // Repeat to the end of the left subtree
          current = current->left;
      return current;
    }

    tree_node* delete_node(tree_node* root, double key)
    {
        if (root == NULL) return root; // if root node is null, return null
        if (key < root->key) // if the node to delete is smaller than root
            root->left = delete_node(root->left, key); // recursive, go to left subtree
        else if (key > root->key) // if the node to delete is bigger than root
            root->right = delete_node(root->right, key); // recursive, go to left subtree

        else // if the node to delete is root node
        {
            if (root->left == NULL) // if no left child
            {
              tree_node *temp = root->right; // copy right child
              delete root; // delete
              return temp; // return right child
            }
            else if (root->right == NULL) // if no right child
            {
              tree_node *temp = root->left; // copy left child
              delete root; // delete
              return temp; // return left child
            }
            // If it has both left and right subtrees
            tree_node* temp = minValueNode(root->right); // copy the smallest the right subtree
            root->key = temp->key; // copy the value copied to the root node
            root->right = delete_node(root->right, temp->key); // recursive, go to right subtree of root

        }
        return root;
    }

    void inorder(tree_node *ptr)
    {
      if(ptr)
      {
          inorder(ptr->left);
          cout <<  "(" << ptr->key;
          cout << "," << ptr->val << ")" << endl;
          inorder(ptr->right);
      }
    }
    void PrintBST()
    {
      inorder(root); //print all node in order.
    }
    bool isEmpty()
    {
      return (root == NULL);
    }
};

int main(void)
{
	BST *tree = new BST();
    double key;
    char cmd;
    string name;

    do{
        cout << "*********** MENU ***********" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;
        cout << "P : Print out all element in queue." << endl;
        cout << "Q : Quit.\n" << endl;
        cout << "Choose menu: ";
        cin >> cmd;
        if(cmd == 'I'){
            cout << "Enter name of element: ";
            cin >> name;
            cout << "Enter key value of element: ";
            cin >> key;
            tree->insert_node(key, name);
            
        } else if(cmd == 'D') {
            cin>>key;
            tree->delete_node(key);
        } else if(cmd == 'C') {
            //tree->DecreaseBST();
        } else if(cmd == 'P') {
            tree->PrintBST();
        }
    } while(cmd != 'Q');

  return 0;
} 
