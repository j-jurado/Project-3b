#pragma once
#include <iostream>
using namespace std;

class Channel {
private:
    string title;
    string channelID;
    string category;
    string country;
    string joinDate;
    string pictureURL;
    string profileURL;
    int videoCount;
    int categoryID;

public:

    //Getters
    string getID();
    string getTitle();
    string getCategory();
    string getCountry();
    string getJoinDate();
    string getPictureURL();
    string getProfileURL();
    int getSubCount();
    int getVidCount();
    int getCategoryID();

    //Setters;
    void setID(string newID);
    void setTitle(string newTitle);
    void setCategory(string newCat);
    void setCountry(string newCountry);
    void setJoinDate(string newDate);
    void setPictureURL(string newURL);
    void setProfileURL(string newURL);
    void setSubCount(int newCount);
    void setVidCount(int newCount);
    void setCategoryID(int newID);

    //Public var for comparison purposes
    int subscriberCount;
};