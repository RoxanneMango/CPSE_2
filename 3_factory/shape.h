#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

class Shape
{
protected:
	bool isSelected = false;
	sf::Vector2f velocity;
	int speed;
	
	sf::Color fillColor;
	sf::Color outlineColor;
	sf::Color selectColor;
	
public:
	int id = -1;
	sf::Shape & body;

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
		velocity.x = 0;
		velocity.y = 0;
		
		if(isSelected)
		{
			body.setOutlineColor(selectColor);
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{ 
				velocity.x = -speed; 
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{ 
				velocity.x = speed; 
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{ 
				velocity.y = -speed;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{ 
				velocity.y = speed; 
			}
			body.move(velocity);
		}
		else
		{
			body.setOutlineColor(outlineColor);
		}
	}
	
	virtual void draw(sf::RenderWindow & window) const = 0;
	virtual std::string getReceipt() = 0;
};

#endif // SHAPE_H