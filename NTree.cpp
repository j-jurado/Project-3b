#include "NTree.h"
#include <queue>
#include <cmath>
#include <algorithm>
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
        Node* curr = prev->parent;
        //Repeatedly backtracks up a level until a new spot is found
        while(true){
            queue<Node*> childrenNodes;
            childrenNodes.push(prev);
            int currWidth = 0;
            while(!childrenNodes.empty()){
                if(childrenNodes.front()->children.size() == 0 && currWidth < lineWidth){
                    childrenNodes.front()->children.push_back(c);
                    c->parent = childrenNodes.front();
                    lineWidth++;
                    return;
                }
                for(int i = 0; i < childrenNodes.front()->children.size(); i++){
                    childrenNodes.push(childrenNodes.front()->children[i]);
                    currWidth++;
                }
                childrenNodes.pop();
                currWidth--;
            }
            curr = curr->parent;
        }
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

//Level order search that returns queue of size #capacity with top channels
queue<NTree::Node *> NTree::searchByTopSubs(int capacity) {
    queue<Node*> searchQ;
    queue<Node*> returnQ;
    vector<Node*> nodes;
    searchQ.push(root);
    int parentCount = 1;

    //Level order search for top channels
    while(!searchQ.empty()){
        for(int j = 0; j < parentCount; j++){
            for(int i = 0; i < searchQ.front()->children.size(); i++){
                searchQ.push(searchQ.front()->children[i]);
            }
            nodes.push_back(searchQ.front());
            searchQ.pop();
        }
        parentCount = searchQ.size();
    }
    //Data must be sorted since CSV file data is NOT completely sorted
    sort(nodes.begin(), nodes.end(), [](Node* lhs, Node* rhs){return lhs->channel.subscriberCount < rhs->channel.subscriberCount;});
    int index = nodes.size()-1;
    for(int i = 0; i < capacity; i++) {
        returnQ.push(nodes[index]);
        index--;
    }
    return returnQ;
}

//Level order search that returns queue of all channels with < minSubCount
queue<NTree::Node *> NTree::searchByMinSubs(int minSubCount) {
    queue<Node*> searchQ;
    queue<Node*> returnQ;
    vector<Node*> nodes;
    searchQ.push(root);
    int parentCount = 1;

    //Level order search
    while(!searchQ.empty()){
        for(int j = 0; j < parentCount; j++){
            for(int i = 0; i < searchQ.front()->children.size(); i++){
                searchQ.push(searchQ.front()->children[i]);
            }
            nodes.push_back(searchQ.front());
            searchQ.pop();
        }
        parentCount = searchQ.size();
    }
    //Data must be sorted since CSV file data is NOT completely sorted
    sort(nodes.begin(), nodes.end(), [](Node* lhs, Node* rhs){return lhs->channel.subscriberCount < rhs->channel.subscriberCount;});
    int index = nodes.size()-1;
    while(nodes[index]->channel.getSubCount() > minSubCount){
        returnQ.push(nodes[index]);
        index--;
    }
    return returnQ;
}

//Level order search that returns queue of size #capacity of top channels in target category
queue<NTree::Node *> NTree::searchByCategory(string targetCat, int capacity) {
    queue<Node*> searchQ;
    queue<Node*> returnQ;
    vector<Node*> nodes;
    searchQ.push(root);
    int parentCount = 1;

    //Level order search of category
    while(!searchQ.empty()){
        for(int j = 0; j < parentCount; j++){
            for(int i = 0; i < searchQ.front()->children.size(); i++){
                searchQ.push(searchQ.front()->children[i]);
            }
            if(searchQ.front()->channel.getCategory() == targetCat){
                nodes.push_back(searchQ.front());
            }
            searchQ.pop();
        }
        parentCount = searchQ.size();
    }
    //Data must be sorted since CSV file data is NOT completely sorted
    sort(nodes.begin(), nodes.end(), [](Node* lhs, Node* rhs){return lhs->channel.subscriberCount < rhs->channel.subscriberCount;});
    for(int i = 1; i <= capacity; i++){
        if(i < nodes.size())
            returnQ.push(nodes[nodes.size()-i]);
    }
    return returnQ;
}

//Level order search that returns queue of size #capacity of top channels in target country
queue<NTree::Node *> NTree::searchByCountry(string targetCt, int capacity) {
    queue<Node*> searchQ;
    queue<Node*> returnQ;
    vector<Node*> nodes;
    searchQ.push(root);
    int parentCount = 1;

    //Level order search of country
    while(!searchQ.empty()){
        for(int j = 0; j < parentCount; j++){
            for(int i = 0; i < searchQ.front()->children.size(); i++){
                searchQ.push(searchQ.front()->children[i]);
            }
            if(searchQ.front()->channel.getCountry() == targetCt){
                nodes.push_back(searchQ.front());
            }
            searchQ.pop();
        }
        parentCount = searchQ.size();
    }
    //Data must be sorted since CSV file data is NOT completely sorted
    sort(nodes.begin(), nodes.end(), [](Node* lhs, Node* rhs){return lhs->channel.subscriberCount < rhs->channel.subscriberCount;});
    for(int i = 1; i <= capacity; i++){
        if(i < nodes.size())
            returnQ.push(nodes[nodes.size()-i]);
    }
    return returnQ;
}