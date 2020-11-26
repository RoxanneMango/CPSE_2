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
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
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
	
	std::string getReceipt() override
	{
		std::string s;
		
		s += std::to_string(id) + " ";
		s += std::to_string((int)body.getPosition().x) + " ";
		s += std::to_string((int)body.getPosition().y) + " ";
		s += std::to_string((int)body.getRadius()) + " ";
		s += std::to_string(fillColor.r) + " ";
		s += std::to_string(fillColor.g) + " ";
		s += std::to_string(fillColor.b) + " ";
		s += std::to_string(fillColor.a) + " ";
		s += std::to_string(outlineColor.r) + " ";
		s += std::to_string(outlineColor.g) + " ";
		s += std::to_string(outlineColor.b) + " ";
		s += std::to_string(outlineColor.a) + " ";
		s += std::to_string(selectColor.r) + " ";
		s += std::to_string(selectColor.g) + " ";
		s += std::to_string(selectColor.b) + " ";
		s += std::to_string(selectColor.a) + " ";
		s += std::to_string(speed) + " ";
		s += ";\n";
		
		return s;
	}
};

#endif // TRIANGLE_H