#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

class Shape
{
public:
	sf::Shape & body;

	Shape(sf::Shape & body) : body(body)
	{}
	
	virtual bool interact(sf::Shape & body)
	{
		return false;
	}
	virtual void update()
	{}
	virtual void draw(sf::RenderWindow & window) const = 0;
};

#endif // SHAPE_H