#pragma once
#include "Channel.h"

class RBTree{
    struct Node{
        //Data carried
        Channel channel;

        //Node properties (true = red, false = black)
        bool color = true;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        //Constructor
        Node(Channel newChannel);
    };

private:
    Node* root = nullptr;
public:
    //Getter & Setter
    Node* getRoot();
    void setRoot(Channel newChannel);

    //Insertion
    void insertNode(Channel newChannel);
    Node* insertBSTNode(Node* newRoot, Node* parent, Node* newNode);
    void insertCorrection(Node* curr);
    void leftRotate(Node* curr);
    void rightRotate(Node* curr);
    
    //Helper functions
    void inorder(Node* root);

};