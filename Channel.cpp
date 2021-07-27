#include "Channel.h"
#include <iostream>
using namespace std;

//Getters
string Channel::getID() {
    return channelID;
}
string Channel::getTitle() {
    return title;
}
string Channel::getCategory() {
    return category;
}
string Channel::getCountry() {
    return country;
}
string Channel::getJoinDate() {
    return joinDate;
}
string Channel::getPictureURL() {
    return pictureURL;
}
string Channel::getProfileURL() {
    return profileURL;
}
int Channel::getSubCount() {
    return subscriberCount;
}
int Channel::getVidCount() {
    return videoCount;
}
int Channel::getCategoryID() {
    return categoryID;
}

//Setters
void Channel::setID(string newID) {
    channelID = newID;
}
void Channel::setTitle(string newTitle) {
    title = newTitle;
}
void Channel::setCategory(string newCat) {
    category = newCat;
}
void Channel::setCountry(string newCountry) {
    country = newCountry;
}
void Channel::setJoinDate(string newDate) {
    joinDate = newDate;
}
void Channel::setPictureURL(string newURL) {
    pictureURL = newURL;
}
void Channel::setProfileURL(string newURL) {
    profileURL = newURL;
}
void Channel::setSubCount(int newCount) {
    subscriberCount = newCount;
}
void Channel::setVidCount(int newCount) {
    videoCount = newCount;
}
void Channel::setCategoryID(int newID) {
    categoryID = newID;
}