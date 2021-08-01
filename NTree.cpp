#include "NTree.h"
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*=== Node Class Functions ===*/

//Constructor
NTree::Node::Node(Channel c, Node* newParent) {
    this->channel = c;
}

/*=== NTree Class Functions ===*/

//Constructor
NTree::NTree(int newDegree) {
    this->degree = newDegree;
    this->root = nullptr;
}

//Getter & Setter
NTree::Node *NTree::getRoot() {
    return this->root;
}
void NTree::setRoot(Node *newRoot) {
    this->root = newRoot;
}

/*= Insertion =*/
void NTree::insertNode(Channel c) {
    //Citation: Inspired by section 27.10 in OpenDSA

    /* This insertion method inserts nodes by top down level order,
     * meaning that all possible bins are filled before
     * moving onto a lower level*/

    if(this->root == nullptr){
        root = new Node(c, nullptr);
        return;
    }
    queue<Node*> visitedNodes;
    visitedNodes.push(root);
    //If a node's bin is completely filled...
    while(visitedNodes.front()->children.size() == degree){
        //Keep track of the node's children and move onto the successor node in level order
        Node* curr = visitedNodes.front();
        for(int i = 0; i < curr->children.size(); i++){
            visitedNodes.push(curr->children[i]);
        }
        visitedNodes.pop();
    }
    //If a node's bin has an open spot, place a node there
    if(visitedNodes.front()->children.size() < degree){
        Node* newNode = new Node(c, visitedNodes.front());
        visitedNodes.front()->children.push_back(newNode);
    }
}

/*= Helper Functions =*/

//Level order printer for debugging purposes
void NTree::levelPrint() {
    queue<Node*> printQ;
    printQ.push(root);
    int parentCount = 1;

    //Enqueue parent nodes, enqueue their children, print parent nodes, pop all parent nodes
    while(!printQ.empty()){
        for(int j = 0; j < parentCount; j++){
            cout << printQ.front()->channel.getTitle() << " ";
            for(int i = 0; i < printQ.front()->children.size(); i++){
                printQ.push(printQ.front()->children[i]);
            }
            printQ.pop();
        }
        cout << endl;
        parentCount = printQ.size();
    }
}