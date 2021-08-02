#include "RBTree.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "Channel.h"
#include "Graph.h"

using namespace std;

// Redeclare static objects in global namespace
sf::Font Graph::font; 
int Graph::bar::maxNumber = 0;
int Graph::bar::numberOfBars = 0;
float Graph::bar::pixelWidthPerPoint = 10;
float Graph::bar::outlineWidth = 2.0f;


void Graph::runTestGraphic() {
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);

    sf::Event event;

    while (Window.isOpen()) {

        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        Window.clear();
        Window.draw(background);
        Window.draw(circle);
        Window.display();
    }

}

void Graph::EventLoop() {
    sf::Event event;

    while (Window.isOpen()) {

        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        Window.clear();
        Draw();
        Window.display();
    }


}

void Graph::displayRBTree(queue<RBTree::Node*>& q, string title) {
    int size = q.size();
    bar::numberOfBars = size;

    for (int i = 0; i < size; i++) {
        Channel currChannel = q.front()->channel;
        q.pop();
        Bars.push_back(bar(currChannel.getTitle(), currChannel.getSubCount()));

        if (currChannel.getSubCount() > bar::maxNumber)
            bar::maxNumber = currChannel.getSubCount();
    }

    setChannelAesthetics();

    EventLoop();
}

void Graph::RBTreeHandler(queue<RBTree::Node*>& q, string title) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), title);

    Graph myGraph(window);
    myGraph.displayRBTree(q, title);
}




void Graph::setChannelAesthetics() {
    int width = Window.getSize().x;
    int height = Window.getSize().y;

    float barheight = height / bar::numberOfBars / 2.0f;

    // If the bars are too big, readjust the ratio so that they fit in the window
    if (bar::maxNumber * bar::pixelWidthPerPoint > MaxBarLengthRatio * width)
        bar::pixelWidthPerPoint = (float)MaxBarLengthRatio * (float)width / (float)bar::maxNumber;


    for (int i = 0; i < bar::numberOfBars; i++) {
        Bars[i].setSize(sf::Vector2f(Bars[i].displayNumber * bar::pixelWidthPerPoint, barheight - bar::outlineWidth));
        Bars[i].setPosition(sf::Vector2f(0, barheight * 2 * i + barheight));

        Bars[i].setFillColor(sf::Color::Blue);
        Bars[i].setOutlineColor(sf::Color::Black);
        Bars[i].setOutlineThickness(bar::outlineWidth);

        Bars[i].channelLabel.setOrigin(sf::Vector2f(0, Bars[i].channelLabel.getGlobalBounds().height * 2));
        Bars[i].channelLabel.setPosition(sf::Vector2f(0, barheight * 2 * i + barheight));
        Bars[i].numberLabel.setOrigin(sf::Vector2f(Bars[i].numberLabel.getGlobalBounds().width + 10, Bars[i].numberLabel.getGlobalBounds().height));
        Bars[i].numberLabel.setPosition(sf::Vector2f(Bars[i].getSize().x, barheight * 2 * i + barheight + barheight/2));

    }

}


void Graph::Draw() {
    Window.draw(background);
    for (int i = 0; i < bar::numberOfBars; i++) {
        Window.draw(Bars[i]);
        Window.draw(Bars[i].channelLabel);
        Window.draw(Bars[i].numberLabel);
        // Draw labels:

    }

}

Graph::Graph(sf::RenderWindow& Window) : Window(Window) {
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(Window.getSize()));


    if (!font.loadFromFile("arial.ttf"))
        throw invalid_argument("Font File Not Found");

}


Graph::bar::bar(string channelName, int displayNumber) {
    this->channelName = channelName;
    this->displayNumber = displayNumber;


    channelLabel.setFont(font);
    numberLabel.setFont(font);

    channelLabel.setString(channelName);
    channelLabel.setFillColor(sf::Color::Black);
    channelLabel.setCharacterSize(24);
    
    numberLabel.setString(to_string(displayNumber));
    numberLabel.setFillColor(sf::Color::Black);
    numberLabel.setCharacterSize(24);
}