#include "RBTree.h"
#include "Channel.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

RBTree::Node* parseCSVinRBTree();


int main(){

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