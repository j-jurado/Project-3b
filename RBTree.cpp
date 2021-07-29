#include "RBTree.h"
#include <iostream>
using namespace std;

/*=== Node class functions ===*/

RBTree::Node::Node(Channel newChannel) {
    this->channel = newChannel;
}


/*=== RBTree class functions ===*/

//Getter & Setter
RBTree::Node *RBTree::getRoot() {
    return this->root;
}
void RBTree::setRoot(Channel newChannel) {
    this->root = new Node(newChannel);
}

//Prints inorder nodes for debugging purposes
void RBTree::inorder(Node *root) {
    //Citation: Inspired by algo in slide 37 of Trees-1 ppt
    if(root == nullptr){
        cout << "";
    }
    else{
        inorder(root->left);
        cout << root->channel.getTitle() << " ";
        inorder(root->right);
    }
}
//Normal BST insertion BEFORE any corrections
RBTree::Node *RBTree::insertNode(RBTree::Node *newRoot, Channel newChannel) {
    //Citation: Inspired by algo in slide 31 of Trees-1 ppt
    if (newRoot == nullptr)
        return new Node(newChannel);
    if (newChannel.getSubCount() < newRoot->channel.getSubCount())
        newRoot->left = insertNode(newRoot->left, newChannel);
    else
        newRoot->right = insertNode(newRoot->right, newChannel);
}

