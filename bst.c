/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Chung-Yu, Yang
 * Email: yangchun@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"
#include <assert.h>

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
struct bst_node {
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
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create(int val) 
{
  struct bst* tree = malloc(sizeof(struct bst));
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
void free_bst_node(struct bst_node* node) 
{
  if (node->left == NULL && node->right == NULL) 
  {
    free(node);
  }
  else if (node->right != NULL) 
  {
    free_bst_node(node->right);
  }
  else (node->left != NULL);
  {
    free_bst_node(node->left);
  }
  free(node);
}

void bst_free(struct bst* bst) 
{
  free_bst_node(bst->root);
  free(bst);
  return;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */

int bst_subtree(struct bst_node* root)
{
  int size = 1;
  //number nodes in right tree of root
  if(root->right != NULL)
  {
    size += bst_subtree(root->right);
  }
  //number nodes in left tree of root
  if(root->left != NULL)
  {
    size += bst_subtree(root->left);
  }
return size;
}

int bst_size(struct bst* bst) 
{
  assert(bst);
  int size = 0;
  if(bst->root != NULL)
  {
    size = bst_subtree(bst->root);
  }
  return size;
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
void bst_insert(struct bst* bst, int key, void* value) 
{
  struct bst_node* ptr;
  struct bst_node* tree = malloc(sizeof(struct bst_node));
    
  tree->key = key;
  tree->value = value;
  tree->right = NULL;
  tree->left = NULL;
  
  if(bst->root == NULL)
  {
    bst->root = tree;
    return;
  }
  else {
    ptr = bst->root;
  }
  //using the while to insert check the key for the left side 
  //and right side
  int node = 1;
  while(node == 1)
  {
    if(tree->key >= ptr->key)
    {
      if(ptr->right == NULL)
      {
        node = 0;
        ptr->right = tree;
      }
      else 
        ptr = ptr->right;
    }
    else if(tree->key < ptr->key)
    {
      if(ptr->left == NULL)
      {
        node = 0;
        ptr->left = tree;     
      }
      else 
        ptr = ptr->left;
    }
  }
  return;
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
void bst_remove(struct bst* bst, int key) 
{
  struct bst_node* node_n = bst->root;
  struct bst_node* prve = NULL;

  while(node_n != NULL && key != node_n->key)
  {
    prve = node_n;
    if(key < node_n->key)
    {
      node_n = node_n->left;
    }
    else if (node_n->key < key)
    {
      node_n = node_n->right;
    }
    else break;
  }
  //Check if the node left and right is the NULL
  if(node_n->left == NULL && node_n->right == NULL)
  {
    if(node_n == prve->left)
    {
      prve->left = NULL;
    }
    else
      prve->right = NULL;
  }
  //Check if the left is not NULL and if right node is NULL
  else if(node_n->left != NULL && node_n->right == NULL)
  {
    if(node_n == prve->left)
    {
      prve->left = node_n->left;
    }
    else
      prve->right = node_n->left;
  }
  //Check if the right is not NULL and if left node is NULL
  else if(node_n->left == NULL && node_n->right != NULL)
  {
    if(node_n == prve->left)
    {
      prve->left = node_n->right;
    }
    else
      prve->right = node_n->right;
  }
  
  else {
    struct bst_node* node_s;
    struct bst_node* parent_s;

    node_s = node_n->right;
    parent_s = node_n;
    while(node_s->left != NULL && node_s != NULL)
    {
      parent_s = node_s;
      node_s = node_s->left;
    }
      node_s->left = node_n->left;
      if(node_s != node_n->right)
      {
        parent_s->left = node_s->right;
        node_s->right = node_n->right;
      }
      if (prve == NULL)
      {
        bst->root = node_s;
      }
      else if(node_n == prve->left)
      {
        prve->left = node_s;
      }
      else
        prve->right = node_s;
  }
  free(node_n);
  return;
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

void* get_bst_node(struct bst_node *ptr, int key) 
{
  if(ptr == NULL) 
    return NULL;

  else if(ptr->key == key) 
    return ptr->value;

  else if(key < ptr->key) 
    return get_bst_node(ptr->left, key);

  else 
    return get_bst_node(ptr->right, key);
}

void* bst_get(struct bst* bst, int key) 
{
  if(bst == NULL)
    return NULL;

  return get_bst_node(bst->root, key);
}


/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
int bst_height_val(struct bst_node* root)
{
  if(root == NULL)
  {
    return -1;
  }
  int left = bst_height_val(root->left);
  int right = bst_height_val(root->right);
    return left > right ? left +1 : right +1;
}

 int bst_height(struct bst* bst) 
 {
  return bst_height_val(bst->root);
 }

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  return 0;//bst_path_sum_tree(sum, bst->root);
}

/*int bst_path_sum_tree(int sum, struct bst_node* ptr)
{
  if(ptr == NULL)
    return 0;
    
  if(ptr->left == NULL && ptr->right == NULL)
    return 1;
  int left = bst_path_sum_tree(sum, ptr->left);
  int right = bst_path_sum_tree(sum, ptr-right);
    return left || right;
}*/

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */

int get_bst_range_sum(struct bst_node* ptr, int lower, int upper)
{
  if (ptr == NULL) {
    return 0;
  }
    else if(ptr->key > upper)
    {
      return get_bst_range_sum(ptr->left, lower, upper);
    }
    else if(ptr->key < lower)
    {
      return get_bst_range_sum(ptr->right, lower, upper);
    }
  else
    return ptr->key + get_bst_range_sum(ptr->left, lower, upper) + get_bst_range_sum(ptr->right, lower, upper);
}

int bst_range_sum(struct bst* bst, int lower, int upper) 
{
  return get_bst_range_sum(bst->root, lower, upper);
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if (value) {
    *value = NULL;
  }
  return 0;
}
