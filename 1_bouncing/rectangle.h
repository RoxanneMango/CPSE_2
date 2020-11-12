#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
	sf::RectangleShape body;
	
	Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color, bool justOutline = false);
	~Rectangle();
	
	void update();
	void draw(sf::RenderWindow & window);
};

#endif // RECTANGLE_H