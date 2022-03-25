#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

class Shape
{
public:
	sf::Shape & body;

	int id = -1;
	std::string name;

	sf::Vector2f size;
	int radius = 0;
	
	std::string PATH;
	sf::Color fillColor;
	sf::Color outlineColor;
	sf::Color selectColor;
	int speed;

	bool isSelected = false;
	sf::Vector2f velocity;

	Shape(sf::Shape & body) : body(body)
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	
	virtual void interact(sf::Shape & body)
	{
		isSelected = false;
		
		if(&this->body == &body) return; // if it is the same body return by default
		
		// match rotations
		float rotation = this->body.getRotation();
		this->body.setRotation(body.getRotation());
		
		float deltaX = this->body.getPosition().x - body.getPosition().x;
		float deltaY = this->body.getPosition().y - body.getPosition().y;
		//
		float intersectX = abs(deltaX) - (this->body.getOrigin().x + body.getOrigin().x);
		float intersectY = abs(deltaY) - (this->body.getOrigin().y + body.getOrigin().y);
		//	
		if(intersectX < 0.0f && intersectY < 0.0f)
		{	
			isSelected = true;
		}
		this->body.setRotation(rotation);
	}
	virtual void update()
	{	
		if(isSelected)
		{
			body.setOutlineColor(selectColor);
			body.move(velocity);
		}
		else
		{
			body.setOutlineColor(outlineColor);
		}
		velocity.x = 0;
		velocity.y = 0;
	}
	
	virtual void draw(sf::RenderWindow & window) const = 0;
};

#endif // SHAPE_H