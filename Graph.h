#pragma once
#include <SFML/Graphics.hpp>
/*
============================
Class for handling Bar Graph
============================
*/



class Graph {
	sf::RenderWindow& Window;
	std::vector<int*> Data;

public:

	// Inner Bar Class for handling all of the individual graphics per channel
	struct bar : public sf::RectangleShape {
		string channelName;
		int displayNumber;
		int order;

		sf::Text channelLabel;
		sf::Text numberLabel;

		bar(string channelName, int displayNumber);
		static int maxNumber;
		static int numberOfBars;
		static float outlineWidth;
		static float pixelWidthPerPoint;
	};

	std::vector<bar> Bars;
	static float MaxBarLengthRatio;

	sf::RectangleShape background;
	static sf::Font font;

	void runTestGraphic();

	void displayRBTree(queue<RBTree::Node*>& q, string title = "Title");
	void displayNTree(queue<NTree::Node*>& q, string title = "Title");

	void setChannelAesthetics();
	void Draw();
	void EventLoop();

	void static RBTreeHandler(queue<RBTree::Node*>& q, string title = "Title");
	void static NTreeHandler(queue<NTree::Node*>& q, string title = "Title");

	Graph(sf::RenderWindow& Window);

};