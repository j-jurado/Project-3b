#include "RBTree.h"
#include <iostream>
using namespace std;

/*=== Node class functions ===*/

RBTree::Node::Node(Channel newChannel){
    this->channel = newChannel;
}


/*=== RBTree class functions ===*/

//Getter & Setter
RBTree::Node *RBTree::getRoot(){
    return this->root;
}
void RBTree::setRoot(Channel newChannel){
    this->root = new Node(newChannel);
}

//Prints nodes w/ color in order for debugging purposes
void RBTree::inorder(Node *root){
    if(root == nullptr){
        cout << "";
    }
    else{
        inorder(root->left);
        cout << root->channel.getID() << " : " << root->color << endl;
        inorder(root->right);
    }
}

//Insert new Channel node into RB tree (Use this in main)
void RBTree::insertNode(Channel newChannel){
    Node* newNode = new Node(newChannel);
    insertBSTNode(root, nullptr, newNode);
    insertCorrection(newNode);
}

//Normal BST insertion BEFORE any corrections
RBTree::Node *RBTree::insertBSTNode(Node* newRoot, Node* parent, Node* newNode){
    //Base case
    if (newRoot == nullptr){
        newRoot = newNode;
        newRoot->parent = parent;
        newRoot->color = true;

        //If tree is empty
        if(root == nullptr){
            root = newRoot;
            root->parent = nullptr;
            root->color = false;
        }
        return newRoot;
    }
    if (newNode->channel.getID() < newRoot->channel.getID())
        newRoot->left = insertBSTNode(newRoot->left, newRoot, newNode);
    else
        newRoot->right = insertBSTNode(newRoot->right, newRoot, newNode);
    return newRoot;
}

//Recolors and rotates inserted BST nodes to accommodate RB Tree rules
void RBTree::insertCorrection(Node *curr){
    //Citation: Inspired by balancing algo in Professor Resch's RBTree ppt slide 5
    
    //Recoloring based on root status
    if(curr->parent == nullptr){
        curr->color = false;
        root = curr;
        return;
    }
    //Do nothing if curr has a black parent
    if(curr->parent->color == false){
        return;
    }
    
    //Mapping parent and grandparent
    Node* parent = curr->parent;
    Node* grandparent = curr->parent->parent;
    
    //Mapping correct uncle
    Node* uncle = nullptr;
    if(curr->parent == curr->parent->parent->right && curr->parent->parent->left != nullptr){
        uncle = curr->parent->parent->left;
    }
    else if(curr->parent == curr->parent->parent->left && curr->parent->parent->right != nullptr){
        uncle = curr->parent->parent->right;
    }

    //Recoloring based on uncle's color
    if(uncle != nullptr && uncle->color == true){
        parent->color = false;
        grandparent->color = true;
        uncle->color = false;
        insertCorrection(grandparent);
        return;
    }
    //Only makes it this far if a rotation is needed
    
    //If curr is a left-right child, it requires a primary left rotation
    if(curr == parent->right && parent == grandparent->left){
        leftRotate(parent);
        curr = parent;
        parent = curr->parent;
    }
    //If curr is a right-left child, it requires a primary right rotation
    else if (curr == parent->left && parent == grandparent->right){
        rightRotate(parent);
        curr = parent;
        parent = curr->parent;
    }

    if (parent != nullptr)
        parent->color = false;
    if (grandparent != nullptr)
        grandparent->color = true;

    //Final rotations
    if(parent != nullptr){
        if(grandparent != nullptr){
            if(curr == parent->left)
                rightRotate(grandparent);
            else
                leftRotate(grandparent);
        }
    }
}

//Citation: Rotations inspired by rotation algo in slide 27 Trees-3 ppt
void RBTree::leftRotate(Node *curr){
   //Initial assigning
    Node* newParent = curr->right;
    curr->right = newParent->left;

    //Assigns the left child of the new Parent to the current node
    if(newParent->left != nullptr)
        newParent->left->parent = curr;

    //Assigns the parent of the current node to the new parent
    newParent->parent = curr->parent;
    if(curr->parent == nullptr)
        root = newParent;
    else if (curr == curr->parent->left)
        curr->parent->left = newParent;
    else
        curr->parent->right = newParent;

    //Final assigning
    newParent->left = curr;
    curr->parent = newParent;
}

void RBTree::rightRotate(Node *curr){
    //Initial Assigning
    Node* newParent = curr->left;
    curr->left = newParent->right;

    //Assigns the right child of the new parent to the current node
    if(newParent->right != nullptr)
        newParent->right->parent = curr;

    //Assigns the parent of the current node to the new parent
    newParent->parent = curr->parent;
    if(curr->parent == nullptr)
        root = newParent;
    else if (curr == curr->parent->right)
        curr->parent->right = newParent;
    else
        curr->parent->left = newParent;

    //Final assigning
    newParent->right = curr;
    curr->parent = newParent;
}