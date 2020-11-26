#ifndef CURSOR_H
#define CURSOR_H

#include "shape.h"

class Cursor : public Shape
{
public:
	sf::RectangleShape body;
	
	Cursor(sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, sf::Color selectColor) :
		body(size), Shape(body)
	{
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = 0;
		
		body.setOrigin(size.x/2, size.y/2);
		
		body.setOutlineThickness(1);
		body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Cursor()
	{}

	void interact(sf::Shape & body) override
	{
		isSelected = true;
	}

	void update() override
	{
		if(isSelected)
		{
			body.setOutlineColor(selectColor);
		}
		else
		{
			body.setOutlineColor(outlineColor);
		}
		isSelected = false;
	}
	
	void draw(sf::RenderWindow & window) const override
	{
		window.draw(body);
	}
	
	std::string getReceipt() override
	{
		std::string s;
		
		s += std::to_string(id);
		
		return s;
	}
};

#endif // CURSOR_H