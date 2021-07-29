#pragma once
#include "Channel.h"

class RBTree {
    struct Node {
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
    Node* insertNode(Node* newRoot, Channel newChannel);

    //Helper functions
    void inorder(Node* root);
};
