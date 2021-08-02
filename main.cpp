#include "RBTree.h"
#include "Channel.h"
#include "NTree.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

RBTree::Node* parseCSVinRBTree();
NTree::Node* parseCSVinNTree(int degree);
void printMainMenu();
void printSubMenu();
typedef high_resolution_clock Clock;

int main(){

    cout << "*********************************\n"
            "*   Youtube Channel Analytics   *\n"
            "*********************************\n"
            "* Filter, search, and view the  *\n"
            "* statistics of the top Youtube *\n"
            "* channels all in one place!    *\n"
            "*********************************\n";

    cout << endl;
    cout << "Lets get started!" << endl;
    cout << "1. Parse CSV data" << endl;
    cout << "2. Exit program" << endl;
    cout << "Please make a selection:";



    int option = -1;
    cin >> option;

    if(option == 0){
        return 0;
    }
    else if (option == 1){

        cout << endl;
        cout << "Enter a base n for the N-ary Tree:";
        int degree;
        cin >> degree;

        cout << "Parsing..." << endl;
        cout << endl;
        RBTree rbTree;
        NTree nTree(degree);

        auto t1 = Clock::now();
        rbTree.setRoot(parseCSVinRBTree());
        auto t2 = Clock::now();
        cout << "Red-Black Tree parse time: " << duration<double>(t2-t1).count() << " seconds" << endl;

        t1 = Clock::now();
        nTree.setRoot(parseCSVinNTree(degree));
        t2 = Clock::now();
        cout << "N-ary Tree parse time: " << duration<double>(t2-t1).count() << " seconds" << endl;
        cout << endl;


        while(true){
            printMainMenu();
            cin >> option;
            cout << endl;

            if (option == 1){
                cout << "---------- Search by Top Subs ---------" << endl;
                cout << "Enter number of channels to display:";
                int capacity;
                cin >> capacity;
                t1 = Clock::now();
                queue<RBTree::Node*> q = rbTree.searchByTopSubs(capacity);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<nanoseconds>(t2-t1).count() << " nanoseconds" << endl;
                cout << endl;
                printSubMenu();
                cin >> option;
                cout << endl;
                cout << "Displaying top " << capacity << " channels..." << endl;
                cout << endl;
                while(!q.empty()){
                    if(option == 1)
                        rbTree.smallPrint(q.front());
                    else if (option == 2)
                        rbTree.largePrint(q.front());
                    q.pop();
                }
                cout << endl;
            }
            else if (option == 2){

            }
            else if (option == 3){

            }
            else if (option == 4){

            }
            else if (option == 5){

            }
            else if(option == 6){
                return 0;
            }
            else{
                cout << "Error: Enter a value from the menu" << endl;
            }

        }
    }

    return 0;
}

//Parses CSV cells and inserts them into RBTree. Returns root node of new RBTree
RBTree::Node* parseCSVinRBTree(){
    string line;
    //Line vector to track all cells, or fields, of the line
    vector<string> fullLine;
    ifstream file("channels.csv");

    RBTree tree;

    if (file.is_open()){
        //Extract first line
        getline(file, line);

        //While there is a line to read
        while(getline(file,line)){
            istringstream stream(line);
            bool quoteStatus = true;
            string cell;
            string newCell;

            //Keeps reading over cells that have commas in quotes not meant to be delimiters
            while(getline(stream, cell, ',')){
                if(count(cell.begin(), cell.end(), '"') % 2 != 0){
                    quoteStatus = !quoteStatus;
                }
                string tempComma;
                if(quoteStatus)
                    tempComma = "";
                else
                    tempComma = ",";
                newCell += cell + tempComma;
                if(quoteStatus){
                    fullLine.push_back(newCell);
                    newCell.clear();
                }
            }

            //Creates appropriate variables from CSV cells
            int categoryID = stoi(fullLine[0]);
            string category = fullLine[1];
            string channelID = fullLine[2];
            string country = fullLine[3];
            int subscriberCount = stoi(fullLine[4]);
            string joinDate = fullLine[5];
            string pictureURL = fullLine[6];
            string profileURL = fullLine[7];
            string title = fullLine[8];
            int videoCount = stoi(fullLine[9]);

            //Creates channel object and inserts appropriate values
            Channel c;
            c.setID(channelID);
            c.setTitle(title);
            c.setCategory(category);
            c.setCountry(country);
            c.setJoinDate(joinDate);
            c.setPictureURL(pictureURL);
            c.setProfileURL(profileURL);
            c.setSubCount(subscriberCount);
            c.setVidCount(videoCount);
            c.setCategoryID(categoryID);

            //Inserts channel into RBTree and clears the line vector
            tree.insertNode(c);
            fullLine.clear();
        }
    }
    return tree.getRoot();
}

