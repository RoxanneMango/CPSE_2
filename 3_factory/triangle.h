#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
public:
	sf::CircleShape body;

	Triangle(sf::Vector2f position, int radius, sf::Color fillColor, sf::Color outlineColor, sf::Color selectColor, int speed) : 
		body(radius, 3), Shape(body)
	{
		this->id = 2;
		this->radius = radius;
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
		this->name = "triangle";
		
		body.setOrigin(radius, radius);
		body.setPosition(position);
		
		body.setOutlineThickness(2);
		body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Triangle()
	{}
	
	void draw(sf::RenderWindow & window) const override
	{
		window.draw(body);
	}
};

#endif // TRIANGLE_H