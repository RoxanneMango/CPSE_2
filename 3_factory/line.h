#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
	sf::RectangleShape body;
	
	Line(sf::Vector2f position, float length, float rotation, sf::Color fillColor, sf::Color outlineColor, sf::Color selectColor, int speed) :
		body(sf::Vector2f(length, 0)), Shape(body)
	{
		this->id = 3;
		this->size = sf::Vector2f(length, 0);
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
		this->name = "line";
		
		body.setOrigin(body.getSize().x/2, body.getSize().y/2);
		body.setPosition(position);
		body.setRotation(rotation);

		body.setOutlineThickness(2);
		body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Line()
	{}
	
	void draw(sf::RenderWindow & window) const override
	{
		window.draw(body);
	}
};

#endif // LINE_H