#include "rectangle.h"

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color, bool justOutline) : body(size), Shape(body)
{
	body.setOrigin(size.x/2, size.y/2);
	body.setPosition(pos);
	if(justOutline)
	{
		body.setOutlineThickness(1);
		body.setFillColor(sf::Color::Transparent);
		body.setOutlineColor(color);
	}
	else
	{
		body.setFillColor(color);
	}
}

Rectangle::~Rectangle()
{}

void
Rectangle::update()
{
	/* Nothing to do here yet . . . */
}

void
Rectangle::draw(sf::RenderWindow & window)
{
	window.draw(body);
}