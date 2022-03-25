#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
	sf::RectangleShape body;
	
	Rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, sf::Color selectColor, int speed) :
		body(size), Shape(body)
	{
		this->id = 1;
		this->size = size;
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
		this->name = "rectangle";
		
		body.setOrigin(size.x/2, size.y/2);
		body.setPosition(position);

		body.setOutlineThickness(2);
		body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Rectangle()
	{}
	
	void draw(sf::RenderWindow & window) const override
	{
		window.draw(body);
	}
};

#endif // RECTANGLE_H