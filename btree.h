/**
 * @file btree.h
 * @author Sophia Deak
 * @date August 2018
 * @brief header file w function definitions for b tree
 **/

#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
typedef struct tree BTree;
typedef struct node Node;

/**
 * @brief node struct for b+ tree 
 *
 */
struct node{
    bool leaf;  ///< flag indicating if node is leaf or middle
    int degree;       ///< degree (or order) of tree which node belongs to
    int numberOfKeys; ///< number of keys in the node
    BTree *myTree;  ///< tree pointer to tree which node belongs to
    Node *parent; ///< node pointer to parent of node
    void **keys; ///< void array of keys
    
    Node **children; ///< node pointer array containing children of node (only in middle nodes)
    void **data; ///< void pointer array of data (only in leaf nodes)
};

/**
 * @brief tree struct of b+ tree
 */

struct tree {
    int degree; ///< degree of tree
    Node *root; ///< node pointer to root of tree
    int (*compare)(void *data1, void *data2); ///< function pointer to compare data 
    void (*destroy)(void *data); ///< function pointer to destroy data
    void (*print)(void *data); ///< function pointer to print data
};


/**
 * @brief creates and initializes a leaf node
 * @param[in] degree  the degree of the node
 * @return Node pointer to newly created node
 */
Node *createleafNode(int degree);

/**
 * @brief creates and initializes a middle node
 * @param[in] degree of node
 * @return Node pointer to newly created middle node
 */
Node *createMidNode(int degree);

/**
 * @brief creates a empty b+ tree structure
 * @param[in] degree  the degree of the tree
 * @param[in] compare  function to compare data type contained in tree
 * @param[in] destroy   function to destroy the datatype contained in tree
 * @param[in] print     function to print datatype contained in tree
 */
BTree *createBTree(int degree, 
                   int (*compare)(void *data1, void *data2),
                   void (*destroy)(void *data),
                   void (*print)(void *data));
/**
 * @brief inserts a key/data pair to a tree
 * @param[out] root  Node pointer of root to insert to
 * @param[in]  key   void pointer of key to insert
 * @param[in]  data  void pointer of data to insert
 */
Node *insert(Node *root, void *key, void *data);

/* inserts a key/data pair to a leaf node
 * @param theLeaf leafNode pointer to node to insert to
 * @param key void ptr to key to insert
 * @param data void ptr to data to insert
 * @return leafNode ptr of leafNode with key and data inserted
 **/
Node * insertToLeaf(Node *theLeaf, void *key, void *data);

Node *insertToMiddle(Node *theMiddle, void *key, Node *leftChild, Node *rightChild);

Node *insertAbove(Node *theNode, void *key, Node *leftChild, Node *rightChild);
//return pointer to new root node
Node *splitNode(Node *theNode);

Node *findLeaf(Node *root, void *key);
#endif
