#pragma once
#include "Channel.h"
#include <vector>
#include <queue>

class NTree{
public:
    struct Node{
        //Data Carried
        Channel channel;

        //Node properties
        vector<Node*> children;
        Node* parent;

        //Constructor
        Node(Channel c, Node* parent);
    };
    //Constructor
    NTree(int newDegree);

    //Getter & setter
    Node* getRoot();
    void setRoot(Node* newRoot);

    //Insertion
    void insertNode(Node* c, Node* prev);

    //Helper functions
    void levelPrint();
    void smallPrint(Node* curr);
    void largePrint(Node* curr);
    Node* recursiveFind(Node* curr);
    Node* recursiveFind2(Node* curr);

    //Search functions
    Node* searchByID(string targetID);
    queue<Node*> searchByTopSubs(int capacity);
    queue<Node*> searchByMinSubs(int minSubCount);
    queue<Node*> searchByCategory(string targetCat, int capacity);
    queue<Node*> searchByCountry(string targetCt, int capacity);

    int height;
    int lineWidth;

private:
    Node* root = nullptr;
    //The order of the tree (maximum num children)
    int degree = 0;
};