#ifndef PICTURE_H
#define PICTURE_H

#include "shape.h"

class Picture : public Shape
{
	sf::Texture texture;
public:
	sf::RectangleShape body;
	
	Picture(sf::Vector2f position, sf::Vector2f size, std::string PATH, sf::Color outlineColor, sf::Color selectColor, int speed) :
		body(size), Shape(body)
	{
		if(!(texture.loadFromFile(&PATH[0])))
		{
			// exit
			exit(-1);
		}
		body.setTexture(&texture);
		
		this->name = "picture";
		
		this->id = 4;
		this->PATH = PATH;
		this->size = size;
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
};

#endif // PICTURE_H