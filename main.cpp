#include "RBTree.h"
#include "NTree.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>

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

    if(option == 2){
        cout << endl;
        cout << "Thank you for using the Youtube Channel Analytic program!" << endl;
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

        cout << "Both trees will be used, but only one can be viewed at a time." << endl;
        cout << "1. Red-Black Tree" << endl;
        cout << "2. N-ary Tree" << endl;
        cout << "Please select a tree to view results from:";
        int viewTree;
        cin >> viewTree;
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
                queue<RBTree::Node*> rbQ = rbTree.searchByTopSubs(capacity);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                t1 = Clock::now();
                queue<NTree::Node*> nQ = nTree.searchByTopSubs(capacity);
                t2 = Clock::now();
                cout << "N-ary Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                cout << endl;
                printSubMenu();
                cin >> option;
                cout << endl;

                if(option == 1)
                    if(viewTree == 1)
                        while(!rbQ.empty()){
                            rbTree.smallPrint(rbQ.front());
                            rbQ.pop();
                        }
                    else{
                        while(!nQ.empty()){
                            nTree.smallPrint(nQ.front());
                            nQ.pop();
                        }
                    }
                else if (option == 2)
                    while(!rbQ.empty()){
                        rbTree.largePrint(rbQ.front());
                        rbQ.pop();
                    }
                else{
                    while(!nQ.empty()){
                        nTree.largePrint(nQ.front());
                        nQ.pop();
                    }
                }
                cout << endl;
            }
            else if (option == 2){
                cout << "---------- Search by Min Subs ---------" << endl;
                cout << "Enter minimum number of subscribers:";
                int capacity;
                cin >> capacity;

                t1 = Clock::now();
                queue<RBTree::Node*> rbQ = rbTree.searchByMinSubs(capacity);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                t1 = Clock::now();
                queue<NTree::Node*> nQ = nTree.searchByMinSubs(capacity);
                t2 = Clock::now();
                cout << "N-ary Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                cout << endl;
                printSubMenu();
                cin >> option;
                cout << endl;

                if(option == 1)
                    if(viewTree == 1)
                        while(!rbQ.empty()){
                            rbTree.smallPrint(rbQ.front());
                            rbQ.pop();
                        }
                    else{
                        while(!nQ.empty()){
                            nTree.smallPrint(nQ.front());
                            nQ.pop();
                        }
                    }
                else if (option == 2)
                    while(!rbQ.empty()){
                        rbTree.largePrint(rbQ.front());
                        rbQ.pop();
                    }
                else{
                    while(!nQ.empty()){
                        nTree.largePrint(nQ.front());
                        nQ.pop();
                    }
                }
                cout << endl;
            }
            else if (option == 3){
                cin.ignore();
                cin.clear();
                cin.sync();

                cout << "---------- Search by Category ---------" << endl;
                cout << "Enter category name:";
                string targetCat;
                cin >> targetCat;

                cout << "How many channels do you want to display?";
                int capacity;
                cin >> capacity;
                cout << endl;

                t1 = Clock::now();
                queue<RBTree::Node*> rbQ = rbTree.searchByCategory(targetCat, capacity);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                t1 = Clock::now();
                queue<NTree::Node*> nQ = nTree.searchByCategory(targetCat, capacity);
                t2 = Clock::now();
                cout << "N-ary Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                cout << endl;
                printSubMenu();
                cin >> option;
                cout << endl;

                if(option == 1)
                    if(viewTree == 1)
                        while(!rbQ.empty()){
                            rbTree.smallPrint(rbQ.front());
                            rbQ.pop();
                        }
                    else{
                        while(!nQ.empty()){
                            nTree.smallPrint(nQ.front());
                            nQ.pop();
                        }
                    }
                else if (option == 2)
                    while(!rbQ.empty()){
                        rbTree.largePrint(rbQ.front());
                        rbQ.pop();
                    }
                else{
                    while(!nQ.empty()){
                        nTree.largePrint(nQ.front());
                        nQ.pop();
                    }
                }
                cout << endl;
            }
            else if (option == 4){
                cin.ignore();
                cin.clear();
                cin.sync();

                cout << "---------- Search by Country ----------" << endl;
                cout << "Enter country name:";
                string targetCt;
                getline(cin, targetCt);

                cout << "How many channels do you want to display?";
                int capacity;
                cin >> capacity;
                cin.ignore();

                t1 = Clock::now();
                queue<RBTree::Node*> rbQ = rbTree.searchByCountry(targetCt, capacity);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                t1 = Clock::now();
                queue<NTree::Node*> nQ = nTree.searchByCountry(targetCt, capacity);
                t2 = Clock::now();
                cout << "N-ary Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                cout << endl;
                printSubMenu();
                cin >> option;
                cout << endl;

                if(option == 1)
                    if(viewTree == 1)
                        while(!rbQ.empty()){
                            rbTree.smallPrint(rbQ.front());
                            rbQ.pop();
                        }
                    else{
                        while(!nQ.empty()){
                            nTree.smallPrint(nQ.front());
                            nQ.pop();
                        }
                    }
                else if (option == 2)
                    while(!rbQ.empty()){
                        rbTree.largePrint(rbQ.front());
                        rbQ.pop();
                    }
                else{
                    while(!nQ.empty()){
                        nTree.largePrint(nQ.front());
                        nQ.pop();
                    }
                }
                cout << endl;
            }
            else if (option == 5){
                cout << "--------- Search by Channel ID --------" << endl;
                cout << "Enter ChannelID:";
                string targetID;
                cin >> targetID;
                cout << endl;

                t1 = Clock::now();
                RBTree::Node* tempRBNode = rbTree.searchByID(targetID);
                t2 = Clock::now();
                cout << "Red-Black Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;

                t1 = Clock::now();
                NTree::Node* tempNNode = nTree.searchByID(targetID);
                t2 = Clock::now();
                cout << "N-ary Tree search time: " << duration_cast<milliseconds>(t2-t1).count() << " milliseconds" << endl;
                cout << endl;

                if(viewTree == 1){
                    if(tempRBNode != nullptr)
                        rbTree.largePrint(tempRBNode);
                    else
                        cout << "Channel not found!" << endl;
                }
                else{
                    if(tempNNode != nullptr)
                        nTree.largePrint(tempNNode);
                    else{
                        cout <<  "Channel not found!" << endl;
                    }
                }
                cout << endl;
            }
            else if(option == 6){
                cout << "Thank you for using the Youtube Channel Analytic program!" << endl;
                return 0;
            }
            else{
                cout << "Error: Enter a value from the menu" << endl;
            }
        }
    }
    return 0;
}

/*=== CSV Parsers ===*/

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

            //Inserts channel into NTree and clears the line vector
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

/*=== Print Menus ===*/

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