#pragma once
#include "Channel.h"
#include <vector>
#include <stack>
#include <queue>

class RBTree{
public:
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

    //Getter & Setter
    Node* getRoot();
    void setRoot(Node* newRoot);

    //Insertion
    void insertNode(Channel newChannel);
    Node* insertBSTNode(Node* newRoot, Node* parent, Node* newNode);
    void insertCorrection(Node* curr);
    void leftRotate(Node* curr);
    void rightRotate(Node* curr);

    //Helper functions
    void inorderPrint(Node* root);

    //Binary traversal
    Node* searchByID(string targetID);
    queue<Node*> searchByTopSubs(int capacity);
    queue<Node*> searchByMinSubs(int minSubCount);
    queue<Node*> searchByCategory(string targetCat, int capacity);
    queue<Node*> searchByCountry(string targetCt, int capacity);

private:
    Node* root = nullptr;
};