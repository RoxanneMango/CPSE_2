#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
	sf::CircleShape body;

	Circle(sf::Vector2f position, int radius, sf::Color fillColor, sf::Color outlineColor, sf::Color selectColor, int speed) : 
		body(radius, 3*radius), Shape(body)
	{
		this->id = 0;
		this->radius = radius;
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
		this->name = "circle";
		
		body.setOrigin(radius, radius);
		body.setPosition(position);

		body.setOutlineThickness(2);
		body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Circle()
	{}
	
	void draw(sf::RenderWindow & window) const override
	{
		window.draw(body);
	}
};

#endif // CIRCLE_H