//Parses CSV cells and inserts them into NTree. Returns root node of new NTree
NTree::Node* parseCSVinNTree(int degree){
    string line;
    //Line vector to track all cells, or fields, of the line
    vector<string> fullLine;
    ifstream file("channels.csv");

    NTree tree(degree);
    NTree::Node* prev = nullptr;

    if (file.is_open()){
        //Extract first line
        getline(file, line);

        //While there is a line to read
        while(getline(file,line)){
            istringstream stream(line);
            bool quoteStatus = true;
            string cell;
            string newCell;

            //Keeps reading over cells that have commas in quotes not meant to be delimiters
            while(getline(stream, cell, ',')){
                if(count(cell.begin(), cell.end(), '"') % 2 != 0){
                    quoteStatus = !quoteStatus;
                }
                string tempComma;
                if(quoteStatus)
                    tempComma = "";
                else
                    tempComma = ",";
                newCell += cell + tempComma;
                if(quoteStatus){
                    fullLine.push_back(newCell);
                    newCell.clear();
                }
            }

            //Creates appropriate variables from CSV cells
            int categoryID = stoi(fullLine[0]);
            string category = fullLine[1];
            string channelID = fullLine[2];
            string country = fullLine[3];
            int subscriberCount = stoi(fullLine[4]);
            string joinDate = fullLine[5];
            string pictureURL = fullLine[6];
            string profileURL = fullLine[7];
            string title = fullLine[8];
            int videoCount = stoi(fullLine[9]);

            //Creates channel object and inserts appropriate values
            Channel c;
            c.setID(channelID);
            c.setTitle(title);
            c.setCategory(category);
            c.setCountry(country);
            c.setJoinDate(joinDate);
            c.setPictureURL(pictureURL);
            c.setProfileURL(profileURL);
            c.setSubCount(subscriberCount);
            c.setVidCount(videoCount);
            c.setCategoryID(categoryID);

            //Inserts channel into RBTree and clears the line vector

            if(tree.getRoot() == nullptr){
                NTree::Node* newRoot = new NTree::Node(c, nullptr);
                tree.insertNode(newRoot, nullptr);
                tree.getRoot()->parent = tree.getRoot();
                prev = tree.getRoot();
            }
            else{
                NTree::Node* newNode = new NTree::Node(c, nullptr);
                tree.insertNode(newNode, prev);
                prev = newNode;
            }
            fullLine.clear();
        }
    }
    return tree.getRoot();
}

void printMainMenu() {
    cout << "-------------- Main Menu --------------\n"
            "1. View overall top subscribed channels\n"
            "2. Filter by minimum subscriber count\n"
            "3. Filter by top channels per category\n"
            "4. Filter by top channels per country\n"
            "5. Search by channel ID number\n"
            "6. Exit program\n"
            "---------------------------------------\n"
            "Please make a selection:";
}
void printSubMenu(){
    cout << "Would you like to view extended or minimal statistics?\n"
            "1. Minimal\n"
            "2. Extended\n"
            "Please make a selection:";
}