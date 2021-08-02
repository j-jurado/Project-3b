#include "RBTree.h"
#include "NTree.h"
#include <vector>
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
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
float Graph::MaxBarLengthRatio = 0.9f;


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
    // max out bar graph at 2 channels
    if (size > 20) {
        size = 20;
        cout << "Note: Histogram can onlly display up to 20 channels." << endl;
        cout << "Displaying the first 20... " << endl;
    }
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

void Graph::NTreeHandler(queue<NTree::Node*>& q, string title) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), title);

    Graph myGraph(window);
    myGraph.displayNTree(q, title);
}
void Graph::displayNTree(queue<NTree::Node*>& q, string title) {
    int size = q.size();
    // max out bar graph at 2 channels
    if (size > 20) {
        size = 20;
        cout << "Note: Histogram can onlly display up to 20 channels." << endl;
        cout << "Displaying the first 20... " << endl;
    }
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



void Graph::setChannelAesthetics() {
    int width = Window.getSize().x;
    int height = Window.getSize().y;

    float barheight = height / bar::numberOfBars / 2.0f;

    // If there are more than 10 bars, readjust the maximum ratio so that channel names can fit on the right side
    bool aboveThreshold = false;
    if (bar::numberOfBars > 10) {
        MaxBarLengthRatio = 0.8f;
        aboveThreshold = true;
    }


    // If the bars are too big, readjust the ratio so that they fit in the window
    if (bar::maxNumber * bar::pixelWidthPerPoint > MaxBarLengthRatio * width)
        bar::pixelWidthPerPoint = (float)MaxBarLengthRatio * (float)width / (float)bar::maxNumber;


    for (int i = 0; i < bar::numberOfBars; i++) {
        Graph::bar& currBar = Bars[i];
        currBar.setSize(sf::Vector2f(currBar.displayNumber * bar::pixelWidthPerPoint, barheight - bar::outlineWidth));
        currBar.setPosition(sf::Vector2f(0, barheight * 2 * i + barheight));

        currBar.setFillColor(sf::Color::Blue);
        currBar.setOutlineThickness(bar::outlineWidth);
        currBar.setOutlineColor(sf::Color::Black);

        if (aboveThreshold) {
            currBar.numberLabel.setCharacterSize(12);
            currBar.channelLabel.setCharacterSize(12);
        }


        currBar.numberLabel.setOrigin(sf::Vector2f(currBar.numberLabel.getGlobalBounds().width + 10, currBar.numberLabel.getGlobalBounds().height));
        currBar.numberLabel.setPosition(sf::Vector2f(Bars[i].getSize().x, barheight * 2 * i + barheight + barheight/2));

        if (!aboveThreshold) {
            currBar.channelLabel.setOrigin(sf::Vector2f(0, currBar.channelLabel.getGlobalBounds().height * 2));
            currBar.channelLabel.setPosition(sf::Vector2f(0, barheight * 2 * i + barheight));
        }
        else {
            currBar.channelLabel.setOrigin(sf::Vector2f(-10, currBar.channelLabel.getGlobalBounds().height));
            currBar.channelLabel.setPosition(sf::Vector2f(currBar.getSize().x, barheight * 2 * i + barheight + barheight /2));
        }

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