#ifndef PICTURE_H
#define PICTURE_H

#include "shape.h"

class Picture : public Shape
{
	std::string PATH;
	sf::Texture texture;
public:
	sf::RectangleShape body;
	
	Picture(sf::Vector2f position, sf::Vector2f size, std::string PATH, sf::Color outlineColor, sf::Color selectColor, int speed) :
		PATH(PATH), body(size), Shape(body)
	{
		if(!(texture.loadFromFile(&PATH[0])))
		{
			printf("Error: could not open texture '%s'\n", PATH);
		}
		body.setTexture(&texture);
		
		this->id = 4;
		this->fillColor = sf::Color::Transparent;
		this->outlineColor = outlineColor;
		this->selectColor = selectColor;
		this->speed = speed;
		
		body.setOrigin(size.x/2, size.y/2);
		body.setPosition(position);

		body.setOutlineThickness(2);
	//	body.setFillColor(fillColor);
		body.setOutlineColor(outlineColor);
	}
	~Picture()
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
		s += PATH + " ";
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

#endif // PICTURE_H