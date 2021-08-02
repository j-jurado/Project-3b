#include "NTree.h"
#include <queue>
#include <cmath>
using namespace std;

/*=== Node Class Functions ===*/

//Constructor
NTree::Node::Node(Channel c, Node* newParent){
    this->channel = c;
    this->parent = newParent;
}

/*=== NTree Class Functions ===*/

//Constructor
NTree::NTree(int newDegree){
    this->degree = newDegree;
    this->root = nullptr;
}

//Getter & Setter
NTree::Node *NTree::getRoot(){
    return this->root;
}
void NTree::setRoot(Node *newRoot){
    this->root = newRoot;
}

/*= Insertion =*/
void NTree::insertNode(Node* c, Node* prev){
    //Citation: Inspired by section 27.10 in OpenDSA

    /* This insertion method inserts nodes by top down level order,
     * meaning that all possible bins are filled before
     * moving onto a lower level*/

    if(this->root == nullptr){
        root = c;
        lineWidth = 0;
        height = 1;
        return;
    }
    //If a bin still has space
    else if(prev->parent->children.size() < degree){
        prev->parent->children.push_back(c);
        lineWidth++;
        c->parent = prev->parent;
    }
    //If all bins in a row are full
    else if(lineWidth ==  pow(degree, height)){
        Node *curr = root;

        while(curr->children.size() != 0){
            curr = curr->children[0];
        }
        curr->children.push_back(c);
        c->parent = curr;
        height++;
        lineWidth = 1;
    }
    //If a bin is full, but there are successor bins down the row
    else{
        queue<Node*> childrenNodes;
        childrenNodes.push(root);
        while(!childrenNodes.empty()){
            if(childrenNodes.front()->children.size() == 0){
                childrenNodes.front()->children.push_back(c);
                c->parent = childrenNodes.front();
                break;
            }
            for(int i = 0; i < childrenNodes.front()->children.size(); i++){
                childrenNodes.push(childrenNodes.front()->children[i]);
            }
            childrenNodes.pop();
        }
        lineWidth++;
    }
}

/*= Helper Functions =*/

//Level order printer for debugging purposes
void NTree::levelPrint(){
    queue<Node*> printQ;
    printQ.push(root);
    int parentCount = 1;

    //Enqueue parent nodes, enqueue their children, print parent nodes, pop all parent nodes
    while(!printQ.empty()){
        for(int j = 0; j < parentCount; j++){
            cout << printQ.front()->channel.getID() << " ";
            for(int i = 0; i < printQ.front()->children.size(); i++){
                printQ.push(printQ.front()->children[i]);
            }
            printQ.pop();
        }
        cout << endl;
        parentCount = printQ.size();
    }
}

void NTree::smallPrint(Node *curr){
    cout << "Title: " << curr->channel.getTitle() << endl;
    cout << "Subscribers: " << curr->channel.getSubCount() << endl;
    cout << "Channel ID: " << curr->channel.getID() << endl;
    cout << "---------------------------------------" << endl;
}

void NTree::largePrint(Node *curr){
    cout << "Title: " << curr->channel.getTitle() << endl;
    cout << "Subscribers: " << curr->channel.getSubCount() << endl;
    cout << "Video Count: " << curr->channel.getVidCount() << endl;
    cout << "Category: " << curr->channel.getCategory() << endl;
    cout << "Country: ";
    if (curr->channel.getCountry() == "")
        cout << "N/A" << endl;
    else
        cout << curr->channel.getCountry() << endl;
    cout << "Join Date: " << curr->channel.getJoinDate() << endl;
    cout << "Channel ID: " << curr->channel.getID() << endl;
    cout << "Profile URl: " << curr->channel.getProfileURL() << endl;
    cout << "---------------------------------------" << endl;
}

/*= Search Functions =*/

//Level order search that returns target Node
NTree::Node *NTree::searchByID(string targetID){
    queue<Node*> searchQ;
    searchQ.push(root);
    int parentCount = 1;

    //Level order search for ID
    while(!searchQ.empty()){
        for(int j = 0; j < parentCount; j++){
            if(searchQ.front()->channel.getID() == targetID)
                return searchQ.front();
            for(int i = 0; i < searchQ.front()->children.size(); i++){
                searchQ.push(searchQ.front()->children[i]);
            }
            searchQ.pop();
        }
        parentCount = searchQ.size();
    }
}