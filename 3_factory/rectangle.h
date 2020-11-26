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
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
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
	
	std::string getReceipt() override
	{
		std::string s;
		
		s += std::to_string(id) + " ";
		s += std::to_string((int)body.getPosition().x) + " ";
		s += std::to_string((int)body.getPosition().y) + " ";
		s += std::to_string((int)body.getSize().x) + " ";
		s += std::to_string((int)body.getSize().y) + " ";
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

#endif // RECTANGLE_H