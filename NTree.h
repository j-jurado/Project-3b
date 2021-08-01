#pragma once
#include "Channel.h"
#include <vector>

class NTree {
    struct Node{
        //Data Carried
        Channel channel;

        //Node properties
        vector<Node*> children;

        //Constructor
        Node(Channel c, Node* parent);
    };
public:
    //Constructor
    NTree(int newDegree);

    //Getter & setter
    Node* getRoot();
    void setRoot(Node* newRoot);

    //Insertion
    void insertNode(Channel c);

    //Helper functions
    void levelPrint();

private:
    Node* root = nullptr;
    //The order of the tree (maximum num children)
    int degree = 0;
};