#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

class Shape
{
public:
	sf::Shape & body;

	Shape(sf::Shape & body) : body(body)
	{}
	
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
};

#endif // SHAPE_H