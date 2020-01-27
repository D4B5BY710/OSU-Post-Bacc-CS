/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <assert.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node
{
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst
{
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create()
{
  struct bst* tree = malloc(sizeof(struct bst));

  assert(tree);

  tree->root = NULL;

  return tree;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */

void freeBST(struct bst_node* node)
{
  if(node != NULL)
  {
    freeBST(node->left);
    freeBST(node->right);
    free(node);
  }
}

void bst_free(struct bst* bst)
{
  freeBST(bst->root);
  free(bst);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bstRecursiveSize(struct bst_node* node)
{
  if(node != NULL)
  {
    return(1 + bstRecursiveSize(node->left) + bstRecursiveSize(node->right));
  }
  else
  {
   return 0;
  }
}

int bst_size(struct bst* bst)
{
  return bstRecursiveSize(bst->root);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

struct bst_node* nodeStructure(int key, void* value)
{
  struct bst_node* newNode = malloc(sizeof(struct bst_node));

  assert(newNode);

  newNode->key = key;
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

struct bst_node* insertRec(struct bst_node* node, int key, void* value)
{
  if(node == NULL)
  {
    return nodeStructure(key, value);
  }
  else if(node->key > key)
  {
    node->left = insertRec(node->left, key, value);
  }
  else
  {
    node->right = insertRec(node->right, key, value);
  }

  return node;
}

void bst_insert(struct bst* bst, int key, void* value)
{
  bst->root = insertRec(bst->root, key, value);
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */

struct bst_node* findLeftMostNode(struct bst_node* node)
{
  while(node->left != NULL)
  {
    node = node->left;
  }

  return node;
}

struct bst_node* removeRec(struct bst_node* node, int key)
{
  struct bst_node* tempNode;

  if(node == NULL)
  {
    return node;
  }

  if(node->key > key)
  {
    node->left = removeRec(node->left, key);
  }
  else if(node->key < key)
  {
    node->right = removeRec(node->right, key);
  }
  else
  {
    if(node->right == NULL)
    {
      tempNode = node->left;
      free(node);

      return tempNode;
    }
    else if(node->left == NULL)
    {
      tempNode = node->right;
      free(node);

      return tempNode;
    }

    tempNode = findLeftMostNode(node->right);

    node->key = tempNode->key;

    node->right = removeRec(node->right, tempNode->key);
  }

  return node;
}

void bst_remove(struct bst* bst, int key)
{
  bst->root = removeRec(bst->root, key);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key)
{
  struct bst_node* node = bst->root;

  while(node != NULL)
  {
    if(node->key == key)
    {
      return node;
    }
    else if(node->key > key)
    {
      node = node->left;
    }
    else
    {
      node = node->right;
    }
  }

  return NULL;
}
